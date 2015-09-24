
#include <stdio.h>

#include "server.h"
#include "terminal.h"
#include "dlc.h"
#include "nwk.h"


static dect_conn_t *clist;


static unsigned short dlc_checksum(unsigned short lsig, unsigned char *buf, int flen)
{
	int c0, c1;
	unsigned char r0, r1;
	int i;

	c0 = 0;
	c1 = 0;

	/* Data */
	for (i = 0; i < (flen-2); i++) {
		c0 += buf[i];
		c1 += c0;
	}

	/* checksum bytes = 0 */
	c1 += c0;
	c1 += c0;

	c0 = c0 % 255;
	c1 = c1 % 255;

	/* result */
	r0 = (2*255 + c0 - c1) % 255;
	r1 = (2*255 + c1 - 2*c0) % 255;

	return (r0 << 8) | r1;
}

dect_conn_t *dect_find_connection(unsigned int pmid, unsigned char ecn)
{
	dect_conn_t *mbc;

	/* Find existing connection */
	mbc = clist;
	while (mbc) {
		if ((mbc->pmid == pmid) && (mbc->ecn == ecn)) return mbc;
		mbc = mbc->next;
	}

	/* Not exist - create new */
	mbc = malloc(sizeof(dect_conn_t));
	if (mbc) {
		memset(mbc, 0, sizeof(dect_conn_t));
		mbc->pmid = pmid;
		mbc->ecn = ecn;
		log_print(0, ":: New connection %05X.%02X\n", pmid, ecn);
		g726_init_state(&mbc->g726_dec);
		g726_init_state(&mbc->g726_enc);
	}

	/* Add to list */
	mbc->next = clist;
	clist = mbc;

	return mbc;
}

static void dlc_send_rr(dect_client_t *client, dect_conn_t *mbc, char lln)
{
	unsigned char rr[5];
	unsigned short csum;

	/* RR response */
	rr[0] = 0x01 | (lln << 4);
	rr[1] = 0x01 | (mbc->dlc_a.vr << 5);
	rr[2] = 0x01;
	csum = dlc_checksum(0, rr, 5);
	rr[3] = csum >> 8;
	rr[4] = csum & 0xFF;
	/* send packet */
	dect_server_send_lapc(client, mbc, rr, 5);
}

void dlc_send_data(dect_client_t *client, dect_conn_t *mbc, char lln,
						  unsigned char *data, int len)
{
	unsigned char cbuf[70];
	unsigned short csum;
	int i, l;

	memset(cbuf, 0xF0, 70);

	cbuf[0] = 0x03 | (lln << 4);
	cbuf[1] = (mbc->dlc_a.vr << 5) | (mbc->dlc_a.vs << 1);
	cbuf[2] = 0x01 | (len << 2);

	for (i = 0; i < len; i++)
		cbuf[i+3] = data[i];

	l = (len + 4) / 5 + 1;
	l = l * 5;
	csum = dlc_checksum(0, cbuf, l);
	cbuf[l-2] = csum >> 8;
	cbuf[l-1] = csum & 0xFF;

	dect_server_send_lapc(client, mbc, cbuf, l);
}

void dlc_init()
{
	clist = NULL;
}

void dlc_done()
{
	dect_conn_t *mbc, *conn;

	mbc = clist;
	while (conn = mbc) {
		mbc = mbc->next;
		free(conn);
	}
}

void dlc_recv(dect_client_t *client, unsigned int pmid, unsigned char ecn, unsigned char *pkt, int len)
{
	int i;
	char lln;
	unsigned char rr[10], nr, ns;
	unsigned short csum;
	void *pdata;
	int plen;
	dect_conn_t *mbc;

	mbc = dect_find_connection(pmid, ecn);
	if (!mbc) return;
	mbc->client = client;

	lln = (pkt[0] >> 4) & 7;

	/* Class A packet */
	if (lln == DLC_LLN_CLASS_A) {
		if (pkt[0] & DLC_ADDR_NLF) {
			/* New link flag */
			mbc->dlc_a.vr = 1;
			mbc->dlc_a.va = 0;
			mbc->dlc_a.vs = 0;
			mbc->dlc_a.spkt_len = 0;
			/* Response */
			rr[0] = 0x91;
			rr[1] = 0x01 | (mbc->dlc_a.vr << 5);
			rr[2] = 0x01;
			csum = dlc_checksum(0, rr, 5);
			rr[3] = csum >> 8;
			rr[4] = csum & 0xFF;
			/* send packet */
			dect_server_send_lapc(client, mbc, rr, 5);
			/* check data, if any */
			pdata = &pkt[3];
			plen = pkt[2] >> 2;
			if (plen) nwk_recv(mbc, pdata, plen);
			return;
		} else {
			if ( ((pkt[1] & 1) == 0) || ((pkt[1] & 0x0F) == 0x01) ) {
				/* checking ack */
				nr = (pkt[1] >> 5) & 7;
				if (nr == ((mbc->dlc_a.vs + 1) & 1)) {
					mbc->dlc_a.vs = nr;
				}
			}
			if ((pkt[1] & 1) == 0) {
				/* I frame */
				ns = (pkt[1] >> 1) & 7;
				if (ns == mbc->dlc_a.vr) {
					/* in-order packet, send ACK */
					mbc->dlc_a.vr = (mbc->dlc_a.vr + 1) & 1;
					dlc_send_rr(client, mbc, DLC_LLN_CLASS_A);
					/* send to network layer */
					pdata = &pkt[3];
					plen = pkt[2] >> 2;
					nwk_recv(mbc, pdata, plen);
				} else {
					/* out-of-order packet */
					dlc_send_rr(client, mbc, DLC_LLN_CLASS_A);
				}
			}
		}
	} /* DLC_LLN_CLASS_A */
}

int dlc_uplane_connect(dect_conn_t *mbc, unsigned char type, dect_uplane_cb func, void *ptr)
{
	if (!mbc) return -1;

	mbc->u_type = type;
	mbc->u_callback = func;
	mbc->u_ptr = ptr;

	return 0;
}

void dlc_uplane_disconnect(dect_conn_t *mbc)
{
	if (!mbc) return;

	mbc->u_type = 0;
	mbc->u_callback = NULL;
}
