
#ifndef _NETWORK_TFTP_H
#define _NETWORK_TFTP_H

#define TFTP_CMD_RRQ	1
#define TFTP_CMD_WRQ	2
#define TFTP_CMD_DATA	3
#define TFTP_CMD_ACK	4
#define TFTP_CMD_ERROR	5


typedef void (*tftp_callback)(int code, uint8 *data, int len);

typedef struct tftpc {
	uint32			s_addr;
	uint16			s_port;
	uint16			c_port;
	uint16			block;
	char			* filename;
	struct tftpc	* next;
	tftp_callback	cbfunc;
} tftp_client;


void tftp_init(void);
int tftp_start(tftp_client *tftp, char *file);
void tftp_handler(uint16 sport, uint16 dport, uint8 *data, uint16 size);

#endif
