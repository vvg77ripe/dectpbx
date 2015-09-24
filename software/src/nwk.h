
#ifndef _NWK_H
#define _NWK_H

#include <pthread.h>

#include "dlc.h"
#include "g726.h"


#define DECT_NWK_MAX_REQUEST		63
#define DECT_NWK_MAX_REPLY			63

/* Transaction Signals */
#define TSIG_TERMINATE				1
#define TSIG_USER					100

/* Protocol IDs */
#define DECT_PROTO_LCE				0
#define DECT_PROTO_CC				3
#define DECT_PROTO_CISS				4
#define DECT_PROTO_MM				5
#define DECT_PROTO_CLMS				6
#define DECT_PROTO_COMS				7

/* LCE messages */
#define DECT_LCE_PAGE_RESPONSE		0x71
#define DECT_LCE_PAGE_REJECT		0x72

/* IWU types */
#define IWU_TYPE_SIEMENS			2
#define IWU_TYPE_PANASONIC			596

/* IWU callback types */
#define IWU_LOCATE_ACCEPT			1
#define IWU_LOCATE_ACCEPT_PARM		2

/* Message parameters */
#define P_PORTABLE_IDENTITY			0x05
#define P_FIXED_IDENTITY			0x06
#define P_LOCATION_AREA				0x07
#define P_PROGRESS_INDICATOR		0x1E
#define P_MULTI_KEYPAD				0x2C
#define P_REJECT_REASON				0x60
#define P_TERMINAL_CAPABILITY		0x63
#define P_CALLING_PARTY_NUMBER		0x6C
#define P_IWU_TO_IWU				0x77
#define P_PROPRIETARY				0x7B

#define P_BASIC_SERVICE				0xE0
#define P_RELEASE_REASON			0xE2
#define P_SIGNAL					0xE4

/* Release reason codes */
#define RELEASE_NORMAL				0x00
#define RELEASE_UNKNOWN_TRANSACTION	0x02
#define RELEASE_MANDATORY_MISSING	0x03
#define RELEASE_NOT_IMPLEMENTED		0x06
#define RELEASE_USER_DETACHED		0x10
#define RELEASE_USER_BUSY			0x14
#define RELEASE_OVERLOAD			0x31
#define RELEASE_IWU_CONGESTION		0x34

/* Reject reason codes */
#define REJECT_IPUI_UNKNOWN			0x02
#define REJECT_IPUI_NOT_ACCEPTED	0x06
#define REJECT_NO_RESOURCES			0x2F
#define REJECT_INVALID_MESSAGE		0x5F
#define REJECT_INFORMATION_ELEMENT	0x60


#define NWK_QUEUE_LEN				2

typedef struct nwk_queue {
	unsigned short	len;
	unsigned char *	data;
} nwk_queue_t;

typedef struct nwk_transaction nwk_trans_t;

struct nwk_transaction {
	nwk_trans_t *	next;						/* Next transaction pointer */

	unsigned char	tid;						/* Transaction ID */
	unsigned char	client_tid;					/* Client Transaction ID */
	pthread_t		thread_id;					/* Transaction Thread ID */
	dect_conn_t *	mbc;						/* Connection pointer */
	void *			sql;						/* SQL server connection */
	char			signal;						/* Signal value */
	/* Input queues */
	nwk_queue_t		inq_c[NWK_QUEUE_LEN];		/* Input command queue */
	nwk_queue_t		inq_r[NWK_QUEUE_LEN];		/* Input reply queue */
	/* Request/reply buffers */
	unsigned short	req_len;
	unsigned char	req[DECT_NWK_MAX_REQUEST];
	unsigned short	rep_len;
	unsigned char	rep[DECT_NWK_MAX_REPLY];
};

typedef struct pp_info {
	int				tpui;
	unsigned short	iwu_type;
	char *			phone;
	unsigned char	ipui_len;
	unsigned char	ipui[64];
} pp_info_t;


#define PAGE_CALLBACK_OK	1
#define PAGE_CALLBACK_FAIL	2

typedef void (*page_callback_t)(nwk_trans_t *trans, pp_info_t *pp, int type, void *ptr);
typedef struct nwk_page nwk_page_t;

struct nwk_page {
	nwk_page_t *	next;
	page_callback_t	func;
	void *			func_ptr;
	pp_info_t *		pp;
	unsigned int	page_time;
	char			page_count;
};


void nwk_init();
void nwk_recv(dect_conn_t *mbc, unsigned char *data, int len);
void nwk_reply_parm(struct nwk_transaction *trans, unsigned char code,
					unsigned char len, unsigned char *val);
void nwk_reply(struct nwk_transaction *trans, unsigned char code);

int nwk_send(struct nwk_transaction *trans, unsigned char *data, int len);
int nwk_send_command(struct nwk_transaction *trans, unsigned int tid);
int nwk_send_reply(struct nwk_transaction *trans);

int nwk_recv_queue(struct nwk_transaction *trans, unsigned char *data, int len);

unsigned char * nwk_find_parm(unsigned char id, int *plen, unsigned char *data, int len);


pp_info_t *pp_find(struct nwk_transaction *trans, unsigned char *ipui, int len);
void pp_free(pp_info_t *pp);
int pp_iwu(int type, struct nwk_transaction *trans, pp_info_t *pp, unsigned char *data, int len);

void page_start(pp_info_t *pp, page_callback_t func, void *ptr);
void page_timers();


#endif
