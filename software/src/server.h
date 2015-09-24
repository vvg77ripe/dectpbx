
#ifndef _SERVER_H
#define _SERVER_H

#include <netinet/in.h>

#ifndef PACKED
#define PACKED __attribute__((__packed__))
#endif


#define DECT_SERVER_PORT	2148
#define DECT_CLIENT_PORT	2149

#define DECT_MAX_CLIENTS	16

#define DECT_MSG_PING		0
#define DECT_MSG_LAPC_DATA	1
#define DECT_MSG_SYSINFO	2
#define DECT_MSG_PAGING		3
#define DECT_MSG_VOICE		10


struct dect_packet {
	char			sign[2];	/* Packet signature */
	unsigned int	fpid;		/* System FP ID */
	unsigned char	rfpi[6];	/* Radio Fixed Part Identity */
	unsigned char	mac[16];	/* Message Authentication Code */

	unsigned short	type;		/* Message Type */
	unsigned short	len;		/* Message Length */
} PACKED;

struct dect_packet_header {
	unsigned short	type;		/* Message Type */
	unsigned short	len;		/* Message Length */
} PACKED;

struct msg_lapc_data {
	unsigned int	pmid;
	unsigned char	ecn;
	unsigned char	uplane;
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

typedef struct dect_client {
	unsigned int	fpid;		/* System FP ID */
	unsigned int	last_active;/* Last packet timestamp */
	unsigned int	ipad;		/* Client IP address */
	unsigned char	rfpi[6];	/* RFPI */
	unsigned char	mbc_count;	/* Connection count */
} dect_client_t;


void dect_server_init(int socket);
void dect_server_done();
void dect_server_recv(char *buf, int len, struct sockaddr_in *sa);
void dect_server_send(dect_client_t *client, char *buf, int len);

void dect_server_send_lapc(dect_client_t *client, void *mbc, char *data, int len);
void dect_server_send_voice(dect_client_t *client, void *mbc, char *data, int len);
void dect_server_send_paging(dect_client_t *client, char *data, int len);


#endif
