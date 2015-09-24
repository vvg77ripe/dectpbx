
#include <mcf5282.h>
#include <stdio.h>
#include <string.h>
#include "config.h"

#include "eeprom.h"
#include "network/udp.h"
#include "term/terminal.h"

#include "tftp.h"


static tftp_client *tftp_list;


static void tftp_send_ack(tftp_client *tftp)
{
	uint8		buf[512];
	fifo_buffer	out;
	IF_BUFFER	ack;

	out.buf = buf;
	out.length = 512;
	out.start = 0;
	out.stop = 2;

	if (tftp->block == 0) {
		/* RRQ */
		buf[0] = 0;
		buf[1] = TFTP_CMD_RRQ;
		bprintf(&out, "%s", tftp->filename);
		fifo_write(&out, buf, 1);
		bprintf(&out, "netascii");
		fifo_write(&out, buf, 1);
	} else {
		/* ACK */
		buf[0] = 0;
		buf[1] = TFTP_CMD_ACK;
		buf[2] = tftp->block >> 8;
		buf[3] = tftp->block & 0xFF;
		out.stop += 2;
	}

	ack.data = buf;
	ack.size = out.stop;
	ack.next = NULL;
	udp_send(0, tftp->c_port, tftp->s_addr, tftp->s_port, &ack);
}

static void cmd_ip_tftp_server(struct terminal *term, int reason)
{
	uint32 ip;

	if (reason == TERM_RSN_EXEC) {
		ip = term_get_ip(term);
		if (!ip) {
			bprintf(term->out, "Bad IP address.\r\n");
			return;
		}
		eeprom.tftp_server = ip;
	}
}

void tftp_init()
{
	struct term_command *cmd_ip, *cmd_ip_tftp;

	tftp_list = NULL;

	/* Register terminal commands */
	term_find(&cmd_ip, "ip", NULL);
	cmd_ip_tftp = term_reg_command(cmd_ip, "tftp", "Configure TFTP client", NULL);
	term_reg_command(cmd_ip_tftp, "server", "Set address of default TFTP server", cmd_ip_tftp_server);
}

int tftp_start(tftp_client *tftp, char *file)
{
	/* Default server address */
	if (!tftp->s_addr) tftp->s_addr = eeprom.tftp_server;

	/* Client port */
	tftp->c_port = UDPC_TFTP_START;
	tftp->s_port = UDP_PORT_TFTP;

	/* Start */
	tftp->filename = file;
	tftp->block = 0;

	/* Add to client chain */
	tftp->next = tftp_list;
	tftp_list = tftp;

	/* Send RRQ */
	tftp_send_ack(tftp);
	return 0;
}

void tftp_handler(uint16 sport, uint16 dport, uint8 *data, uint16 size)
{
	tftp_client *tftp;
	uint16		cmd, block;

	if (size < 4) return;
	cmd = (data[0] << 8) + data[1];

	tftp = tftp_list;
	while (tftp) {
		if (tftp->c_port == dport) {
			if (cmd == TFTP_CMD_DATA) {
				/* Data packet */
				block = (data[2] << 8) + data[3];
				if (tftp->block != block) {
					tftp->block = block;
					if (tftp->cbfunc) tftp->cbfunc(tftp->block, &data[4], size-4);
				}
				tftp->s_port = sport;
				tftp_send_ack(tftp);
			}
			return;
		}
		tftp = tftp->next;
	}
}
