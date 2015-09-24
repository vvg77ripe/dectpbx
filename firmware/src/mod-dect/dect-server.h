
#ifndef _MOD_DECT_DECT_SERVER_H
#define _MOD_DECT_DECT_SERVER_H

#define DECT_SERVER_PORT	2148
#define DECT_CLIENT_PORT	2149

#define DECT_MSG_PING		0
#define DECT_MSG_LAPC_DATA	1
#define DECT_MSG_SYSINFO	2
#define DECT_MSG_PAGING		3
#define DECT_MSG_VOICE		10

#define DECT_TMR_PING		500


struct dect_packet {
	char			sign[2];	/* Packet signature */
	unsigned int	fpid;		/* System FP ID */
	unsigned char	rfpi[6];	/* Radio Fixed Part Identity */
	unsigned char	mac[16];	/* Message Authentication Code */

	unsigned short	type;		/* Message Type */
	unsigned short	len;		/* Message Length */
} PACKED;

typedef struct dect_buffer {
	uint8 *			packet;
	uint16			size;
} dect_buf_t;

struct msg_lapc_data {
	unsigned int	pmid;
	unsigned char	ecn;
	unsigned char	uplane;
} PACKED;

struct msg_paging {
	unsigned char	msg[3];
} PACKED;

struct msg_sysinfo {
	unsigned int	v_mbclist;	/* Connection table list version */
	unsigned char	mbc_count;	/* Connection count */
	unsigned short	hlcap;		/* Higher layer capabilities */
} PACKED;

struct msg_voice_data {
	unsigned int	pmid;
	unsigned char	ecn;
	unsigned short	seq;
} PACKED;


void dect_serv_handler(uint32 server_ip, uint8 *data, uint16 len);
void dect_serv_send(uint8 *data, uint16 len);

void dect_serv_send_ping(void);
void dect_serv_send_lapc(uint32 pmid, uint8 ecn, uint8 *data, uint8 len);
void dect_serv_send_voice(uint32 pmid, uint8 ecn, uint8 *data, uint8 len);

void dect_serv_buffer_add(dect_buf_t *buffer, uint16 cmd, uint16 size, void *data);

#endif
