
#include <mcf5282.h>
#include <stdlib.h>
#include "config.h"

#include "term/terminal.h"
#include "network/if.h"
#include "network/udp.h"
#include "eeprom.h"
#include "timer.h"
#include "lsic.h"
#include "time.h"
#include "module.h"


#define MOD_BASEADDR		0x20000000		/* Module base address */
#define LSIC_ADC_ADDR		0x40			/* A/D converter I2C address */

#define LSIC_NVRAM_CONFIG	64				/* Configuration offset in NVRAM */
#define LSIC_NVRAM_KEYADDR	3072			/* Key table offset in NVRAM */

static struct lsic_ram *lsic;

static uint8 bit_count;
static uint8 bit_timeout;
static uint8 bit_buffer[8];


/* lsic_adc_setup()
 *   Configures AD7993 A/D converter.
 */
static void lsic_adc_setup()
{
	uint8	buf[30];

	/* Configuration register */
	buf[0] = AD7993_REG_CONFIG;
	buf[1] = 0xF0 | AD7993_CONFIG_ALERT;
	/* Cycle timer register */
	buf[2] = AD7993_REG_TIMER;
	buf[3] = AD7993_TIMER_X32;
	/* Input 1 */
	if (lsic->config.inp[0].type) {
		/* DATAlow CH1 */
		buf[4] = AD7993_REG_DATAL1;
		buf[5] = (lsic->config.inp[0].min >> 8) & 0x0F;
		buf[6] = lsic->config.inp[0].min & 0xFC;
		/* DATAhigh CH1 */
		buf[7] = AD7993_REG_DATAH1;
		buf[8] = (lsic->config.inp[0].max >> 8) & 0x0F;
		buf[9] = lsic->config.inp[0].max & 0xFC;
	} else {
		/* DATAlow CH1 */
		buf[4] = AD7993_REG_DATAL1;
		buf[5] = 0;
		buf[6] = 0;
		/* DATAhigh CH1 */
		buf[7] = AD7993_REG_DATAH1;
		buf[8] = 0x0F;
		buf[9] = 0xFC;
	}
	/* Input 2 */
	if (lsic->config.inp[1].type) {
		/* DATAlow CH2 */
		buf[10] = AD7993_REG_DATAL2;
		buf[11] = (lsic->config.inp[1].min >> 8) & 0x0F;
		buf[12] = lsic->config.inp[1].min & 0xFC;
		/* DATAhigh CH2 */
		buf[13] = AD7993_REG_DATAH2;
		buf[14] = (lsic->config.inp[1].max >> 8) & 0x0F;
		buf[15] = lsic->config.inp[1].max & 0xFC;
	} else {
		/* DATAlow CH2 */
		buf[10] = AD7993_REG_DATAL2;
		buf[11] = 0;
		buf[12] = 0;
		/* DATAhigh CH2 */
		buf[13] = AD7993_REG_DATAH2;
		buf[14] = 0x0F;
		buf[15] = 0xFC;
	}
	/* Input 3 */
	if (lsic->config.inp[2].type) {
		/* DATAlow CH3 */
		buf[16] = AD7993_REG_DATAL3;
		buf[17] = (lsic->config.inp[2].min >> 8) & 0x0F;
		buf[18] = lsic->config.inp[2].min & 0xFC;
		/* DATAhigh CH3 */
		buf[19] = AD7993_REG_DATAH3;
		buf[20] = (lsic->config.inp[2].max >> 8) & 0x0F;
		buf[21] = lsic->config.inp[2].max & 0xFC;
	} else {
		/* DATAlow CH3 */
		buf[16] = AD7993_REG_DATAL3;
		buf[17] = 0;
		buf[18] = 0;
		/* DATAhigh CH3 */
		buf[19] = AD7993_REG_DATAH3;
		buf[20] = 0x0F;
		buf[21] = 0xFC;
	}
	/* Input 4 */
	if (lsic->config.inp[3].type) {
		/* DATAlow CH4 */
		buf[22] = AD7993_REG_DATAL4;
		buf[23] = (lsic->config.inp[3].min >> 8) & 0x0F;
		buf[24] = lsic->config.inp[3].min & 0xFC;
		/* DATAhigh CH4 */
		buf[25] = AD7993_REG_DATAH4;
		buf[26] = (lsic->config.inp[3].max >> 8) & 0x0F;
		buf[27] = lsic->config.inp[3].max & 0xFC;
	} else {
		/* DATAlow CH4 */
		buf[22] = AD7993_REG_DATAL4;
		buf[23] = 0;
		buf[24] = 0;
		/* DATAhigh CH4 */
		buf[25] = AD7993_REG_DATAH4;
		buf[26] = 0x0F;
		buf[27] = 0xFC;
	}

	/* Write configuration to ADC */
	i2c_write(LSIC_ADC_ADDR, buf, 28);
	i2c_stop();
}

/* lsic_adc_get_alert()
 *   Get alert bits from ADC.
 */
static uint8 lsic_adc_get_alert()
{
	uint8 buf[10];

	/* Alert status register */
	buf[0] = AD7993_REG_ALERT;
	buf[1] = 0xFF;

	/* Read alert status */
	i2c_write(LSIC_ADC_ADDR, buf, 1);
	i2c_read(LSIC_ADC_ADDR, &buf[1], 2);

	/* clear alert bits */
	i2c_write(LSIC_ADC_ADDR, buf, 2);
	i2c_stop();

	return buf[1];
}

static void lsic_adc_get_values(uint16 *data)
{
	int		i;
	uint8	buf[32];
	char	s_adc[10];

	/* Read A/D results */
	data[0] = 0; data[1] = 0; data[2] = 0; data[3] = 0;
	buf[0] = AD7993_REG_RESULT;
	i2c_write(LSIC_ADC_ADDR, buf, 1);
	if (i2c_read(LSIC_ADC_ADDR, buf, 32) == 32) {
		for (i = 0; i < 16; i++) {
			data[(buf[i*2] >> 4) & 0x03] = 0x8000 | ((buf[i*2] & 0x0F) << 8) | buf[i*2+1];
		}
	}
}

/* lsic_adc_print_value()
 *   Calculates input line resistance from ADC result value.
 */
static void lsic_adc_print_value(char *buf, uint16 value)
{
	uint16 res;

	if ( (value > 3950) || (lsic->config.adc_1k_value == 0) ) {
		sprintf(buf, "open");
		return;
	}

	res = value * 1000 / lsic->config.adc_1k_value;
	sprintf(buf, "%i", res);
}

static void lsic_log(uint8 code, uint8 key_len, uint8 *key_bits, uint8 param)
{
	int i;

	i = lsic->log_next_idx;
	lsic->logs[i].id = ++lsic->log_last_id;
	lsic->logs[i].tms = time(NULL);
	lsic->logs[i].type = code;
	lsic->logs[i].bitcnt = key_len;
	lsic->logs[i].param = param;
	if (key_bits) memcpy(lsic->logs[i].bits, key_bits, 7);

	/* Move to next entry */
	lsic->log_next_idx++;
	if (lsic->log_next_idx >= LSIC_MAX_LOGS) lsic->log_next_idx = 0;
}

/* lsic_wiegand_process()
 *   Process received wiegand data.
 */
static void lsic_wiegand_process(int count, uint8 *bits)
{
	int i, bc;

	/* Do not accept <26 bits */
	if (count < 26) return;

	/* Byte count */
	bc = (count+7) >> 3;

	/* Log */
	term_log_all("LSIC: %i wiegand bits [%X %X %X %X].\r\n", count,
		bits[0], bits[1], bits[2], bits[3]);

	/* Find key */
	for (i = 0; i < LSIC_MAX_KEYS; i++) {
		if ( (lsic->keys[i].flags & LSIC_KEY_VALID) && (lsic->keys[i].bitcnt == count) ) {
			/* Compare keys */
			if (memcmp(&lsic->keys[i].bits, bits, bc) == 0) {
				/* Log */
				term_log_all("LSIC: ACCESS GRANTED\r\n");
				lsic_log(LSIC_LOG_KEY_GRANTED, count, bits, 0);
				/* Open door */
				lsic->tmr_door_open = lsic->config.tv_door_open;
				/* Short beep */
				lsic->tmr_beep = 100;
				return;
			}
		}
	}

	/* Check if we need to add new key */
	if (lsic->tmr_rfid_assign) {
		lsic->tmr_rfid_assign = 0;
		for (i = 0; i < LSIC_MAX_KEYS; i++) {
			/* Find empty record */
			if (lsic->keys[i].flags == 0) {
				lsic->keys[i].bitcnt = count;
				memcpy(lsic->keys[i].bits, bits, 7);
				lsic->keys[i].flags = LSIC_KEY_VALID | LSIC_KEY_SAVE;
				/* Log */
				term_log_all("LSIC: New key assigned.\r\n");
				lsic_log(LSIC_LOG_KEY_ASSIGNED, count, bits, 0);
				return;
			}
		}
		return;
	}

	/* Log */
	term_log_all("LSIC: ACCESS DENIED\r\n");
	lsic_log(LSIC_LOG_KEY_NOTFOUND, count, bits, 0);
	/* Long beep */
	lsic->tmr_beep = 2000;
}

static int lsic_state_bit(int stateid)
{
	time_t	tms;

	tms = time(NULL);

	switch (stateid) {
		case LSIC_STATE_DOOR_OPEN:
			return lsic->tmr_door_open != 0;
		case LSIC_STATE_ALARM:
			return (lsic->alarm) != 0;
		case LSIC_STATE_BEEP:
			return (lsic->tmr_beep != 0) | ( (lsic->alarm) && (tms & 1) );
	}
	return 0;
}

static void lsic_state_active(uint8 num)
{
	switch (lsic->config.inp[num].type) {
		/* ALARM */
		case LSIC_INPUT_ALARM:
			lsic_log(LSIC_LOG_ALARM, 0, NULL, num);
			break;

		/* 'door open' button pressed */
		case LSIC_INPUT_DOOR_KEY:
			if (!lsic->tmr_door_open) {
				lsic->tmr_door_open = lsic->config.tv_door_open;
				lsic_log(LSIC_LOG_DOOR_OPENKEY, 0, NULL, 0);
			}
			break;
	}
}

static void lsic_state_change(uint8 state)
{
	uint8	alarm;

	/* Check if alert bits are actually changed */
	if (lsic->alert == state) return;

	/* Calculate ALARM bit mask */
	alarm = 0;
	if (lsic->config.inp[0].type == LSIC_INPUT_ALARM) alarm |= 0x03;
	if (lsic->config.inp[1].type == LSIC_INPUT_ALARM) alarm |= 0x0C;
	if (lsic->config.inp[2].type == LSIC_INPUT_ALARM) alarm |= 0x30;
	if (lsic->config.inp[3].type == LSIC_INPUT_ALARM) alarm |= 0xC0;

	/* Process new bits */
	if ( (state & ~lsic->alert) & 0x03 ) lsic_state_active(0);
	if ( (state & ~lsic->alert) & 0x0C ) lsic_state_active(1);
	if ( (state & ~lsic->alert) & 0x30 ) lsic_state_active(2);
	if ( (state & ~lsic->alert) & 0xC0 ) lsic_state_active(3);

	lsic->alert = state;
	lsic->alarm = alarm & state;
}

/* lsic_config_read()
 *   read configuration from NVRAM
 */
static void lsic_config_read()
{
	lsic_config_t	conf;

	memset(&conf, 0, sizeof(conf));
	eeprom_read(1, LSIC_NVRAM_CONFIG, (uint8 *)&conf, sizeof(conf));

	if (conf.version == 1) {
		memcpy(&lsic->config, &conf, sizeof(conf));
		return;
	}
}

static void lsic_config_store()
{
	eeprom_write(1, LSIC_NVRAM_CONFIG, (uint8 *)&lsic->config, sizeof(lsic_config_t));
}

static char *lsic_state_string(int stateid)
{
	switch (stateid) {
		case LSIC_STATE_DOOR_OPEN:
			return "Door open";
		case LSIC_STATE_ALARM:
			return "Alarm";
		case LSIC_STATE_BEEP:
			return "Beeper";
	}
	return "(None)";
}

static void cmd_guard_assign(struct terminal *term, int reason)
{
	if (reason == TERM_RSN_EXEC) {
		lsic->tmr_rfid_assign = lsic->config.tv_assign;
	}
}

static void cmd_show_guard(struct terminal *term, int reason)
{
	int		i;
	uint16	adc[4];
	char	s_adc[10];

	if (reason == TERM_RSN_EXEC) {
		/* Read A/D results */
		lsic_adc_get_values(adc);
		/* Write line status */
		bprintf(term->out, "Line  Resist\r\n");
		for (i = 0; i < 4; i++) {
			sprintf(s_adc, "?");
			if (adc[i] & 0x8000) lsic_adc_print_value(s_adc, adc[i] & 0x7FFF);
			bprintf(term->out, " %i    %s\r\n", i, s_adc);
		}
	}
}

/* ==================================================================
 * = Module API
 */

static void mod_lsic_process()
{
	int i, cnt, stat;
	int key_offset;
	uint8 out;

	if (!lsic) return;

	/* 0.5ms interval */
	cnt = MCF5282_GPTA_GPTCNT >> 7;
	if (cnt == lsic->tmr_counter) return;
	lsic->tmr_counter = cnt;

	/* Timers */
	if (lsic->tmr_beep) lsic->tmr_beep--;

	/* Read module status */
	stat = lsic->modbase[7];
	if (stat & 0x80) return;

	/* Process wiegand bits */
	if (stat & 0x02) {
		/* Store bit */
		if ( (bit_count < 64) && (stat & 0x01) ) {
			bit_buffer[bit_count >> 3] |= 0x80 >> (bit_count & 7);
		}
		bit_count++;
		bit_timeout = 0;
	} else {
		if (bit_count) {
			bit_timeout++;
			if (bit_timeout > 10) {
				/* End of bit sequence */
				lsic_wiegand_process(bit_count, bit_buffer);
				bit_count = 0;
				memset(bit_buffer, 0, 8);
			}
		}
	}

	/* Check ADC alert */
	if ( !(stat & LSIC_STATUS_ALARM) ) {
		if (!lsic->alert) {
			lsic_state_change(lsic_adc_get_alert());
		}
	}

	/* Write control register */
	out = 0;
	if (lsic_state_bit(lsic->config.relay1_state)) out |= LSIC_CONTROL_RLY1;
	if (lsic_state_bit(lsic->config.relay2_state)) out |= LSIC_CONTROL_RLY2;
	if (lsic_state_bit(lsic->config.onewire_state)) out |= LSIC_CONTROL_1WIRE;
	lsic->modbase[7] = out;

	/* Check if we need to store key table modifications */
	for (i = 0; i < LSIC_MAX_KEYS; i++) {
		if (lsic->keys[i].flags & LSIC_KEY_SAVE) {
			/* Clear SAVE bit */
			lsic->keys[i].flags &= ~LSIC_KEY_SAVE;
			/* Calculate NVRAM offset */
			key_offset = LSIC_NVRAM_KEYADDR + i * sizeof(lsic_key_rec);
			/* Save to NVRAM */
			eeprom_write(1, key_offset, (uint8 *)&lsic->keys[i], sizeof(lsic_key_rec));
			/* One key per 0.5ms */
			break;
		}
	}

	/* 1s interval */
	if (lsic->tmr_seconds == time(NULL)) return;
	lsic->tmr_seconds = time(NULL);

	/* 1s timers */
	if (lsic->tmr_door_open) lsic->tmr_door_open--;
	if (lsic->tmr_rfid_assign) lsic->tmr_rfid_assign--;

	/* Update ADC alert */
	if (lsic->alert) {
		lsic_state_change(lsic_adc_get_alert());
	}
}

static struct module_func mod_lsic_func = {
	.mod_process = mod_lsic_process
};

void mod_lsic_init()
{
	int i;
	struct term_command *cmd_show, *cmd_guard;

	/* Allocate memory */
	lsic = malloc(sizeof(struct lsic_ram));
	if (!lsic) return;
	memset(lsic, 0, sizeof(struct lsic_ram));

	/* Initialize variables */
	lsic->tmr_counter = 0;
	lsic->modbase = (uint8 *)MOD_BASEADDR;
	bit_count = 0;
	bit_timeout = 0;
	memset(bit_buffer, 0, 8);

	/* IO setup */
	MCF5282_CS3_CSAR = MOD_BASEADDR >> 16;
	MCF5282_CS3_CSMR = MCF5282_CS_CSMR_BAM_64K | MCF5282_CS_CSMR_CI | MCF5282_CS_CSMR_V;
	MCF5282_CS3_CSCR = MCF5282_CS_CSCR_WS(2) |
		MCF5282_CS_CSCR_AA | MCF5282_CS_CSCR_PS_32;

	/* Pins setup */
	MCF5282_GPIO_PBCDPAR = MCF5282_GPIO_PBCDPAR_PCDPA;	/* D0-D15 */
	MCF5282_GPIO_PEPAR = MCF5282_GPIO_PEPAR_PEPA4;		/* R/W */
	MCF5282_GPIO_PJPAR = MCF5282_GPIO_PJPAR_PJPA3;		/* CS3 */

	/* LSIC configuration defaults */
	lsic->config.version = 1;
	lsic->config.tv_door_open = 5;
	lsic->config.tv_assign = 10;
	lsic->config.relay1_state = LSIC_STATE_DOOR_OPEN;
	lsic->config.relay2_state = LSIC_STATE_ALARM;
	lsic->config.onewire_state = LSIC_STATE_BEEP;

	/* Default ADC config */
	lsic->config.adc_1k_value = 2935;
	lsic->config.inp[0].type = LSIC_INPUT_ALARM;
	lsic->config.inp[0].min = 0x0100;
	lsic->config.inp[0].max = 0x0FFF;

	/* read config from NVRAM */
	lsic_config_read();

	/* Register terminal commands */
	term_find(&cmd_show, "show", NULL);
	term_reg_command(cmd_show, "guard", "Show guard system status", cmd_show_guard);

	cmd_guard = term_reg_command(NULL, "guard", "Guard system commands", NULL);
	term_reg_command(cmd_guard, "assign", "Assign new RFID key", cmd_guard_assign);

	/* Read key table from NVRAM */
	eeprom_read(1, LSIC_NVRAM_KEYADDR, (uint8 *)lsic->keys, sizeof(lsic->keys));
	for (i = 0; i < LSIC_MAX_KEYS; i++) {
		if ( !(lsic->keys[i].flags & LSIC_KEY_VALID) ) {
			lsic->keys[i].flags = 0;
		}
	}
	tmr_gp_blink(100);

	/* Initialize ADC */
	lsic_adc_setup();

	/* Register callbacks */
	mod_set_callbacks(&mod_lsic_func);
}

void lsic_serv_handler(uint32 s_addr, uint16 s_port, uint8 *data, uint16 len)
{
	IF_BUFFER buf;
	struct lsic_net_packet *pkt;
	struct lsic_net_packet resp;
	int resp_len, i, bc;

	/* Check if module is initialized */
	if (!lsic) return;

	/* Check packet size */
	pkt = (struct lsic_net_packet *)data;
	if (len < sizeof(struct lsic_net_header)) return;

	/* Check signature */
	if (pkt->header.sign[0] != 'L') return;
	if (pkt->header.sign[1] != 'S') return;
	if (pkt->header.sign[2] != 'I') return;
	if (pkt->header.sign[3] != 'C') return;

	/* Fill response header */
	memcpy(resp.header.sign, pkt->header.sign, 4);
	resp.header.code = pkt->header.code;
	resp_len = 0;

	/* Command dispatcher */
	switch (pkt->header.code) {
		case LSIC_CMD_STATUS:
			resp.data.r_status.door = lsic->tmr_door_open != 0;
			resp.data.r_status.alarm = lsic->alarm;
			resp.data.r_status.assign = lsic->tmr_rfid_assign != 0;
			resp.data.r_status.last_log_id = lsic->log_last_id;
			resp_len = sizeof(resp.header) + sizeof(resp.data.r_status);
			break;

		case LSIC_CMD_ASSIGN:
			lsic->tmr_rfid_assign = lsic->config.tv_assign;
			break;

		case LSIC_CMD_DOOR_OPEN:
			lsic->tmr_door_open = lsic->config.tv_door_open;
			lsic_log(LSIC_LOG_DOOR_OPENNET, 0, NULL, 0);
			break;

		case LSIC_CMD_KEY_LIST:
			resp.data.r_key_list.start = 0;
			resp.data.r_key_list.count = 0;
			for (i = 0; i < LSIC_MAX_KEYS; i++) {
				/* Max 10 records */
				if (resp.data.r_key_list.count >= 10) break;
				/* Copy used key records */
				if (lsic->keys[i].flags & LSIC_KEY_VALID) {
					memcpy(&resp.data.r_key_list.keys[resp.data.r_key_list.count++],
						&lsic->keys[i], sizeof(lsic_key_rec));
				}
			}
			resp_len = sizeof(resp.header) + sizeof(resp.data.r_key_list);
			break;

		case LSIC_CMD_KEY_UPDATE:
			/* Byte count */
			bc = (pkt->data.c_key_update.key.bitcnt+7) >> 3;
			for (i = 0; i < LSIC_MAX_KEYS; i++) {
				if ( (lsic->keys[i].flags & LSIC_KEY_VALID) &&
					(lsic->keys[i].bitcnt == pkt->data.c_key_update.key.bitcnt) ) {
					/* Compare keys */
					if (memcmp(&lsic->keys[i].bits, &pkt->data.c_key_update.key.bits, bc) == 0) {
						lsic->keys[i].flags = pkt->data.c_key_update.key.flags;
						lsic->keys[i].flags |= LSIC_KEY_SAVE;
					}
				}
			}
			resp_len = sizeof(resp.header);
			break;

		case LSIC_CMD_LOGENTRY:
			resp.data.r_logentry.count = 0;
			/* Find a event with requested ID */
			for (i = 0; i < LSIC_MAX_LOGS; i++) {
				if (lsic->logs[i].id == pkt->data.c_logentry.id) {
					/* record found - copy it to response packet */
					resp.data.r_logentry.count = 1;
					memcpy(&resp.data.r_logentry.entry, &lsic->logs[i], sizeof(lsic_log_rec));
					break;
				}
			}
			resp_len = sizeof(resp.header) + sizeof(resp.data.r_logentry);
			break;

		case LSIC_CMD_CONFIG_GET:
			memcpy(&resp.data.r_config_get.config, &lsic->config, sizeof(lsic_config_t));
			resp_len = sizeof(resp.header) + sizeof(resp.data.r_config_get);
			break;

		case LSIC_CMD_CONFIG_PUT:
			memcpy(&lsic->config, &pkt->data.c_config_put.config, sizeof(lsic_config_t));
			lsic_adc_setup();
			lsic_config_store();
			resp_len = sizeof(resp.header);
			break;

		case LSIC_CMD_INPUTS_GET:
			resp.data.r_inputs_get.adc_1k_value = lsic->config.adc_1k_value;
			lsic_adc_get_values(resp.data.r_inputs_get.inputs);
			resp_len = sizeof(resp.header) + sizeof(resp.data.r_inputs_get);
			break;
	}

	/* Send response */
	if (resp_len) {
		buf.data = (uint8 *)&resp;
		buf.size = resp_len;
		buf.next = NULL;
		udp_send(eeprom.ip_addr, LSIC_CLIENT_PORT, s_addr, s_port, &buf);
	}
}
