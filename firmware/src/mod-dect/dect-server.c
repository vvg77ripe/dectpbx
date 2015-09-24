
#include <mcf5282.h>
#include "config.h"

#include "network/udp.h"

#include "dect.h"
#include "dect-server.h"


static void dect_serv_recv_lapc(struct msg_lapc_data *pkt, uint16 len)
{
	int i, j;
	mbc_inst_t *mbc;
	uint8 *pdata, plen;

	pdata = (uint8 *)pkt + sizeof(struct msg_lapc_data);
	plen = len - sizeof(struct msg_lapc_data);

	for (i = 0; i < DECT_MBC_MAX; i++) {
		if ( (dect->mbc[i].pmid == pkt->pmid) && (dect->mbc[i].ecn == pkt->ecn) ) {
			/* MBC found*/
			mbc = &dect->mbc[i];
			mbc->uplane = pkt->uplane;

			/* Free space check */
			if ((DECT_CS_MAX_FLEN - mbc->cs_send_len) < len) return;
			if (plen % 5) return;

			/* Copy data packet */
			for (j = 0; j < plen; j++)
				mbc->cs_send[mbc->cs_send_len+j] = pdata[j];
			mbc->cs_send_len += plen;
			break;
		}
	}
}

static void dect_serv_recv_paging(uint8 *data, uint16 len)
{
	if (len < 3) return;

	dect->ptail[0] = data[0];
	dect->ptail[1] = data[1];
	dect->ptail[2] = data[2];
	dect->ptail[4] = 7;
	term_log_all("DECT: Paging message %X %X %X\r\n", data[0], data[1], data[2]);
}

static void dect_serv_recv_voice(uint8 *data, uint16 len)
{
	struct msg_voice_data *msg;
	uint8 *voice;

	msg = (struct msg_voice_data *)data;
	voice = (uint8 *)data + sizeof(struct msg_voice_data);
	dect_mbc_voice_recv(msg->pmid, msg->ecn, voice, len - sizeof(struct msg_voice_data));
}

/* dect_serv_handler()
 *   Called when received UDP packed from DECT server.
 */
void dect_serv_handler(uint32 server_ip, uint8 *data, uint16 len)
{
	struct dect_packet *pkt;
	void *pdata;
	uint16 plen;

	/* Check if module is initialized */
	if (!dect) return;

	pkt = (struct dect_packet *)data;
	if (len < sizeof(struct dect_packet)) return;

	/* Check sign */
	if (pkt->sign[0] != 'D') return;
	if (pkt->sign[1] != 'S') return;

	pdata = (uint8 *)pkt + sizeof(struct dect_packet);
	plen = pkt->len;

	switch (pkt->type) {
		case DECT_MSG_LAPC_DATA:
			dect_serv_recv_lapc((struct msg_lapc_data *)pdata, plen);
			break;
		case DECT_MSG_PAGING:
			dect_serv_recv_paging(pdata, plen);
			break;

		case DECT_MSG_VOICE:
			dect_serv_recv_voice(pdata, plen);
			break;
	}
}

void dect_serv_send(uint8 *data, uint16 len)
{
	struct dect_packet pkt;
	IF_BUFFER if_hdr, if_data;

	if (!dect->config.dect_server) return;

	/* Packet header */
	pkt.sign[0] = 'F';
	pkt.sign[1] = 'P';
	pkt.fpid = dect->config.fpid;
	pkt.rfpi[0] = dect->rfpi[0];
	pkt.rfpi[1] = dect->rfpi[1];
	pkt.rfpi[2] = dect->rfpi[2];
	pkt.rfpi[3] = dect->rfpi[3];
	pkt.rfpi[4] = dect->rfpi[4];
	pkt.rfpi[5] = dect->rfpi[5];

	/* Send packet */
	if_hdr.data = (uint8 *)&pkt;
	if_hdr.size = sizeof(pkt) - 4;
	if_hdr.next = &if_data;
	if_data.data = data;
	if_data.size = len;
	if_data.next = NULL;
	udp_send(0, DECT_CLIENT_PORT, dect->config.dect_server, DECT_SERVER_PORT, &if_hdr);
}

void dect_serv_buffer_add(dect_buf_t *buffer, uint16 cmd, uint16 size, void *data)
{
	uint16 *hdr = (uint16 *)(buffer->packet + buffer->size);

	/* Store packet header */
	hdr[0] = cmd;
	hdr[1] = size;
	buffer->size += 4;

	/* Copy packet data */
	if (size && data) {
		memcpy(buffer->packet + buffer->size, data, size);
		buffer->size += size;
	}
}

void dect_serv_send_ping()
{
	int i, mbc_count;
	uint8	buf[100];
	dect_buf_t buffer;
	struct msg_sysinfo m_sysinfo;

	/* Prepare buffer */
	buffer.packet = buf;
	buffer.size = 0;

	/* PING message */
	dect_serv_buffer_add(&buffer, DECT_MSG_PING, 0, NULL);

	/* SYSINFO message */
	mbc_count = 0;
	for (i = 0; i < DECT_MBC_MAX; i++) {
		if (dect->mbc[i].pmid) mbc_count++;
	}
	m_sysinfo.v_mbclist = 0;
	m_sysinfo.mbc_count = mbc_count;
	m_sysinfo.hlcap = 0;
	dect_serv_buffer_add(&buffer, DECT_MSG_SYSINFO, sizeof(m_sysinfo), &m_sysinfo);

	/* Send packet */
	dect_serv_send(buffer.packet, buffer.size);
}

void dect_serv_send_lapc(uint32 pmid, uint8 ecn, uint8 *data, uint8 len)
{
	uint16 buf[64];
	struct msg_lapc_data *msg;
	uint8 *sdata;
	int i;

	msg = (struct msg_lapc_data *)&buf[2];
	sdata = (uint8 *)msg + sizeof(struct msg_lapc_data);
	buf[0] = DECT_MSG_LAPC_DATA;
	buf[1] = sizeof(struct msg_lapc_data) + len;

	msg->pmid = pmid;
	msg->ecn = ecn;
	for (i = 0; i < len; i++)
		*sdata++ = data[i];

	dect_serv_send((uint8 *)buf, buf[1] + 4);
}

void dect_serv_send_voice(uint32 pmid, uint8 ecn, uint8 *data, uint8 len)
{
	uint16 buf[128];
	struct msg_voice_data *msg;
	uint8 *sdata;
	int i;

	buf[0] = DECT_MSG_VOICE;
	buf[1] = len + sizeof(struct msg_voice_data);
	msg = (struct msg_voice_data *)&buf[2];
	sdata = (uint8 *)msg + sizeof(struct msg_voice_data);

	msg->pmid = pmid;
	msg->ecn = ecn;
	msg->seq = dect->frame + 16 * dect->mframe;

	for (i = 0; i < len; i++)
		*sdata++ = data[i];

	dect_serv_send((uint8 *)buf, buf[1] + 4);
}
