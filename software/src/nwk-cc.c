
#include <stdlib.h>

#include <ortp/ortp.h>

#include "dlc.h"
#include "nwk.h"
#include "nwk-cc.h"
#include "g726.h"
#include "sip.h"

#include "iwu-siemens.h"


#define MAX_DIAL_LENGTH		50

#define TSIG_CC_RINGING		TSIG_USER + 0
#define TSIG_CC_BUSY		TSIG_USER + 1
#define TSIG_CC_HANGUP		TSIG_USER + 2
#define TSIG_CC_CONNECT		TSIG_USER + 3
#define TSIG_CC_PROGRESS	TSIG_USER + 4


/* cc_sip_callback()
 *
 * Note that the sip callback function is invoked in the main thread context.
 * Simply set signal to transaction thread and exit.
 */
static void cc_sip_callback(sip_call_t *call, int type, void *ptr)
{
	struct nwk_transaction *trans;

	trans = (struct nwk_transaction *)ptr;
	if (!trans) return;

	switch (type) {
		case SIP_CB_RINGING:
			trans->signal = TSIG_CC_RINGING;
			break;
		case SIP_CB_PROGRESS:
			trans->signal = TSIG_CC_PROGRESS;
			break;
		case SIP_CB_CONNECT:
			trans->signal = TSIG_CC_CONNECT;
			break;
		case SIP_CB_BUSY:
			trans->signal = TSIG_CC_BUSY;
			break;
		case SIP_CB_HANGUP:
			trans->signal = TSIG_CC_HANGUP;
			break;
	}
}

static void cc_uplane_callback(dect_conn_t *mbc, unsigned char *data, int len, void *ptr)
{
	int more;
	sip_call_t *call;

	call = (sip_call_t *)ptr;
	if (!call) return;

	if ((call->state == CALL_STATE_CONNECTED) || (call->state == CALL_STATE_PROGRESS)) {
		/* Calc TX sequence number */
		call->send_ts = mbc->u_seq_counter * 80;
		/* Send and recv RTP */
		rtp_session_send_with_ts(call->rtp, data, len, call->send_ts);
		rtp_session_recv_with_ts(call->rtp, data, len, call->send_ts, &more);
		/* Adjust RX sequence number */
		call->recv_ts += len;
	}

}

static void cc_setup_basic(struct nwk_transaction *trans, pp_info_t *pp, unsigned char *data, int len)
{
	unsigned char cpkt[256];
	unsigned char v[10];
	unsigned char cmd;
	unsigned char *val;
	int i, clen, dlen, ddone, vlen;
	char dialstr[MAX_DIAL_LENGTH];
	sip_call_t *call;

	/* Allocate sip_call_t structure */
	call = sip_call_create();
	if (!call) {
		nwk_reply(trans, DECT_CC_RELEASE_COM);
		nwk_send_reply(trans);
		return;
	}
	sip_call_set_callback(call, &cc_sip_callback, trans);

	/* Empty dial string, wait for dial number */
	dlen = 0;
	ddone = 0;

	/* TEST */
	trans->mbc->u_signal = UPLANE_SIGNAL_BUSY;

	dlc_uplane_connect(trans->mbc, 1, NULL, call);
	nwk_reply(trans, DECT_CC_SETUP_ACK);
	v[0] = 0x80;
	v[1] = 0x88;
	nwk_reply_parm(trans, P_PROGRESS_INDICATOR, 2, v);
	nwk_send_reply(trans);

	while ((clen = nwk_recv_queue(trans, cpkt, 256)) >= 0) {

		switch (trans->signal) {
			/* SIP peer busy - release call */
			case TSIG_CC_BUSY:
				nwk_reply(trans, DECT_CC_RELEASE);
				nwk_reply_parm(trans, P_RELEASE_REASON, RELEASE_USER_BUSY, NULL);
				nwk_send_reply(trans);
				break;

			/* SIP peer hangup - release call */
			case TSIG_CC_HANGUP:
				dlc_uplane_disconnect(trans->mbc);
				nwk_reply(trans, DECT_CC_RELEASE);
				nwk_reply_parm(trans, P_RELEASE_REASON, RELEASE_NORMAL, NULL);
				nwk_send_reply(trans);
				break;

			/* SIP peer connected */
			case TSIG_CC_CONNECT:
				dlc_uplane_connect(trans->mbc, 1, cc_uplane_callback, call);
				trans->mbc->u_signal = UPLANE_SIGNAL_NONE;
				nwk_reply(trans, DECT_CC_CONNECT);
				nwk_send_reply(trans);
				break;

			/* Ringing */
			case TSIG_CC_RINGING:
				trans->mbc->u_signal = UPLANE_SIGNAL_RINGBACK;
				nwk_reply(trans, DECT_CC_ALERTING);
				nwk_send_reply(trans);
				break;
			/* Inband call progress */
			case TSIG_CC_PROGRESS:
				call->state = CALL_STATE_PROGRESS;
				dlc_uplane_connect(trans->mbc, 1, cc_uplane_callback, call);
				trans->mbc->u_signal = UPLANE_SIGNAL_NONE;
				break;
		}

		trans->signal = 0;

		/* Start SIP call */
		if (ddone == 1) {
			ddone = 2;
			dialstr[dlen] = 0;
			trans->mbc->u_signal = UPLANE_SIGNAL_NONE;
			sip_call_originate(call, pp->phone, dialstr);
		}

		if (!clen) continue;

		cmd = cpkt[0];
		switch (cmd) {
			case DECT_CC_INFO:
				/* Dialed digits */
				val = nwk_find_parm(P_MULTI_KEYPAD, &vlen, &cpkt[1], clen-1);
				if (val) {
					if (!ddone) {
						for (i = 0; i < vlen; i++) {
							if (val[i] > 32) dialstr[dlen++] = val[i];
						}
						if (vlen > 1) ddone = 1;
					} else {
						/* Keypad while call in progress */
						/* TODO: DTMF signalling */
					}
				}
				break;

			case DECT_CC_RELEASE:
				nwk_reply(trans, DECT_CC_RELEASE_COM);
				nwk_send_reply(trans);
				dlc_uplane_disconnect(trans->mbc);
				sip_call_destroy(call);
				return;
			case DECT_CC_RELEASE_COM:
				dlc_uplane_disconnect(trans->mbc);
				sip_call_destroy(call);
				return;
		}
	}

	dlc_uplane_disconnect(trans->mbc);
	sip_call_destroy(call);
}

static void cc_setup_int(struct nwk_transaction *trans, pp_info_t *pp, unsigned char *data, int len)
{
	unsigned char cpkt[256];
	unsigned char cmd;
	int clen, tmr;

	while ((clen = nwk_recv_queue(trans, cpkt, 256)) >= 0) {

		tmr++;
		if (tmr > 5) {
			tmr = 0;
			nwk_reply(trans, DECT_CC_INFO);
			iwu_siemens(IWU_LOCATE_ACCEPT, trans, NULL, data, len);
			nwk_send_reply(trans);
		}

		if (!clen) continue;

		cmd = cpkt[0];
		switch (cmd) {
			case DECT_CC_RELEASE:
				nwk_reply(trans, DECT_CC_RELEASE_COM);
				nwk_send_reply(trans);
				return;
			case DECT_CC_RELEASE_COM:
				return;
		}

	}
}

void cc_setup_incoming(nwk_trans_t *trans, pp_info_t *pp, int type, void *ptr)
{
	unsigned char v[50];
	sip_call_t *call;
	unsigned char cpkt[256];
	unsigned char cmd;
	int clen;

	if (!ptr) return;

	call = (sip_call_t *)ptr;

	if (type == PAGE_CALLBACK_FAIL) {
		/* Portable Part unavailable */
		sip_call_response(call, 486, NULL);
		sip_call_destroy(call);
		return;
	}

	trans->tid = 0x83;
	log_print(0, "===== Incoming Call Control Transaction Started\n");
	trans->mbc->u_signal = UPLANE_SIGNAL_NONE;
	sip_call_set_callback(call, &cc_sip_callback, trans);

	nwk_reply(trans, DECT_CC_SETUP);
	nwk_reply_parm(trans, P_PORTABLE_IDENTITY, pp->ipui_len, pp->ipui);
	/* Fixed Identity */
	v[0] = 0xA0; /* Type = PARK */
	v[1] = 0xA0; /* Len = 32bits */
	v[2] = 0x15;
	v[3] = 0x24;
	v[4] = 0x20;
	v[5] = 0x01;
	nwk_reply_parm(trans, P_FIXED_IDENTITY, 6, v);
	nwk_reply_parm(trans, P_BASIC_SERVICE, 0x80, NULL);
	/* Calling party number */
	v[0] = 0x81;	/* E.164 number */
	snprintf(&v[1], 49, "%s", call->r_user);
	strtok(&v[1], "@");
	nwk_reply_parm(trans, P_CALLING_PARTY_NUMBER, strlen(&v[1])+1, v);
	/* Signal - External call */
	nwk_reply_parm(trans, P_SIGNAL, 0x41, NULL);
	nwk_send_command(trans, DECT_PROTO_CC);

	while ((clen = nwk_recv_queue(trans, cpkt, 256)) >= 0) {

		switch (trans->signal) {
			/* SIP peer hangup - release call */
			case TSIG_CC_HANGUP:
				dlc_uplane_disconnect(trans->mbc);
				nwk_reply(trans, DECT_CC_RELEASE);
				nwk_reply_parm(trans, P_RELEASE_REASON, RELEASE_NORMAL, NULL);
				nwk_send_reply(trans);
				break;
		}

		trans->signal = 0;
		if (!clen) continue;

		cmd = cpkt[0];
		switch (cmd) {
			case DECT_CC_ALERTING:
				sip_call_response(call, 180, NULL);
				break;

			case DECT_CC_CONNECT:
				sip_call_response(call, 200, NULL);
				dlc_uplane_connect(trans->mbc, 1, cc_uplane_callback, call);
				nwk_reply(trans, DECT_CC_CONNECT_ACK);
				nwk_send_reply(trans);
				break;

			case DECT_CC_RELEASE:
				nwk_reply(trans, DECT_CC_RELEASE_COM);
				nwk_send_reply(trans);
				dlc_uplane_disconnect(trans->mbc);
				sip_call_destroy(call);
				return;
			case DECT_CC_RELEASE_COM:
				dlc_uplane_disconnect(trans->mbc);
				sip_call_destroy(call);
				return;
		}
	}

	dlc_uplane_disconnect(trans->mbc);
	sip_call_destroy(call);
	log_print(0, "===== Incoming Call Control Transaction Ended\n");
}

char * cc_dump_cmd(unsigned char cmd)
{
	switch (cmd) {
		case DECT_CC_SETUP:
			return "CC-SETUP";
		case DECT_CC_SETUP_ACK:
			return "CC-SETUP-ACK";
		case DECT_CC_ALERTING:
			return "CC-ALERTING";
		case DECT_CC_CALL_PROC:
			return "CC-CALL-PROC";
		case DECT_CC_CONNECT:
			return "CC-CONNECT";
		case DECT_CC_CONNECT_ACK:
			return "CC-CONNECT-ACK";
		case DECT_CC_RELEASE:
			return "CC-RELEASE";
		case DECT_CC_RELEASE_COM:
			return "CC-RELEASE-COM";

		case DECT_CC_INFO:
			return "CC-INFO";
		case DECT_CC_FACILITY:
			return "FACILITY";
	}
	return "<UNKNOWN>";
}

void cc_command(struct nwk_transaction *trans, unsigned char cmd, unsigned char *data, int len)
{
	unsigned char *val;
	int vlen;
	unsigned char bserv;
	pp_info_t *pp;

	if ( (cmd == DECT_CC_RELEASE) || (cmd == DECT_CC_RELEASE_COM) ) {
		/* Ingore unwanted release messages */
		return;
	}

	if (cmd != DECT_CC_SETUP) {
		nwk_reply(trans, DECT_CC_RELEASE_COM);
		nwk_reply_parm(trans, P_RELEASE_REASON, RELEASE_UNKNOWN_TRANSACTION, NULL);
		nwk_send_reply(trans);
		return;
	}

	/* Now we has received CC-SETUP for a new connection
	 *
	 */
	log_print(0, "===== Call Control Transaction Started\n");

	/* Service type check */
	val = nwk_find_parm(P_BASIC_SERVICE, &vlen, data, len);
	if (!val) {
		nwk_reply(trans, DECT_CC_RELEASE_COM);
		nwk_reply_parm(trans, P_RELEASE_REASON, RELEASE_MANDATORY_MISSING, NULL);
		nwk_send_reply(trans);
		return;
	}
	bserv = val[0];

	/* Portable identity */
	val = nwk_find_parm(P_PORTABLE_IDENTITY, &vlen, data, len);
	if (!val) {
		nwk_reply(trans, DECT_CC_RELEASE_COM);
		nwk_reply_parm(trans, P_RELEASE_REASON, RELEASE_MANDATORY_MISSING, NULL);
		nwk_send_reply(trans);
		return;
	}
	pp = pp_find(trans, val, vlen);
	if (!pp) {
		nwk_reply(trans, DECT_CC_RELEASE_COM);
		nwk_reply_parm(trans, P_RELEASE_REASON, RELEASE_MANDATORY_MISSING, NULL);
		nwk_send_reply(trans);
		return;
	}

	/* Basic speech setup */
	switch (bserv) {
		case 0x80:
			cc_setup_basic(trans, pp, data, len);
			break;
		case 0x90:
			cc_setup_int(trans, pp, data, len);
			break;
		default:
			nwk_reply(trans, DECT_CC_RELEASE_COM);
			nwk_reply_parm(trans, P_RELEASE_REASON, RELEASE_NOT_IMPLEMENTED, NULL);
			nwk_send_reply(trans);
			break;
	}

	pp_free(pp);

	log_print(0, "===== Call Control Transaction Ended\n");
	dlc_uplane_disconnect(trans->mbc);
}
