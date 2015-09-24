
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <osip2/osip.h>
#include <osip2/osip_dialog.h>
#include <osipparser2/sdp_message.h>
#include <ortp/ortp.h>

#include "sip.h"
#include "nwk.h"
#include "nwk-cc.h"
#include "cfgfile.h"
#include "terminal.h"

static int s_sip;
static osip_t *osip;
static sip_call_t *sip_call_list;

static char *	cfg_proxy;
static char *	cfg_bindip;
static int		cfg_bindport;


static void sip_send_ack(osip_message_t *resp);


static unsigned int random_number()
{
	return osip_build_random_number();
}

static void sip_log_message(char *dir, osip_message_t *msg)
{
	char buf[200];
	char *tmp;

	snprintf(buf, 200, "[%s => %s]", msg->from->url->username, msg->to->url->username);

	if (MSG_IS_REQUEST(msg)) {
		log_print(0, "SIP %s: %s %s\n", dir, buf, msg->sip_method);
	} else {
		log_print(0, "SIP %s: %s %u %s\n", dir, buf, msg->status_code, msg->reason_phrase);
	}

	if (0) {
		/* From */
		osip_from_to_str(msg->from, &tmp);
		log_print(0, "  From: %s\n", tmp);
		free(tmp);
		/* To */
		osip_from_to_str(msg->to, &tmp);
		log_print(0, "  To: %s\n", tmp);
		free(tmp);
		/* Call-ID */
		osip_call_id_to_str(msg->call_id, &tmp);
		log_print(0, "  CSeq: %s\n", tmp);
		free(tmp);
	}
}

static void sip_default_headers(osip_message_t *msg)
{
	/* Allowed methods */
	osip_message_set_allow(msg, "INVITE");
	osip_message_set_allow(msg, "ACK");
	osip_message_set_allow(msg, "CANCEL");
	osip_message_set_allow(msg, "BYE");
	osip_message_set_allow(msg, "OPTIONS");
}

static void sip_default_response(osip_message_t **msg, int status, osip_message_t *req,
								 char *body)
{
	int pos;
	osip_via_t *via1, *via2;
	osip_message_t *resp;

	*msg = NULL;
	if (!req) return;

	if (osip_message_init(&resp)) return;

	resp->sip_version = osip_strdup("SIP/2.0");
	osip_message_set_status_code(resp, status);
	resp->reason_phrase = osip_strdup(osip_message_get_reason(status));
	resp->req_uri = NULL;
	resp->sip_method = NULL;

	osip_to_clone(req->to, &resp->to);
	osip_from_clone(req->from, &resp->from);
	osip_call_id_clone(req->call_id, &resp->call_id);
	osip_cseq_clone(req->cseq, &resp->cseq);

	pos = 0;
	while (!osip_list_eol(req->vias, pos)) {
		via1 = (osip_via_t *)osip_list_get(req->vias, pos);
		osip_via_clone(via1, &via2);
		osip_list_add(resp->vias, via2, -1);
		pos++;
	}

	if (body) {
		osip_message_set_body(resp, body);
		osip_message_set_content_type(resp, "application/sdp");
	}

	sip_default_headers(resp);

	*msg = resp;
}

static sdp_message_t * sip_get_sdp(osip_message_t *msg)
{
	sdp_message_t *sdp;
	osip_body_t *body;
	int pos;

	pos = 0;
	while (!osip_list_eol(msg->bodies, pos)) {
		body = (osip_body_t *)osip_list_get(msg->bodies, pos);
		pos++;

		sdp_message_init(&sdp);
		if (!sdp_message_parse(sdp, body->body)) return sdp;
		sdp_message_free(sdp);
	}

	return NULL;
}

static unsigned short sip_get_rtp_port()
{
	unsigned short port;
	sip_call_t *call;
	char *used;

	used = malloc(65536);
	if (!used) return 0;
	memset(used, 0, 65536);

	for (call = sip_call_list; call; call = call->next) {
		used[call->voice_port] = 1;
	}

	for (port = SIP_RTP_PORT_START; port < SIP_RTP_PORT_END; port += 2) {
		if (!used[port]) {
			free(used);
			return port;
		}
	}

	free(used);
	return 0;
}

static int sip_check_sdp(sip_call_t *call, osip_message_t *msg)
{
	sdp_message_t *sdp;
	sdp_media_t *media;
	int pos;

	/* Get sdp body */
	sdp = sip_get_sdp(msg);
	if (!sdp) return 0;

	/* Find audio stream */
	pos = 0;
	media = NULL;
	while (!osip_list_eol(sdp->m_medias, pos)) {
		media = (sdp_media_t *)osip_list_get(sdp->m_medias, pos);
		pos++;
		if (!strcasecmp(media->m_media, "audio")) break;
		media = NULL;
	}
	if (media) {
		log_print(0, "SIP: Starting RTP session to %s:%s\n", sdp->o_addr, media->m_port);
		rtp_session_set_remote_addr(call->rtp, sdp->o_addr, atoi(media->m_port));
		rtp_session_set_payload_type(call->rtp, 8);
	}

	sdp_message_free(sdp);

	return 1;
}

static void sip_check_remote_tag(sip_call_t *call, osip_from_t *from)
{
	osip_generic_param_t *tag;

	if (!call->r_tag) {
		osip_from_get_tag(from, &tag);
		if (tag) {
			call->r_tag = strdup(tag->gvalue);
		}
	}
}

static void sip_check_local_tag(sip_call_t *call)
{
	char tmp[50];

	if (!call->l_tag) {
		snprintf(tmp, 50, "%u", random_number());
		call->l_tag = strdup(tmp);
	}
}

static void cb_kill_transaction(int type, osip_transaction_t *trans)
{
	osip_remove_transaction(osip, trans);
}

static void cb_message(int type, osip_transaction_t *trans, osip_message_t *msg)
{
	sip_call_t *call;
	pp_info_t *pp;
	osip_generic_param_t *tag;
	osip_message_t *answer;
	osip_event_t *revent;
	char tmp[256];

	call = (sip_call_t *)osip_transaction_get_your_instance(trans);

	switch (type) {
		case OSIP_IST_INVITE_RECEIVED:
			/* Find Portable Part */
			snprintf(tmp, 256, "%s@%s", msg->to->url->username, msg->to->url->host);
			pp = pp_find(NULL, tmp, 0);
			if (!pp) {
				sip_default_response(&answer, 404, msg, NULL);
				revent = osip_new_outgoing_sipmessage(answer);
				revent->transactionid = trans->transactionid;
				osip_transaction_add_event(trans, revent);
				return;
			}
			/* Create SIP call */
			call = sip_call_create();
			snprintf(tmp, 256, "%s@%s", msg->to->url->username, msg->to->url->host);
			call->l_user = strdup(tmp);
			snprintf(tmp, 256, "%s@%s", msg->from->url->username, msg->from->url->host);
			call->r_user = strdup(tmp);
			osip_call_id_to_str(msg->call_id, &call->call_id);
			osip_transaction_set_your_instance(trans, call);
			/* Get sdp body */
			if (!sip_check_sdp(call, msg)) {
				log_print(0, "SIP: Cannot find any sdp body in the INVITE\n");
				pp_free(pp);
				sip_call_destroy(call);
				return;
			}
			/* Create sip dialog */
			call->dlg_state = SIP_DLG_CONFIRMED;
			sip_check_remote_tag(call, msg->from);
			/* Start paging */
			page_start(pp, cc_setup_incoming, call);
			return;

		case OSIP_ICT_STATUS_1XX_RECEIVED:
			if (call) {
				/* Start RTP, if present */
				sip_check_sdp(call, msg);

				/* Create sip dialog */
				if (msg->status_code != 100) {
					call->dlg_state = SIP_DLG_EARLY;
					sip_check_remote_tag(call, msg->to);
				}
				/* inform upper layer */
				if (call->cbfunc) call->cbfunc(call, msg->status_code, call->cbptr);
			}
			return;

		case OSIP_ICT_STATUS_2XX_RECEIVED:
			log_print(0, "SIP: Call answered\n");
			if (call) {
				if (!sip_check_sdp(call, msg)) return;

				/* Send ACK */
				sip_send_ack(msg);

				/* Update dialog state */
				call->dlg_state = SIP_DLG_CONFIRMED;
				sip_check_remote_tag(call, msg->to);

				/* inform upper layer */
				if (call->state != CALL_STATE_CONNECTED) {
					call->state = CALL_STATE_CONNECTED;
					if (call->cbfunc) call->cbfunc(call, SIP_CB_CONNECT, call->cbptr);
				}
			}
			return;

		case OSIP_ICT_STATUS_3XX_RECEIVED:
		case OSIP_ICT_STATUS_4XX_RECEIVED:
		case OSIP_ICT_STATUS_5XX_RECEIVED:
		case OSIP_ICT_STATUS_6XX_RECEIVED:
			if (call) {
				if (call->cbfunc) call->cbfunc(call, SIP_CB_BUSY, call->cbptr);
			}
			return;
	}
}

static int cb_send_message(osip_transaction_t *trans, osip_message_t *msg,
							char *host, int port, int out_socket)
{
	struct sockaddr_in sa;
	char *data;
	int len;

	if (host == NULL) {
		host = msg->req_uri->host;
		if (msg->req_uri->port) {
			port = osip_atoi(msg->req_uri->port);
		} else {
			port = 5060;
		}
	}

	memset(&sa, 0, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = inet_addr(host);
	if (sa.sin_addr.s_addr == INADDR_NONE) {
		/* set default ip address */
		sa.sin_addr.s_addr = inet_addr(cfg_proxy);
	}
	sa.sin_port = htons(port);

	if ( !osip_message_to_str(msg, &data) ) {
		sip_log_message("TX", msg);
		len = strlen(data);
		sendto(s_sip, data, len, 0, (struct sockaddr *)&sa, sizeof(sa));
		free(data);
	}

	return 0;
}

static void sip_cancel_request(osip_message_t *creq)
{
	osip_message_t *req;
	osip_via_t *via1, *via2;
	osip_transaction_t *trans;
	osip_event_t *event;

	if (!creq) return;

	if (osip_message_init(&req)) return;
	do {
		/* Request-Line */
		osip_message_set_method(req, osip_strdup("CANCEL"));
		osip_message_set_version(req, osip_strdup("SIP/2.0"));
		osip_message_set_status_code(req, 0);
		osip_message_set_reason_phrase(req, NULL);

		if (osip_uri_clone(creq->req_uri, &req->req_uri)) break;

		/* Clone headers */
		if (osip_from_clone(creq->from, &req->from)) break;
		if (osip_to_clone(creq->to, &req->to)) break;
		if (osip_call_id_clone(creq->call_id, &req->call_id)) break;

		/* CSeq */
		if (osip_cseq_clone(creq->cseq, &req->cseq)) break;
		osip_free(req->cseq->method);
		req->cseq->method = osip_strdup("CANCEL");

		/* VIA */
		if (osip_message_get_via(creq, 0, &via1)) break;
		if (osip_via_clone(via1, &via2)) break;
		osip_list_add(req->vias, via2, -1);

		/* Defaults */
		osip_message_set_max_forwards(req, "70");
		sip_default_headers(req);

		/* Create Client Transaction */
		if (osip_transaction_init(&trans, NICT, osip, req)) break;

		event = osip_new_outgoing_sipmessage(req);
		event->transactionid = trans->transactionid;
		osip_transaction_add_event(trans, event);
		return;

	} while (0);

	osip_message_free(req);
}

static void sip_send_ack(osip_message_t *resp)
{
	osip_message_t *ack;
	char tmp[1024];

	if (osip_message_init(&ack)) return;

	do {
		/* Request-Line */
		ack->sip_method = osip_strdup("ACK");
		ack->sip_version = osip_strdup("SIP/2.0");
		ack->status_code = 0;
		ack->reason_phrase = NULL;

		/* URI */
		if (osip_uri_clone(resp->to->url, &ack->req_uri)) break;

		/* From/To */
		if (osip_from_clone(resp->from, &ack->from)) break;
		if (osip_to_clone(resp->to, &ack->to)) break;

		/* Call-ID */
		if (osip_call_id_clone(resp->call_id, &ack->call_id)) break;

		/* CSeq */
		if (osip_cseq_clone(resp->cseq, &ack->cseq)) break;
		osip_free(ack->cseq->method);
		ack->cseq->method = osip_strdup("ACK");

		/* VIA */
		snprintf(tmp, 1024, "SIP/2.0/UDP %s:%u;branch=z9hG4bK%u",
			cfg_bindip, cfg_bindport, random_number());
		osip_message_set_via(ack, tmp);

		/* Contact */
		snprintf(tmp, 1024, "<sip:%s@%s:%u>", ack->from->url->username,
			cfg_bindip, cfg_bindport);
		osip_message_set_contact(ack, tmp);

		/* Defaults */
		osip_message_set_max_forwards(ack, "70");
		sip_default_headers(ack);

		/* Send ACK */
		cb_send_message(NULL, ack, NULL, 0, -1);
	} while (0);

	osip_message_free(ack);
}

static void sip_send_bye(sip_call_t *call)
{
	osip_message_t *req;
	osip_call_id_t *call_id;
	osip_cseq_t *cseq;
	osip_transaction_t *trans;
	osip_event_t *event;
	char tmp[1024];

	if (!call) return;

	if (osip_message_init(&req)) return;
	do {
		/* Request-Line */
		osip_message_set_method(req, osip_strdup("BYE"));
		osip_message_set_version(req, osip_strdup("SIP/2.0"));
		osip_message_set_status_code(req, 0);
		osip_message_set_reason_phrase(req, NULL);

		/* To */
		snprintf(tmp, 1024, "sip:%s", call->r_user);
		if (osip_message_set_to(req, osip_strdup(tmp))) break;
		if (call->r_tag) osip_to_set_tag(req->to, osip_strdup(call->r_tag));
		osip_uri_clone(req->to->url, &req->req_uri);
		/* From */
		snprintf(tmp, 1024, "sip:%s", call->l_user);
		if (osip_message_set_from(req, osip_strdup(tmp))) break;
		if (call->l_tag) osip_from_set_tag(req->from, osip_strdup(call->l_tag));

		/* VIA */
		snprintf(tmp, 1024, "SIP/2.0/UDP %s:%u;branch=z9hG4bK%u",
			cfg_bindip, cfg_bindport, random_number());
		osip_message_set_via(req, tmp);

		/* Call-ID */
		if (osip_call_id_init(&call_id)) break;
		osip_call_id_parse(call_id, call->call_id);
		req->call_id = call_id;

		/* CSeq */
		if (osip_cseq_init(&cseq)) break;
		snprintf(tmp, 1024, "%u", ++call->l_cseq);
		osip_cseq_set_number(cseq, osip_strdup(tmp));
		osip_cseq_set_method(cseq, osip_strdup("BYE"));
		req->cseq = cseq;

		/* Contact */
		snprintf(tmp, 1024, "<sip:%s@%s:%u>", req->from->url->username,
			cfg_bindip, cfg_bindport);
		osip_message_set_contact(req, tmp);

		/* Defaults */
		osip_message_set_max_forwards(req, "70");
		sip_default_headers(req);

		/* Create Client Transaction */
		if (osip_transaction_init(&trans, NICT, osip, req)) break;

		event = osip_new_outgoing_sipmessage(req);
		event->transactionid = trans->transactionid;
		osip_transaction_add_event(trans, event);
		return;

	} while (0);

	osip_message_free(req);
}

static void sip_new_request(osip_event_t *sipevent)
{
	int i, ctx_type;
	sip_call_t *call;
	char *s;
	osip_transaction_t *trans;
	osip_message_t *answer;
	osip_event_t *revent;

	ctx_type = NIST;
	if (MSG_IS_INVITE(sipevent->sip)) ctx_type = IST;
	if (MSG_IS_ACK(sipevent->sip)) ctx_type = -1;

	trans = NULL;
	if (ctx_type != -1) {
		/* Create new SIP transaction */
		i = osip_transaction_init(&trans, (osip_fsm_type_t)ctx_type, osip, sipevent->sip);
		if (i) {
			osip_event_free(sipevent);
			return;
		}

		/* Add incoming event to newly created transaction */
		sipevent->transactionid = trans->transactionid;
		osip_transaction_add_event(trans, sipevent);

		/* INVITEs */
		if (ctx_type == IST) {
			/* 100: Trying */
			sip_default_response(&answer, 100, sipevent->sip, NULL);
			revent = osip_new_outgoing_sipmessage(answer);
			revent->transactionid = trans->transactionid;
			osip_transaction_add_event(trans, revent);
			return;
		}
	}

	/* Accept any BYEs, just for testing */
	if ( !strcasecmp(sipevent->sip->sip_method, "BYE") ) {
			osip_call_id_to_str(sipevent->sip->call_id, &s);
			call = sip_call_find(s);
			free(s);
			if (call) {
				/* Call found -- Send response */
				call->state = CALL_STATE_HANGUP;
				if (call->cbfunc) call->cbfunc(call, SIP_CB_HANGUP, call->cbptr);
				sip_default_response(&answer, 200, sipevent->sip, NULL);
				revent = osip_new_outgoing_sipmessage(answer);
				revent->transactionid = trans->transactionid;
				osip_transaction_add_event(trans, revent);
			} else {
				/* Call not found -- Send error */
				sip_default_response(&answer, 481, sipevent->sip, NULL);
				revent = osip_new_outgoing_sipmessage(answer);
				revent->transactionid = trans->transactionid;
				osip_transaction_add_event(trans, revent);
			}
			return;
	}

	/* CANCELs */
	if ( !strcasecmp(sipevent->sip->sip_method, "CANCEL") ) {
			osip_call_id_to_str(sipevent->sip->call_id, &s);
			call = sip_call_find(s);
			free(s);
			if (call) {
				/* Call found -- Send response */
				call->state = CALL_STATE_HANGUP;
				if (call->cbfunc) call->cbfunc(call, SIP_CB_HANGUP, call->cbptr);
				sip_default_response(&answer, 200, sipevent->sip, NULL);
				revent = osip_new_outgoing_sipmessage(answer);
				revent->transactionid = trans->transactionid;
				osip_transaction_add_event(trans, revent);
			} else {
				/* Call not found -- Send error */
				sip_default_response(&answer, 481, sipevent->sip, NULL);
				revent = osip_new_outgoing_sipmessage(answer);
				revent->transactionid = trans->transactionid;
				osip_transaction_add_event(trans, revent);
			}
			return;
	}

	if (ctx_type == -1) {
		osip_event_free(sipevent);
	}
}

static void rtp_log_func(const gchar *log_domain, GLogLevelFlags log_level,
						 const gchar *message, gpointer user_data)
{
	char buf[200];

	snprintf(buf, 200, "RTP: %s\n", message);
	log_print(0, buf);
}

/********************************************************************
 * SIP Terminal Commands
 */

static void cmd_show_sip_calls(struct terminal *term, int reason)
{
	sip_call_t *call;
	char *l_user, *r_user;
	char buf[200];

	if (reason == TERM_RSN_EXEC) {
		term_write(term, " Local        Remote\n");
		term_write(term, "-----------------------------------------------------------\n");
		for (call = sip_call_list; call; call = call->next) {
			l_user = call->l_user;
			if (!l_user) l_user = "?";
			r_user = call->r_user;
			if (!r_user) r_user = "?";

			snprintf(buf, 200, " %16s  %16s\n", call->l_user, call->r_user);
			term_write(term, buf);
		}
	}
}

/********************************************************************
 * SIP Module API
 */

void sip_init(int socket)
{
	struct sockaddr_in sa;

	sip_call_list = NULL;

	cfg_proxy = cfg_find("sip.proxy");
	cfg_bindip = cfg_find("sip.localip");
	cfg_bindport = SIP_SERVER_PORT;

	/* Bind sip server socket */
	s_sip = socket;
	memset(&sa, 0, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(SIP_SERVER_PORT);
	bind(s_sip, (struct sockaddr *)&sa, sizeof(sa));

	/* Initialize oRTP */
	g_log_set_handler("", G_LOG_LEVEL_MASK, rtp_log_func, NULL);
	ortp_init();

	/* Initialize oSIP */
	osip_init(&osip);
	osip_set_cb_send_message(osip, &cb_send_message);

	osip_set_kill_transaction_callback(osip, OSIP_ICT_KILL_TRANSACTION, &cb_kill_transaction);
	osip_set_kill_transaction_callback(osip, OSIP_IST_KILL_TRANSACTION, &cb_kill_transaction);
	osip_set_kill_transaction_callback(osip, OSIP_NICT_KILL_TRANSACTION, &cb_kill_transaction);
	osip_set_kill_transaction_callback(osip, OSIP_NIST_KILL_TRANSACTION, &cb_kill_transaction);

	osip_set_message_callback(osip, OSIP_IST_INVITE_RECEIVED, &cb_message);
	osip_set_message_callback(osip, OSIP_ICT_STATUS_1XX_RECEIVED, &cb_message);
	osip_set_message_callback(osip, OSIP_ICT_STATUS_2XX_RECEIVED, &cb_message);
	osip_set_message_callback(osip, OSIP_ICT_STATUS_3XX_RECEIVED, &cb_message);
	osip_set_message_callback(osip, OSIP_ICT_STATUS_4XX_RECEIVED, &cb_message);
	osip_set_message_callback(osip, OSIP_ICT_STATUS_5XX_RECEIVED, &cb_message);
	osip_set_message_callback(osip, OSIP_ICT_STATUS_6XX_RECEIVED, &cb_message);

	/* register terminal commands */
	term_reg_command("show sip calls", cmd_show_sip_calls);
}

void sip_done()
{
	osip_release(osip);
	ortp_exit();
	close(s_sip);
}

void sip_server_recv(char *buf, int len, struct sockaddr_in *sa)
{
	int i;
	osip_event_t *sipevent;

	if (len < 5) return;
	buf[len] = 0;

	sipevent = osip_parse(buf);
	if (sipevent) {
		if (sipevent->sip) {
			/* Log incoming sip message */
			sip_log_message("RX", sipevent->sip);

			i = osip_find_transaction_and_add_event(osip, sipevent);
			if (i) {
				/* This event has no transaction */
				if (MSG_IS_REQUEST(sipevent->sip)) {
					sip_new_request(sipevent);
				} else {
					osip_event_free(sipevent);
				}
			} else {
				/* Message added to transaction */
			}
		} else {
			osip_event_free(sipevent);
		}
	} else {
		/* Parse error */
	}
}

void sip_timers()
{
	osip_timers_ict_execute(osip);
	osip_timers_ist_execute(osip);
	osip_timers_nict_execute(osip);
	osip_timers_nist_execute(osip);

	osip_ict_execute(osip);
	osip_ist_execute(osip);
	osip_nict_execute(osip);
	osip_nist_execute(osip);
}

/********************************************************************
 * SIP Protocol API
 */

/* sip_call_create()
 *   Allocate sip call structure and add it to call chain.
 */
sip_call_t * sip_call_create()
{
	sip_call_t *call;

	/* Allocate memory for sip_call_t */
	call = malloc(sizeof(sip_call_t));
	if (!call) return NULL;

	/* Initialize memory */
	memset(call, 0, sizeof(sip_call_t));

	/* Allocate RTP session structure */
	call->rtp = rtp_session_new(RTP_SESSION_SENDRECV);

	/* Insert into call list */
	call->next = sip_call_list;
	sip_call_list = call;

	return call;
}

/* sip_call_destroy()
 *   Remove specified sip call from call chain, free used memory.
 * This function also cancels all associated transactions.
 */
void sip_call_destroy(sip_call_t *call)
{
	int i;
	sip_call_t *c;
	osip_transaction_t *trans;

	if (!call) return;

	/* Find a call in the call list */
	if (sip_call_list == call) {
		sip_call_list = call->next;
	} else {
		for (c = sip_call_list; c; c = c->next) {
			if (c->next == call) {
				c->next = call->next;
				break;
			}
		}
	}

	/* Release RTP */
	if (call->rtp) rtp_session_destroy(call->rtp);

	/* Send BYE message if call is connected */
	if (call->state == CALL_STATE_CONNECTED) {
		sip_send_bye(call);
	}

	/* Remove references */
	/* Invite Client Transactions */
	i = 0;
	while (!osip_list_eol(osip->osip_ict_transactions, i)) {
		trans = (osip_transaction_t *)osip_list_get(osip->osip_ict_transactions, i);
		i++;

		if (trans->your_instance == call) {
			/* Remove call reference */
			osip_transaction_set_your_instance(trans, NULL);

			/* Cancel INVITE */
			if (trans->last_response)
				if (MSG_IS_STATUS_1XX(trans->last_response)) {
					sip_cancel_request(trans->orig_request);
				}
		}
	}
	/* Invite Server Transactions */
	i = 0;
	while (!osip_list_eol(osip->osip_ist_transactions, i)) {
		trans = (osip_transaction_t *)osip_list_get(osip->osip_ist_transactions, i);
		i++;

		if (trans->your_instance == call) {
			/* Transaction is cancelled */
			if (trans->last_response)
				if (MSG_IS_STATUS_1XX(trans->last_response)) {
					sip_call_response(call, 487, NULL);
				}

			/* Remove call reference */
			osip_transaction_set_your_instance(trans, NULL);
		}
	}

	/* Free strings */
	if (call->l_user) free(call->l_user);
	if (call->r_user) free(call->r_user);
	if (call->call_id) free(call->call_id);
	if (call->l_tag) free(call->l_tag);
	if (call->r_tag) free(call->r_tag);

	/* Free memory */
	free(call);
}

void sip_call_set_callback(sip_call_t *call, sip_callback_t func, void *ptr)
{
	if (!call) return;

	call->cbfunc = func;
	call->cbptr = ptr;
}

int sip_call_originate(sip_call_t *call, char *from, char *to)
{
	int i;
	osip_message_t *req;
	osip_event_t *event;
	osip_transaction_t *trans;
	osip_call_id_t *call_id;
	osip_cseq_t *cseq;
	osip_authorization_t *auth;
	char to_str[256], tmp[1024];

	if (!call) return -1;

	/* Check destination */
	snprintf(to_str, 256, "%s@%s", to, cfg_proxy);

	/* Save source and destination */
	call->l_user = strdup(from);
	call->r_user = strdup(to_str);

	if (osip_message_init(&req)) return -1;

	/* Build INVITE Request */
	do {
		osip_message_set_method(req, osip_strdup("INVITE"));
		osip_message_set_version(req, osip_strdup("SIP/2.0"));
		osip_message_set_status_code(req, 0);
		osip_message_set_reason_phrase(req, NULL);

		/* To */
		snprintf(tmp, 1024, "sip:%s", to_str);
		if (osip_message_set_to(req, osip_strdup(tmp))) break;
		/* From */
		snprintf(tmp, 1024, "sip:%s", from);
		if (osip_message_set_from(req, osip_strdup(tmp))) break;
		sip_check_local_tag(call);
		osip_from_set_tag(req->from, osip_strdup(call->l_tag));
		osip_uri_clone(req->to->url, &req->req_uri);

		/* VIA */
		snprintf(tmp, 1024, "SIP/2.0/UDP %s:%u;branch=z9hG4bK%u",
			cfg_bindip, cfg_bindport, random_number());
		osip_message_set_via(req, tmp);

		/* Call-ID */
		if (osip_call_id_init(&call_id)) break;
		snprintf(tmp, 1024, "%u", random_number());
		osip_call_id_set_number(call_id, osip_strdup(tmp));
		osip_call_id_set_host(call_id, osip_strdup(cfg_bindip));
		req->call_id = call_id;
		osip_call_id_to_str(call_id, &call->call_id);

		/* CSeq */
		if (osip_cseq_init(&cseq)) break;
		call->l_cseq = time(NULL);
		snprintf(tmp, 1024, "%u", call->l_cseq);
		osip_cseq_set_number(cseq, osip_strdup(tmp));
		osip_cseq_set_method(cseq, osip_strdup("INVITE"));
		req->cseq = cseq;

		/* Contact */
		snprintf(tmp, 1024, "<sip:%s@%s:%u>", req->from->url->username,
			cfg_bindip, cfg_bindport);
		osip_message_set_contact(req, tmp);

		/* Authorization header -- ONLY FOR TEST */
		if (osip_authorization_init(&auth)) break;
		osip_authorization_set_username(auth, "dect");
		osip_authorization_set_realm(auth, osip_strdup("asterisk"));
		osip_authorization_set_uri(auth, "sip:uri");

		osip_authorization_set_auth_type(auth, osip_strdup("Digest"));
		osip_authorization_set_nonce(auth, osip_strdup("000"));
		osip_authorization_set_opaque(auth, osip_strdup("000"));
		osip_authorization_set_algorithm(auth, osip_strdup("MD5"));
		osip_authorization_set_response(auth, osip_strdup("0123456789ABCDEF"));
		osip_list_add(req->proxy_authorizations, auth, -1);

		/* Defaults */
		osip_message_set_max_forwards(req, "5");
		sip_default_headers(req);

		/* Add SDP body */
		call->voice_port = sip_get_rtp_port();
		snprintf(tmp, 1024,
			"v=0\r\n"
			"o=dect 0 0 IN IP4 %s\r\n"
			"s=DECT Voice Call\r\n"
			"c=IN IP4 %s\r\n"
			"t=0 0\r\n"
			"m=audio %u RTP/AVP 8\r\n"
			"a=rtpmap:8 PCMA/8000\r\n",
			cfg_bindip, cfg_bindip, call->voice_port);
		osip_message_set_body(req, tmp);
		osip_message_set_content_type(req, "application/sdp");
		rtp_session_set_local_addr(call->rtp, cfg_bindip, call->voice_port);

		/* Expire */
		osip_message_set_expires(req, "120");

		/* Create Invite Client Transaction */
		i = osip_transaction_init(&trans, ICT, osip, req);
		if (i) break;

		osip_transaction_set_your_instance(trans, call);

		event = osip_new_outgoing_sipmessage(req);
		event->transactionid = trans->transactionid;
		osip_transaction_add_event(trans, event);

		return 0;

	} while (0);

	log_print(0, "SIP: Error while sending INVITE\n");
	osip_message_free(req);
	return -1;
}

/* sip_call_find()
 *   This function finds the sip call by the specified Call-ID.
 */
sip_call_t *sip_call_find(char *call_id)
{
	sip_call_t *call;

	call = sip_call_list;
	while (call) {
		if (call->call_id) {
			if (strcmp(call->call_id, call_id) == 0) return call;
		}
		call = call->next;
	}
	return NULL;
}

/* sip_call_response()
 *   This functions sent reply code to the Invite Server Transaction
 * corresponding the specified sip call.
 */
void sip_call_response(sip_call_t *call, int code, char *phrase)
{
	int i;
	osip_transaction_t *trans;
	osip_message_t *answer;
	osip_event_t *revent;
	char tmp[1024];

	if (!call) return;

	i = 0;
	while (!osip_list_eol(osip->osip_ist_transactions, i)) {
		trans = (osip_transaction_t *)osip_list_get(osip->osip_ist_transactions, i);
		i++;

		if (trans->your_instance == call) {
			/* Construct body and generate default response */
			if (code == 200) {
				/* Add SDP body */
				call->voice_port = sip_get_rtp_port();
				rtp_session_set_local_addr(call->rtp, cfg_bindip, call->voice_port);
				snprintf(tmp, 1024,
					"v=0\r\n"
					"o=dect 0 0 IN IP4 %s\r\n"
					"s=DECT Voice Call\r\n"
					"c=IN IP4 %s\r\n"
					"t=0 0\r\n"
					"m=audio %u RTP/AVP 8\r\n"
					"a=rtpmap:8 PCMA/8000\r\n",
					cfg_bindip, cfg_bindip, call->voice_port);
				sip_default_response(&answer, code, trans->orig_request, tmp);
				call->state = CALL_STATE_CONNECTED;
			} else {
				sip_default_response(&answer, code, trans->orig_request, NULL);
			}
			/* Create dialog, if needed */
			if ((code >= 101) && (code <= 200)) {
				sip_check_local_tag(call);
			}
			/* Modify response, if it within a dialog */
			if (call->l_tag) {
				osip_from_set_tag(answer->to, osip_strdup(call->l_tag));
			}
			/* Add response to invite transaction */
			revent = osip_new_outgoing_sipmessage(answer);
			revent->transactionid = trans->transactionid;
			osip_transaction_add_event(trans, revent);
			return;
		}
	}
}
