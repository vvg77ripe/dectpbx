
#ifndef _SIP_H
#define _SIP_H


#include <ortp/ortp.h>


#define SIP_SERVER_PORT			5060
#define SIP_RTP_PORT_START		16384
#define SIP_RTP_PORT_END		32768

#define SIP_CB_HANGUP			1
#define SIP_CB_RINGING			180
#define SIP_CB_PROGRESS			183
#define SIP_CB_CONNECT			200
#define SIP_CB_BUSY				486

#define CALL_STATE_FREE			0
#define CALL_STATE_DIALING		1
#define CALL_STATE_CONNECTED	2
#define CALL_STATE_HANGUP		3
#define CALL_STATE_PROGRESS		4

#define SIP_DLG_FREE			0
#define SIP_DLG_EARLY			1
#define SIP_DLG_CONFIRMED		2


typedef struct sip_call sip_call_t;
typedef void (*sip_callback_t)(sip_call_t *call, int type, void *ptr);

struct sip_call {
	sip_call_t *	next;			/* Next call structure */

	int				state;			/* Call state */
	sip_callback_t	cbfunc;			/* Callback function pointer */
	void *			cbptr;
	char *			l_user;			/* Local user */
	char *			r_user;			/* Remote user */
	/* SIP dialog */
	char			dlg_state;		/* SIP dialog state */
	char *			call_id;		/* Call-ID */
	char *			l_tag;			/* Local tag */
	int				l_cseq;			/* Local sequence number */
	char *			r_tag;			/* Remote tag */
	int				r_cseq;			/* Remote sequence number */
	/* Voice */
	unsigned short	voice_port;
	unsigned int	send_ts;
	unsigned int	recv_ts;
	RtpSession *	rtp;
};


void sip_init(int socket);
void sip_done();
void sip_server_recv(char *buf, int len, struct sockaddr_in *sa);
void sip_timers();

sip_call_t * sip_call_create();
void sip_call_destroy(sip_call_t *call);
void sip_call_set_callback(sip_call_t *call, sip_callback_t func, void *ptr);
int sip_call_originate(sip_call_t *call, char *from, char *to);
sip_call_t *sip_call_find(char *call_id);
void sip_call_response(sip_call_t *call, int code, char *phrase);


#endif
