
#include <mcf5282.h>
#include <stdlib.h>

#include "term/terminal.h"

#include "network/tftp.h"
#include "network/udp.h"

#include "eeprom.h"
#include "timer.h"
#include "module.h"
#include "romfs.h"

#include "dect.h"
#include "dect-mac.h"


#define MOD_BASEADDR	0x20000000
#define MOD_XLXFILE		"ema-dect.bin"

static tftp_client tftp;
static int xlx_bytes;
static uint8 xlx_state;
static uint8 xlx_sniff;

static uint8 rx_afield[8];
static uint8 rx_frame;

/* DECT module memory */
struct dect_ram *dect;


/* ==================================================================
 * = Module FPGA related functions
 */

/* fpga_reset()
 *   This function reset the module FPGA, using the QSPI_CS3 pin.
 */
static void fpga_reset()
{
	/* 1ms sync */
	tmr_gp_wait(1);

	/* CS3 is bit 6 */
	MCF5282_GPIO_PORTQS = 0;
	MCF5282_GPIO_DDRQS = 0x40;

	/* Wait 1ms */
	tmr_gp_wait(1);

	/* Release CS3 */
	MCF5282_GPIO_DDRQS = 0;

	/* Wait before writing to FPGA */
	xlx_state = 0;
	tmr_gp_wait(1);
}

static void cb_tftp_recv(int code, uint8 *data, int len)
{
	int i;

	if (code > 0) {
		if (code == 1) {
			term_log_all("DECT: Loading FPGA...\r\n");
			fpga_reset();
			xlx_bytes = 0;
		}
		if ((!data) || (!len)) return;
		/* Load data into Xilinx */
		for (i = 0; i < len; i++) {
			DECT_REG_DATA = data[i];
		}
		xlx_bytes += len;
		if (len < 512) {
			term_log_all("DECT: FPGA loaded, %i bytes.\r\n", xlx_bytes);
			xlx_state = 1;
			/* STAT7 = 1, STAT6 = 0 if FPGA is initialized */
			if ( (DECT_REG_STATUS & 0xC0) == 0x80 ) {
				xlx_state = 2;
				dect_init_slots();
				term_log_all("DECT: Module initialized.\r\n");
			}
		}
	}
}

static void fpga_init()
{
	memset(&tftp, 0, sizeof(tftp));
	tftp.cbfunc = cb_tftp_recv;
	tftp_start(&tftp, MOD_XLXFILE);
}

static void fpga_init_romfs()
{
	int i;
	struct romfs_file *f;

	f = romfs_find_file(MOD_XLXFILE);
	if (!f) return;

	fpga_reset();
	for (i = 0; i < f->size; i++) {
		DECT_REG_DATA = f->data[i];
	}

	/* STAT7 = 1, STAT6 = 0 if FPGA is initialized */
	if ( (DECT_REG_STATUS & 0xC0) == 0x80 ) {
		xlx_state = 2;
		dect_init_slots();
	}
}

/* ==================================================================
 * = GPS related functions
 */

static void dect_gps_line(char *s)
{
	int n, i, l;
	char *p[20];

	/* Log */
	if (dect->gps.log) {
		term_log_all("DECT: GPS '%s'\r\n", s);
	}

	l = strlen(s);
	if (l < 5) return;
	if (memcmp(s, "$GP", 3)) return;

	n = 0;
	for (i = 0; i < l; i++) {
		if (s[i] == ',') {
			s[i] = 0;
			if (n < 19) p[n++] = &s[i+1];
		}
	}

	/* GPRMC -- Required Minimum */
	if (!strcmp(s, "$GPRMC") && (n >= 6)) {
		if (p[1][0] != 'A') {
			/* GPS data not valid */
			dect->gps.state = DECT_GPS_NOLOCK;
		} else {
			/* GPS data is valid */
			dect->gps.state = DECT_GPS_LOCK;
			dect->gps.lt_high = atoi(p[2]);
			dect->gps.lt_dir = p[3][0];
			dect->gps.lg_high = atoi(p[4]);
			dect->gps.lg_dir = p[5][0];
		}
		return;
	}

	/* GPZDA -- Date and Time */
	if (!strcmp(s, "$GPZDA") && (n >= 6)) {
		return;
	}
}

/* ==================================================================
 * = Terminal commands
 */

static void cmd_dect_init(struct terminal *term, int reason)
{
	if (reason == TERM_RSN_EXEC) {
		fpga_init();
	}
}

static void cmd_dect_sniff(struct terminal *term, int reason)
{
	if (reason == TERM_RSN_EXEC) {
		xlx_sniff = 1;
	}
}

static void cmd_dect_gps_log(struct terminal *term, int reason)
{
	if (reason == TERM_RSN_EXEC) {
		bprintf(term->out, "GPS logging enabled.\r\n");
		dect->gps.log = 1;
	}
}

static void cmd_dect_gps_nolog(struct terminal *term, int reason)
{
	if (reason == TERM_RSN_EXEC) {
		bprintf(term->out, "GPS logging disabled.\r\n");
		dect->gps.log = 0;
	}
}

static void cmd_dect_server(struct terminal *term, int reason)
{
	uint32 ip;

	if (reason == TERM_RSN_EXEC) {
		ip = term_get_ip(term);
		if (!ip) {
			bprintf(term->out, "Bad IP address.\r\n");
			return;
		}
		dect->config.dect_server = ip;

		ip = term_get_int(term, 10);
		if (ip > 0) {
			dect->config.fpid = ip;
		}
	}
}

static void cmd_show_dect(struct terminal *term, int reason)
{
	if (reason == TERM_RSN_EXEC) {
		if (xlx_state == 0) {
			bprintf(term->out, "Module is not initialized.\r\n");
			return;
		}

		bprintf(term->out, "DECT Server is %i.%i.%i.%i, Fixed Part ID is 0x%X\r\n",
			(dect->config.dect_server >> 24) & 0xFF, (dect->config.dect_server >> 16) & 0xFF,
			(dect->config.dect_server >> 8) & 0xFF, (dect->config.dect_server) & 0xFF,
			dect->config.fpid);

		bprintf(term->out, "DECT RFPI is %X:%X:%X:%X:%X\r\n",
			dect->rfpi[0], dect->rfpi[1], dect->rfpi[2], dect->rfpi[3], dect->rfpi[4]);
		/* GPS info */
		switch (dect->gps.state) {
			case DECT_GPS_NONE:
				bprintf(term->out, "GPS not found\r\n");
				break;
			case DECT_GPS_NOLOCK:
				bprintf(term->out, "GPS is not locked\r\n");
				break;
			case DECT_GPS_LOCK:
				bprintf(term->out, "GPS is locked, OSC Freq is %i Hz\r\n", dect->gps.freq);
				bprintf(term->out, "GPS position is %i^%i' %c, %i^%i' %c\r\n",
					dect->gps.lt_high / 100, dect->gps.lt_high % 100, dect->gps.lt_dir,
					dect->gps.lg_high / 100, dect->gps.lg_high % 100, dect->gps.lg_dir);
				break;
		}
	}
}

static void dect_sniff(uint8 *data)
{
	uint8		buf[50];
	uint16		x;
	IF_BUFFER	pkt;
	int			i;

	buf[0] = 'S';
	buf[1] = 0;
	buf[2] = data[0];
	buf[3] = data[1];
	buf[4] = data[2];
	buf[5] = data[3];
	buf[6] = data[4];
	buf[7] = data[5];
	buf[8] = data[6];
	buf[9] = data[7];

	for (i = 0; i < 40; i++) {
		x = DECT_REG_RXD & 0xFF;
		buf[i+10] = x;
	}

	pkt.data = buf;
	pkt.size = 50;
	pkt.next = NULL;
	udp_send(0, 2048, eeprom.tftp_server, 2048, &pkt);
}

/* ==================================================================
 * = Module API
 */

static void mod_dect_process()
{
	uint16 x, m;
	uint32 freq;
	int i;
	uint8 hdr[2], status, rxd, pid;
	IF_BUFFER shdr, sdata;

	/* 8kHz polling rate */
	x = MCF5282_GPTA_GPTCNT >> 5;
	if (x == dect->tmr) return;
	dect->tmr = x;

	/* Switch to dect process */
	pid = tmr_load_switch(dect->dect_pid);

	/* Check for received UART char */
	if (MCF5282_UART0_USR & MCF5282_UART_USR_RXRDY) {
		rxd = MCF5282_UART0_URB;
		/* store GPS line into buffer */
		if (rxd >= 32) {
			if (dect->gps.urx_len < (DECT_URX_SIZE-1)) {
				dect->gps.urx_buf[dect->gps.urx_len++] = rxd;
			}
		}
		/* CR */
		if (rxd == 13) {
			dect->gps.urx_buf[dect->gps.urx_len] = 0;
			dect_gps_line(dect->gps.urx_buf);
			dect->gps.urx_len = 0;
		}
	}

	if (xlx_state == 2) {

		/* Read status register */
		status = DECT_REG_STATUS;

		if (status & DECT_STATUS_RECV) {
			/* Packet received - read slot number */
			DECT_REG_ADDR = DECT_ADDR_SN;
			m = DECT_REG_DATA;
			/* Read packet A-field */
			DECT_REG_ADDR = 0;
			for (i = 0; i < 8; i++) {
				x = DECT_REG_RXD & 0xFF;
				rx_afield[i] = x;
			}

			if (xlx_sniff == 0) {
				dect_recv_sync(m % 12, rx_afield);
			} else {
				dect_sniff(rx_afield);
			}

			/* indicate traffic */
			if (((rx_afield[0] >> 5) & 7) != 3) {
				tmr_gp_blink(50);
			}
		}

		if ((status & 2) != rx_frame) {
			/* Last TX in Frame */
			rx_frame = status & 2;
			dect_next_frame();
		}

		/* Check 1-pulse-per-second GPS signal */
		if ((status & DECT_STATUS_1PPS) != dect->gps.pps) {
			dect->gps.pps = status & DECT_STATUS_1PPS;
			if (dect->gps.pps) {
				tmr_gp_blink(50);
				/* Read current frequency */
				DECT_REG_ADDR = DECT_ADDR_FRQ0;
				freq = DECT_REG_DATA;
				DECT_REG_ADDR = DECT_ADDR_FRQ1;
				freq |= DECT_REG_DATA << 8;
				DECT_REG_ADDR = DECT_ADDR_FRQ2;
				freq |= DECT_REG_DATA << 16;
				DECT_REG_ADDR = DECT_ADDR_FRQ0;
				dect->gps.freq = freq;
			}
		}

	} /* if (xlx_state == 2) */

	/* Switch back */
	tmr_load_switch(pid);
}

static int mod_dect_save()
{
	eeprom_write(1, 64, (uint8 *)&dect->config, sizeof(dect->config));
	return 0;
}

static struct module_func mod_dect_func = {
	.mod_process = mod_dect_process,
	.mod_save = mod_dect_save
};

void mod_dect_init()
{
	struct term_command *cmd_dect, *cmd_dect_gps;
	struct term_command *cmd_show;

	dect = malloc(sizeof(struct dect_ram));
	if (!dect) return;
	memset(dect, 0, sizeof(struct dect_ram));
	dect->modbase = (uint8 *)MOD_BASEADDR;

	/* IO setup */
	MCF5282_CS3_CSAR = MOD_BASEADDR >> 16;
	MCF5282_CS3_CSMR = MCF5282_CS_CSMR_BAM_64K | MCF5282_CS_CSMR_CI | MCF5282_CS_CSMR_V;
	MCF5282_CS3_CSCR = MCF5282_CS_CSCR_WS(2) |
		MCF5282_CS_CSCR_AA | MCF5282_CS_CSCR_PS_32;

	/* Pins setup */
	MCF5282_GPIO_PBCDPAR = MCF5282_GPIO_PBCDPAR_PCDPA;	/* D0-D15 */
	MCF5282_GPIO_PEPAR = MCF5282_GPIO_PEPAR_PEPA4;		/* R/W */
	MCF5282_GPIO_PJPAR = MCF5282_GPIO_PJPAR_PJPA3;		/* CS3 */

	/* UART is used for GPS receiver */
	MCF5282_UART0_UCR = MCF5282_UART_UCR_RESET_MR;
	/* 8bit, no parity, 1 stop bit */
	MCF5282_UART0_UMR = MCF5282_UART_UMR1_PM_NONE | MCF5282_UART_UMR1_BC_8;		/* UMR1 */
	MCF5282_UART0_UMR = MCF5282_UART_UMR2_STOP_BITS_1;							/* UMR2 */
	/* 9600 baud */
	MCF5282_UART0_UCSR = MCF5282_UART_UCSR_RCS_SYS_CLK |
		MCF5282_UART_UCSR_TCS_SYS_CLK;
	MCF5282_UART0_UBG1 = 0;
	MCF5282_UART0_UBG2 = 213;
	/* Enable receiver */
	MCF5282_UART0_UCR = MCF5282_UART_UCR_RX_ENABLED;

	/* UART pins setup */
	MCF5282_GPIO_PUAPAR = 0x03;			/* Enable URXD0 & UTXD0 pins */

	xlx_state = 0;
	xlx_sniff = 0;

	/* Terminal commands */
	cmd_dect = term_reg_command(NULL, "dect", "Digital Cordless Telephone commands", NULL);
	term_reg_command(cmd_dect, "init", "Initialize DECT module", cmd_dect_init);
	term_reg_command(cmd_dect, "sniff", "Start raw packet sniffing", cmd_dect_sniff);
	term_reg_command(cmd_dect, "server", "Set DECT server address", cmd_dect_server);

	cmd_dect_gps = term_reg_command(cmd_dect, "gps", "GPS receiver commands", NULL);
	term_reg_command(cmd_dect_gps, "log", "Enable GPS logging", cmd_dect_gps_log);
	term_reg_command(cmd_dect_gps, "nolog", "Disable GPS logging", cmd_dect_gps_nolog);

	term_find(&cmd_show, "show", NULL);
	term_reg_command(cmd_show, "dect", "Show DECT module status", cmd_show_dect);

	/* Read module configuration from EEPROM */
	eeprom_read(1, 64, (uint8 *)&dect->config, sizeof(dect->config));

	dect->rfpi[0] = 0x15;
	dect->rfpi[1] = 0x24;
	dect->rfpi[2] = 0x20;
	dect->rfpi[3] = 0x01;
	dect->rfpi[4] = dect->config.fpid & 0xFF;
	dect_mbc_init();

	/* Create new process */
	dect->dect_pid = tmr_load_register("DECT Module");

	/* register callbacks */
	mod_set_callbacks(&mod_dect_func);

	/* Start loading FPGA */
	fpga_init_romfs();
}
