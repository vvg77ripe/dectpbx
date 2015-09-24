
#ifndef _DLC_H
#define _DLC_H

#include "server.h"
#include "g726.h"


#define DECT_MAX_FRAME			70

#define DLC_ADDR_NLF			0x80
#define DLC_ADDR_CR				0x02

#define DLC_LLN_CLASS_U			0
#define DLC_LLN_CLASS_A			1

#define UPLANE_SIGNAL_NONE		0
#define UPLANE_SIGNAL_RINGBACK	1
#define UPLANE_SIGNAL_BUSY		2


typedef struct dect_dlc_clsa {
	char			vs;
	char			va;
	char			vr;
	unsigned char	spkt[DECT_MAX_FRAME];
	unsigned char	spkt_len;
} dect_dlca_t;


typedef struct dect_connection dect_conn_t;
typedef void (*dect_uplane_cb)(dect_conn_t *mbc, unsigned char *data, int len, void *ptr);

struct dect_connection {
	dect_conn_t *	next;

	unsigned int	pmid;
	unsigned char	ecn;
	unsigned int	fpid;
	/* U-Plane */
	int					u_type;
	dect_uplane_cb		u_callback;
	void *				u_ptr;
	unsigned short		u_seq;
	unsigned int		u_seq_counter;
	struct g726_state	g726_enc;
	struct g726_state	g726_dec;
	int					u_signal;
	int					u_sig_counter;
	/* refs */
	dect_client_t *	client;
	dect_dlca_t		dlc_a;
};


void dlc_init();
void dlc_done();
dect_conn_t *dect_find_connection(unsigned int pmid, unsigned char ecn);

void dlc_send_data(dect_client_t *client, dect_conn_t *mbc, char lln,
						  unsigned char *data, int len);
void dlc_recv(dect_client_t *client, unsigned int pmid, unsigned char ecn, unsigned char *pkt, int len);

int dlc_uplane_connect(dect_conn_t *mbc, unsigned char type, dect_uplane_cb func, void *ptr);
void dlc_uplane_disconnect(dect_conn_t *mbc);

#endif
