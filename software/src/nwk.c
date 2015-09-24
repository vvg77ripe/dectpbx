
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <string.h>

#include "terminal.h"
#include "dlc.h"
#include "nwk.h"
#include "nwk-mm.h"
#include "nwk-cc.h"
#include "sql.h"

#include "iwu-panasonic.h"
#include "iwu-siemens.h"


static nwk_trans_t *tlist;
static nwk_page_t *plist;


static void trans_print()
{
	nwk_trans_t *trans;
	int i;

	trans = tlist;
	i = 0;
	while (trans) {
		i++;
		trans = trans->next;
	}
}

static void nwk_thread_release(void *p)
{
	int i;
	nwk_trans_t *trans, *tl;

	trans = (struct nwk_transaction *)p;

	if (trans->sql) {
		sql_close(trans->sql);
	}

	for (i = 0; i < NWK_QUEUE_LEN; i++)
		if (trans->inq_c[i].data) free(trans->inq_c[i].data);
	for (i = 0; i < NWK_QUEUE_LEN; i++)
		if (trans->inq_r[i].data) free(trans->inq_r[i].data);

	if (tlist == trans) {
		tlist = trans->next;
	} else {
		tl = tlist;
		while (tl) {
			if (tl->next == trans) {
				tl->next = trans->next;
				break;
			}
			tl = tl->next;
		}
	}

	free(trans);
	trans_print();
}

static void lce_command(struct nwk_transaction *trans, unsigned char cmd, unsigned char *data, int len)
{
	unsigned char *pp_id, *fp_id;
	nwk_page_t *page, *p1;
	pp_info_t *pp;
	int pp_len, fp_len;
	unsigned char buf[20];

	/* Find Portable Identity */
	pp_id = nwk_find_parm(P_PORTABLE_IDENTITY, &pp_len, data, len);
	if (!pp_id) {
		nwk_reply(trans, DECT_LCE_PAGE_REJECT);
		nwk_send_reply(trans);
		return;
	}
	fp_id = nwk_find_parm(P_FIXED_IDENTITY, &fp_len, data, len);

	pp = pp_find(trans, pp_id, pp_len);
	if (!pp) {
		nwk_reply(trans, DECT_LCE_PAGE_REJECT);
		nwk_send_reply(trans);
		return;
	}

	/* Find page structure */
	p1 = NULL;
	for (page = plist; page; page = page->next) {
		if (page->pp->tpui == pp->tpui) {
			/* Remove page from the list  */
			if (p1) {
				p1->next = page->next;
			} else {
				plist = page->next;
			}
			/* Send callback */
			pp->ipui_len = pp_len;
			memcpy(pp->ipui, pp_id, pp_len);
			page->func(trans, pp, PAGE_CALLBACK_OK, page->func_ptr);
			pp_free(page->pp);
			pp_free(pp);
			free(page);
			return;
		}
		p1 = page;
	}

	/* Not found */
	nwk_reply(trans, DECT_LCE_PAGE_REJECT);
	nwk_send_reply(trans);
	pp_free(pp);
}

static void * nwk_thread(void *p)
{
	struct nwk_transaction *trans;

	log_print(0, "Transaction created.\n");

	/* start */
	trans = (struct nwk_transaction *)p;
	pthread_cleanup_push(nwk_thread_release, trans);

	/* init rng */
	srand(time(NULL));

	/* protocol dispatcher */
	switch (trans->tid & 0x0F) {
		case DECT_PROTO_LCE:
			lce_command(trans, trans->req[0], &trans->req[1], trans->req_len-1);
			break;
		case DECT_PROTO_CC:
			cc_command(trans, trans->req[0], &trans->req[1], trans->req_len-1);
			break;
		case DECT_PROTO_MM:
			mm_command(trans, trans->req[0], &trans->req[1], trans->req_len-1);
			break;
	}

	/* cleanup*/
	pthread_cleanup_pop(1);
	return NULL;
}


static void nwk_packet_dump(dect_conn_t *mbc, char dir, unsigned char *data, int len)
{
	unsigned char *val, pid;
	int rlen, vlen, i;
	char *pname, *dstr;
	char tmp[200];
	time_t tms;

	/* Current timestamp */
	tms = time(NULL);
	log_print(0, "# %s", asctime(localtime(&tms)));

	/* Transaction ID and control code */
	if (dir) { dstr = "TX"; } else { dstr = "RX"; }
	tmp[0] = 0;
	switch (data[0] & 0x0F) {
		case DECT_PROTO_LCE:
			snprintf(tmp, 200, "Link Control");
			break;
		case DECT_PROTO_CC:
			snprintf(tmp, 200, "Call Control %s", cc_dump_cmd(data[1]));
			break;
		case DECT_PROTO_MM:
			snprintf(tmp, 200, "Mobility Management %s", mm_dump_cmd(data[1]));
			break;
		default:
			snprintf(tmp, 200, "Unknown");
			break;
	}
	log_print(0, "%s %05X, TID %02X, CODE %02X :: %s\n",
		dstr, mbc->pmid, data[0], data[1], tmp);

	/* Parameters */
	val = data + 2;
	rlen = len - 2;
	while (rlen > 0) {
		pid = val[0];
		val++;
		rlen--;
		vlen = 0;
		if (pid & 0x80) {
			/* Fixed length */
			if ((pid & 0xF0) == 0xE0) vlen = 1;
		} else {
			/* Variable length */
			if (rlen < 1) break;
			vlen = val[0];
			val++;
			rlen--;
			if (rlen < vlen) break;
		}

		pname = "<UNKNOWN>";
		switch (pid) {
			case P_PORTABLE_IDENTITY:
				pname = "Portable Identity";
				break;
			case P_FIXED_IDENTITY:
				pname = "Fixed Identity";
				break;
			case P_LOCATION_AREA:
				pname = "Location Area";
				break;
			case P_REJECT_REASON:
				pname = "Reject Reason";
				break;

			case P_TERMINAL_CAPABILITY:
				pname = "Terminal Capability";
				break;
			case P_IWU_TO_IWU:
				pname = "IWU-to-IWU";
				break;
			case P_PROPRIETARY:
				pname = "Proprietary";
				break;

			case P_MULTI_KEYPAD:
				pname = "Multi-Keypad";
				break;
			case P_CALLING_PARTY_NUMBER:
				pname = "Calling Party Number";
				break;

			case P_BASIC_SERVICE:
				pname = "Basic Service";
				break;
			case P_RELEASE_REASON:
				pname = "Release Reason";
				break;
			case P_SIGNAL:
				pname = "Signal";
				break;
			case P_PROGRESS_INDICATOR:
				pname = "Progress Indicator";
				break;
		}

		/* print */
		tmp[0] = 0;
		if (vlen != 0) sprintf(&tmp[strlen(tmp)], "= ");
		for (i = 0; i < vlen; i++) {
			sprintf(&tmp[strlen(tmp)], "%02X ", val[i]);
			if ((i == 10) && (vlen > 11)) {
				sprintf(&tmp[strlen(tmp)], "...");
				break;
			}
		}
		log_print(0, "    [%02X] %s %s\n", pid, pname, tmp);

		/* next parameter */
		val += vlen;
		rlen -= vlen;
	}
}

static void nwk_create_transaction(dect_conn_t *mbc, unsigned char *data, int len)
{
	int i, r;
	struct nwk_transaction *trans;

	/* allocate memory */
	trans = malloc(sizeof(nwk_trans_t));
	if (!trans) return;

	/* initialize transaction data */
	memset(trans, 0, sizeof(struct nwk_transaction));
	trans->tid = data[0];
	trans->mbc = mbc;

	/* copy request data */
	if (len <= DECT_NWK_MAX_REQUEST) {
		memcpy(trans->req, &data[1], len);
		trans->req_len = len - 1;
	}

	/* add to chain */
	trans->next = tlist;
	tlist = trans;

	/* create transaction thread */
	r = pthread_create(&trans->thread_id, NULL, nwk_thread, (void *)trans);
	if (r) {
		printf("Failed to create transaction thread\n");
		free(trans);
		return;
	}

}

static struct nwk_transaction * nwk_find_transaction(dect_conn_t *mbc, unsigned char tid)
{
	int i;
	nwk_trans_t *trans;

	trans = tlist;
	while (trans) {
		if ( (trans->mbc == mbc) && (trans->tid == tid) ) {
			return trans;
		}
		trans = trans->next;
	}

	return NULL;
}

void nwk_init()
{
	tlist = NULL;
	plist = NULL;
}

void nwk_recv(dect_conn_t *mbc, unsigned char *data, int len)
{
	int i;
	struct nwk_transaction *trans;

	if (len < 2) return;
	nwk_packet_dump(mbc, 0, data, len);

	if ( !(data[0] & 0x80) ) {
		/* Message from transaction originator */
		trans = nwk_find_transaction(mbc, data[0]);
		if (trans) {
			for (i = 0; i < NWK_QUEUE_LEN; i++) {
				if (!trans->inq_c[i].len) {
					trans->inq_c[i].data = malloc(len);
					if (!trans->inq_c[i].data) return;
					memcpy(trans->inq_c[i].data, &data[1], len-1);
					trans->inq_c[i].len = len-1;
					return;
				}
			}
		} else {
			nwk_create_transaction(mbc, data, len);
		}
	} else {
		/* Message from transaction destination */
		trans = nwk_find_transaction(mbc, data[0]);
		if (trans) {
			for (i = 0; i < NWK_QUEUE_LEN; i++) {
				if (!trans->inq_c[i].len) {
					trans->inq_c[i].data = malloc(len);
					if (!trans->inq_c[i].data) return;
					memcpy(trans->inq_c[i].data, &data[1], len-1);
					trans->inq_c[i].len = len-1;
					return;
				}
			}
		}
	}
}

/* nwk_send();
 *   Send network layer packet
 *
 * This function invoked in transaction thread context and may suspend
 * calling thread if DLC layer is busy, or return -1 (error), if connection
 * is closed.
 */
int nwk_send(struct nwk_transaction *trans, unsigned char *data, int len)
{
	if (!trans) return -1;
	if (!data) return -1;

	nwk_packet_dump(trans->mbc, 1, data, len);

	dlc_send_data(trans->mbc->client, trans->mbc, DLC_LLN_CLASS_A, data, len);
	return 0;
}

int nwk_recv_queue(struct nwk_transaction *trans, unsigned char *data, int len)
{
	int i, j;
	int rlen;

	if (!trans) return -1;
	if (!data) return -1;

	for (i = 0; i < 100; i++) {
		for (j = 0; j < NWK_QUEUE_LEN; j++) {
			/* Check signal */
			if (trans->signal) {
				if (trans->signal == TSIG_TERMINATE) return -1;
				return 0;
			}
			/* Check queue */
			if (trans->inq_c[j].len) {
				rlen = trans->inq_c[j].len;
				if (rlen > len) rlen = len;
				memcpy(data, trans->inq_c[j].data, rlen);
				free(trans->inq_c[j].data);
				trans->inq_c[j].data = NULL;
				trans->inq_c[j].len = 0;
				return rlen;
			}
		}
		usleep(1000);
	}

	return 0;
}

void nwk_reply(struct nwk_transaction *trans, unsigned char code)
{
	if (!trans) return;

	trans->rep[0] = 0;
	trans->rep[1] = code;
	trans->rep_len = 2;
}

void nwk_reply_parm(struct nwk_transaction *trans, unsigned char code,
					unsigned char len, unsigned char *val)
{
	int i;

	if (!trans) return;

	if (code & 0x80) {
		/* Fixed length */
		if ((trans->rep_len + 2) > DECT_NWK_MAX_REPLY) return;
		trans->rep[trans->rep_len] = code;
		trans->rep_len++;
		trans->rep[trans->rep_len] = len;
		trans->rep_len++;
	} else {
		/* Variable length */
		if ((trans->rep_len + len + 2) > DECT_NWK_MAX_REPLY) return;
		trans->rep[trans->rep_len] = code;
		trans->rep_len++;
		trans->rep[trans->rep_len] = len;
		trans->rep_len++;
		if (len) for (i = 0; i < len; i++) {
			trans->rep[trans->rep_len] = val[i];
			trans->rep_len++;
		}
	}
}

int nwk_send_reply(struct nwk_transaction *trans)
{
	if (!trans) return;

	trans->rep[0] = trans->tid ^ 0x80;
	return nwk_send(trans, trans->rep, trans->rep_len);
}

int nwk_send_command(struct nwk_transaction *trans, unsigned int tid)
{
	if (!trans) return;

	trans->rep[0] = tid;
	return nwk_send(trans, trans->rep, trans->rep_len);
}

unsigned char * nwk_find_parm(unsigned char id, int *plen, unsigned char *data, int len)
{
	unsigned char *val, pid;
	int rlen, vlen;

	val = data;
	rlen = len;
	while (rlen > 0) {
		pid = val[0];
		val++;
		rlen--;
		vlen = 0;
		if (pid & 0x80) {
			/* Fixed length */
			if ((pid & 0xF0) == 0xE0) vlen = 1;
		} else {
			/* Variable length */
			if (rlen < 1) break;
			vlen = val[0];
			val++;
			rlen--;
			if (rlen < vlen) break;
		}

		if (pid == id) {
			if (plen) *plen = vlen;
			return val;
		}

		/* next parameter */
		val += vlen;
		rlen -= vlen;
	}
	return NULL;
}

/* Portable Parts database functions
 *
 *
 */

pp_info_t *pp_find(struct nwk_transaction *trans, unsigned char *ipui, int len)
{
	pp_info_t *pp;
	int i;
	char ipui_str[50];
	char q[100];
	void *sql;
	void *sql_res;
	char **sql_row;

	/* Create SQL connection */
	if (trans) {
		if (!trans->sql) trans->sql = sql_create();
		sql = trans->sql;
	} else {
		sql = sql_create();
	}

	if (!sql) return NULL;

	pp = malloc(sizeof(pp_info_t));
	if (!pp) return NULL;

	memset(pp, 0, sizeof(pp_info_t));

	do {
		/* Query home database  */
		if (len > 0) {
			/* Find IPUI */
			sprintf(ipui_str, "%02i:", ipui[1] & 0x7F);
			for (i = 2; i < len; i++) {
				sprintf(&ipui_str[i*2 - 1], "%02X", ipui[i]);
			}
			snprintf(q, 100,
				"SELECT tpui, iwu_type, phone, ipui FROM hdb WHERE ipui = '%s'",
				ipui_str);
		} else {
			/* Find phone number */
			snprintf(q, 100,
				"SELECT tpui, iwu_type, phone, ipui FROM hdb WHERE phone = '%s'",
				ipui);
		}
		sql_res = NULL;
		sql_query(sql, q, &sql_res);
		if (sql_res == NULL) break;

		/* Fetch data */
		sql_row = sql_fetch_result(sql_res);
		if (sql_row) {
			pp->tpui = atoi(sql_row[0]);
			pp->iwu_type = atoi(sql_row[1]);
			if (sql_row[2][0] != 0) {
				pp->phone = strdup(sql_row[2]);
			} else {
				pp->phone = strdup("821@sip.udp.itcn.ru");
			}
			/* Get IPUI */
			if (sql_row[3][2] == ':') {
				sql_row[3][2] = 0;
				pp->ipui_len = atoi(sql_row[3]) >> 3;
				for (i = 0; i < pp->ipui_len; i++) {
					sscanf(&sql_row[3][i*2 + 3], "%2X", &pp->ipui[i]);
				}
			}
		}
		sql_free_result(sql_res);

		if (pp->tpui == 0) break;

		if (!trans) sql_close(sql);
		return pp;
	} while (0);

	pp_free(pp);
	if (!trans) sql_close(sql);
	return NULL;
}

void pp_free(pp_info_t *pp)
{
	if (!pp) return;

	if (pp->phone) free(pp->phone);

	free(pp);
}

int pp_iwu(int type, struct nwk_transaction *trans, pp_info_t *pp, unsigned char *data, int len)
{
	if (!pp) return 0;

	switch (pp->iwu_type) {
		case IWU_TYPE_PANASONIC:
			return iwu_panasonic(type, trans, pp, data, len);
		case IWU_TYPE_SIEMENS:
			return iwu_siemens(type, trans, pp, data, len);
	}

	return 0;
}

/* Paging control functions
 *
 *
 */
void page_start(pp_info_t *pp, page_callback_t func, void *ptr)
{
	nwk_page_t *page;

	if (!func) return;

	page = malloc(sizeof(nwk_page_t));
	if (!page) return;
	memset(page, 0, sizeof(nwk_page_t));

	/* Initialize page structure */
	page->next = plist;
	page->pp = pp;
	page->func = func;
	page->func_ptr = ptr;

	/* Add to paging list*/
	plist = page;
}

void page_timers()
{
	nwk_page_t *page, *p1;
	unsigned int tms_next;
	unsigned char buf[10];

	tms_next = time(NULL) - 2;
	p1 = NULL;
	for (page = plist; page; page = page->next) {
		if (page->page_time <= tms_next) {
			page->page_time = time(NULL);
			page->page_count++;

			if (page->page_count < 4) {
				/* Send page message */
				buf[0] = 0x14;
				buf[1] = page->pp->ipui[page->pp->ipui_len-2];
				buf[2] = page->pp->ipui[page->pp->ipui_len-1];
				dect_server_send_paging(NULL, buf, 3);
			} else {
				/* Timeout */
				page->func(NULL, page->pp, PAGE_CALLBACK_FAIL, page->func_ptr);
				if (p1) {
					p1->next = page->next;
				} else {
					plist = page->next;
				}
				/* Free memory */
				if (page->pp) pp_free(page->pp);
				free(page);
				return;
			}
		}

		p1 = page;
	}
}
