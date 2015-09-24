
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "server.h"
#include "terminal.h"
#include "dlc.h"
#include "g711.h"
#include "g726.h"


static int s_dect;
static dect_client_t clist[DECT_MAX_CLIENTS];


static void dect_lapc_data(dect_client_t *client, struct msg_lapc_data *data, int len)
{
	int i, plen;
	unsigned char *pdata;

	plen = len - sizeof(struct msg_lapc_data);
	pdata = (unsigned char *)data + sizeof(struct msg_lapc_data);

	dlc_recv(client, ntohl(data->pmid), data->ecn, pdata, plen);
}

static void dect_voice_data(dect_client_t *client, struct msg_voice_data *data, int len)
{
	int i, a;
	unsigned char r;
	unsigned char gen;
	short v;
	dect_conn_t *mbc;
	unsigned char *voice;
	unsigned char buf[160];
	unsigned short seq_diff;

	voice = (void *)data + sizeof(struct msg_voice_data);

	mbc = dect_find_connection(ntohl(data->pmid), data->ecn);
	if (!mbc) return;

	seq_diff = ntohs(data->seq) - mbc->u_seq;
	if (seq_diff != 2) {
		log_print(0, "NET: Audio packet lost (%u).\n", seq_diff);
	}
	mbc->u_seq_counter += seq_diff;
	mbc->u_seq = ntohs(data->seq);

	/* Decode incoming audio */
	for (i = 0; i < 80; i++) {
		buf[i*2] = alaw_encode(g726_decode(voice[i] >> 4, &mbc->g726_dec));
		buf[i*2+1] = alaw_encode(g726_decode(voice[i] & 0x0F, &mbc->g726_dec));
	}

	/* Send to upper layer, if connected */
	if (mbc->u_type && mbc->u_callback) {
		mbc->u_callback(mbc, buf, 160, mbc->u_ptr);
	} else {
		memset(buf, 0x55, 160);
	}

	/* Insert signal, if set */
	gen = 0;
	switch (mbc->u_signal) {
		case UPLANE_SIGNAL_RINGBACK:
			mbc->u_sig_counter++;
			if (mbc->u_sig_counter > 200) mbc->u_sig_counter = 0;
			gen = 1; /* Silence */
			if (mbc->u_sig_counter < 50) gen = 2; /* Tone */
			break;

		case UPLANE_SIGNAL_BUSY:
			mbc->u_sig_counter++;
			if (mbc->u_sig_counter > 50) mbc->u_sig_counter = 0;
			gen = 1; /* Silence */
			if (mbc->u_sig_counter < 25) gen = 2; /* Tone */
			break;
	}

	/* Signal generator */
	switch (gen) {
		case 1:
			memset(buf, 0x55, 160);
			break;
		case 2:
			for (i = 0; i < 160; i++) {
				v = 20000 * sin(i * M_PI / 10);
				buf[i] = alaw_encode(v);
			}
			break;
	}

	/* Encode outgoing audio */
	for (i = 0; i < 80; i++) {
		r = g726_encode(alaw_decode(buf[i*2]), &mbc->g726_enc) << 4;
		r |= g726_encode(alaw_decode(buf[i*2+1]), &mbc->g726_enc) & 0x0F;
		voice[i] = r;
	}

	/* Send to phone */
	dect_server_send_voice(client, mbc, (char *)data, len);
}

static void dect_recv_sysinfo(dect_client_t *client, struct msg_sysinfo *data, int len)
{
	client->mbc_count = data->mbc_count;
}

/********************************************************************
 * Server terminal commands
 */

static void cmd_show_fp(struct terminal *term, int reason)
{
	int i;
	char buf[200];

	if (reason == TERM_RSN_EXEC) {
		term_write(term, " FPID   IP Address      MBC\n");
		term_write(term, "---------------------------------------------------\n");
		for (i = 0; i < DECT_MAX_CLIENTS; i++) {
			if (clist[i].fpid) {
				snprintf(buf, 200, " %04X  %16s %2i\n",
					clist[i].fpid, inet_ntoa(ntohl(clist[i].ipad)),
					clist[i].mbc_count);
				term_write(term, buf);
			}
		}
	}
}

/********************************************************************
 * Server API
 */

void dect_server_init(int socket)
{
	int i;
	struct sockaddr_in sa;

	s_dect = socket;

	for (i = 0; i < DECT_MAX_CLIENTS; i++) {
		clist[i].fpid = 0;
	}

	memset(&sa, 0, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(DECT_SERVER_PORT);
	bind(s_dect, (struct sockaddr *)&sa, sizeof(sa));

	term_reg_command("show fp", cmd_show_fp);
}

void dect_server_done()
{
	close(s_dect);
}

void dect_server_recv(char *buf, int len, struct sockaddr_in *sa)
{
	int i;
	struct dect_packet *pkt;
	struct dect_packet_header *hdr;
	void *data;
	unsigned short pktlen;
	dect_client_t *client;

	pkt = (struct dect_packet *)buf;
	if (len < sizeof(struct dect_packet)) return;

	/* Check sign */
	if (pkt->sign[0] != 'F') return;
	if (pkt->sign[1] != 'P') return;

	/* Find client record */
	client = NULL;
	for (i = 0; i < DECT_MAX_CLIENTS; i++) {
		if (clist[i].fpid == ntohl(pkt->fpid)) {
			client = &clist[i];
			client->last_active = time(NULL);
			break;
		}
		if (clist[i].fpid == 0) {
			client = &clist[i];
			client->fpid = ntohl(pkt->fpid);
			client->last_active = time(NULL);
			client->ipad = ntohl(sa->sin_addr.s_addr);
			log_print(0, "New FP :: ID %04X, RFPI %02X:%02X:%02X:%02X:%02X\n", client->fpid,
				pkt->rfpi[0], pkt->rfpi[1], pkt->rfpi[2], pkt->rfpi[3], pkt->rfpi[4]);
			break;
		}
	}

	if (!client) return;

	hdr = (struct dect_packet_header *)(buf + sizeof(struct dect_packet) - 4);
	len -= sizeof(struct dect_packet) - 4;

	while (len) {
		/* Check message size */
		if (len < sizeof(struct dect_packet_header)) break;

		/* Dispatch packet message */
		pktlen = ntohs(hdr->len);
		if (pktlen > len) {
			log_print(0, "SERV: Invalid packed size %i, max %i, type %i\n",
				pktlen, len, ntohs(hdr->type));
			break;
		}
		data = (unsigned char *)hdr + sizeof(struct dect_packet_header);

		switch (ntohs(hdr->type)) {
			case DECT_MSG_SYSINFO:
				dect_recv_sysinfo(client, (struct msg_sysinfo *)data, pktlen);
				break;

			case DECT_MSG_LAPC_DATA:
				dect_lapc_data(client, (struct msg_lapc_data *)data, pktlen);
				break;
			case DECT_MSG_VOICE:
				dect_voice_data(client, data, pktlen);
				break;
		}

		/* Goto next message in packet, if any */
		pktlen += sizeof(struct dect_packet_header);
		hdr = (struct dect_packet_header *)((unsigned char *)hdr + pktlen);
		len -= pktlen;
	}
}

void dect_server_send(dect_client_t *client, char *buf, int len)
{
	char pktbuf[1500];
	struct dect_packet *pkt;
	struct sockaddr_in sa;
	int i;

	if (!client) return;
	if (len < 4) return;

	memset(pktbuf, 0, 1500);
	pkt = (struct dect_packet *)pktbuf;

	/* Prepare header */
	pkt->sign[0] = 'D';
	pkt->sign[1] = 'S';
	pkt->fpid = htons(client->fpid);

	/* copy packet data */
	memcpy(&pktbuf[sizeof(struct dect_packet)-4], buf, len);

	/* send packet */
	memset(&sa, 0, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = htonl(client->ipad);
	sa.sin_port = htons(DECT_CLIENT_PORT);
	sendto(s_dect, pktbuf, sizeof(struct dect_packet) + len - 4, 0, (struct sockaddr *)&sa, sizeof(sa));
}

void dect_server_send_lapc(dect_client_t *client, void *mbc, char *data, int len)
{
	unsigned short buf[70];
	struct msg_lapc_data *pkt;
	dect_conn_t *mbcp;

	mbcp = (dect_conn_t *)mbc;
	buf[0] = htons(DECT_MSG_LAPC_DATA);
	buf[1] = htons(sizeof(struct msg_lapc_data) + len);

	pkt = (struct msg_lapc_data *)&buf[2];
	pkt->pmid = htonl(mbcp->pmid);
	pkt->ecn = mbcp->ecn;
	pkt->uplane = mbcp->u_type;

	memcpy((void *)&buf[2] + sizeof(struct msg_lapc_data), data, len);

	dect_server_send(client, (char *)buf, sizeof(struct msg_lapc_data) + len + 4);
}

void dect_server_send_voice(dect_client_t *client, void *mbc, char *data, int len)
{
	unsigned short buf[100];

	buf[0] = htons(DECT_MSG_VOICE);
	buf[1] = htons(len);

	memcpy((void *)&buf[2], data, len);

	dect_server_send(client, (char *)buf, len + 4);
}

void dect_server_send_paging(dect_client_t *client, char *data, int len)
{
	int i;
	unsigned short buf[70];

	if (!client) {
		for (i = 0; i < DECT_MAX_CLIENTS; i++) {
			if (clist[i].fpid == 0) continue;
			client = &clist[i];
			dect_server_send_paging(client, data, len);
		}
		return;
	}

	log_print(0, "LCE: Paging %02X%02X%02X via %s\n",
		data[0] & 0xFF, data[1] & 0xFF, data[2] & 0xFF,
		inet_ntoa(ntohl(client->ipad)));

	buf[0] = htons(DECT_MSG_PAGING);
	buf[1] = htons(len);

	memcpy((void *)&buf[2], data, len);

	dect_server_send(client, (char *)buf, len + 4);
}
