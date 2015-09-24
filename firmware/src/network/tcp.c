
#include "mcf5282.h"

#include "eeprom.h"
#include "if.h"
#include "ip.h"

#include "tcp.h"


static struct tcp_socket *tcp_sockets[MAX_TCP_SOCKETS];


static void tcp_send(ip_frame_hdr *ip, struct tcphdr *tcp, IF_BUFFER *data)
{
	IF_BUFFER tcp_buf, *buf;
	struct tcp_pseudo_hdr pseudo;

	/* TCP pseudo header */
	pseudo.ip_src = eeprom.ip_addr;
	pseudo.ip_dst = ip->dest_addr;
	pseudo.zero = 0;
	pseudo.ptcl = IP_PROTO_TCP;

	/* Calculate packet size */
	pseudo.length = 20;
	buf = data;
	while (buf) {
		pseudo.length += buf->size;
		buf = buf->next;
	}

	/* IP Header */
	ip->protocol = IP_PROTO_TCP;

	/* TCP Header */
	tcp->doff = 0x50;		/* We send always 20-byte tcphdr */

	/* Calculate checksum */
	tcp->checksum = 0;
	tcp->checksum = ip_chksum(~ip_chksum(0, (uint16 *)&pseudo, sizeof(pseudo))
		, (uint16 *)tcp, sizeof(struct tcphdr));
	buf = data;
	while (buf) {
		tcp->checksum = ip_chksum(~tcp->checksum, (uint16*)buf->data, buf->size);
		buf = buf->next;
	}

	/* Prepare buffers and send frame */
	tcp_buf.data = (uint8 *)tcp;
	tcp_buf.size = sizeof(struct tcphdr);
	tcp_buf.next = data;
	ip_send(ip, &tcp_buf);
}

static void tcp_send_reset(ip_frame_hdr *ip, struct tcphdr *tcp)
{
	uint16 port;

	/* IP Header */
	ip->dest_addr = ip->source_addr;

	/* TCP Header */
	port = tcp->sport;
	tcp->sport = tcp->dport;
	tcp->dport = port;
	tcp->flags = TH_RST | TH_ACK;
	tcp->ack = tcp->seq + 1;
	tcp->seq = 0;
	tcp->urg_ptr = 0;

	/* Send TCP packet */
	tcp_send(ip, tcp, NULL);
}

static void tcp_prepare_headers(struct tcp_socket *sock, ip_frame_hdr *ip, struct tcphdr *tcp)
{
	/* IP Header */
	ip->source_addr = sock->local_ip;
	ip->dest_addr = sock->remote_ip;

	/* TCP Header */
	tcp->sport = sock->local_port;
	tcp->dport = sock->remote_port;
	tcp->seq = sock->snd_una;
	if (sock->seq_syn == tcp->seq) tcp->seq++;
	tcp->ack = sock->rcv_nxt;

	tcp->urg_ptr = 0;
	tcp->window = fifo_free_size(&sock->rbuf);
}

static struct tcp_socket *tcp_find_socket(ip_frame_hdr *ip, struct tcphdr *tcp)
{
	int i;

	for (i = 0; i < MAX_TCP_SOCKETS; i++) {
		if (tcp_sockets[i]) {
			/* Check local port */
			if (tcp_sockets[i]->local_port != tcp->dport) continue;

			/* Check remote side for connected sockets */
			if (tcp_sockets[i]->remote_ip) {
				if (tcp_sockets[i]->remote_ip != ip->source_addr) continue;
				if (tcp_sockets[i]->remote_port != tcp->sport) continue;
			}

			/* Valid socket found */
			return tcp_sockets[i];
		}
	}
	return NULL;
}

static void tcp_send_ack(struct tcp_socket *sock)
{
	IF_BUFFER sdata;
	ip_frame_hdr ip;
	struct tcphdr tcp;

	sock->snd_nxt = sock->sbuf.stop;

	sdata.size = fifo_cdata_size(&sock->sbuf);
	if (sdata.size) {
		tcp_prepare_headers(sock, &ip, &tcp);
		tcp.flags = TH_ACK;
		if (sdata.size) {
			if (sock->sock_flags & SF_PUSH) tcp.flags |= TH_PUSH;
			sdata.data = &sock->sbuf.buf[sock->sbuf.start];
			sdata.next = NULL;
			tcp_send(&ip, &tcp, &sdata);
		} else {
			tcp_send(&ip, &tcp, NULL);
		}
	}
}

/*
 *
 */
void tcp_init()
{
	int i;

	/* Zero socket list */
	for (i = 0; i < MAX_TCP_SOCKETS; i++)
		tcp_sockets[i] = NULL;

}

/*
 *
 */
void tcp_process()
{
	int i;
	struct tcp_socket *sock;

	for (i = 0; i < MAX_TCP_SOCKETS; i++)
		if (tcp_sockets[i]) {
			sock = tcp_sockets[i];

			/* Check if we have any new data to send */
			if (sock->snd_nxt != sock->sbuf.stop)
				tcp_send_ack(sock);
		}
}

/*
 * TCP Receive packet handler
 */
void tcp_handler(ip_frame_hdr *ip, uint8 *data, uint32 size)
{
	IF_BUFFER sdata;
	unsigned char *rdata;
	struct tcphdr *tcp_hdr;
	struct tcp_socket *sock;
	uint32 seg_seq, seg_ack, seg_len, iss;

	tcp_hdr = (struct tcphdr *)data;

	/* Find socket */
	sock = tcp_find_socket(ip, tcp_hdr);
	if (!sock) {
		if ( !(tcp_hdr->flags & TH_RST) ) tcp_send_reset(ip, tcp_hdr);
		return;
	}

	seg_seq = tcp_hdr->seq;
	seg_ack = tcp_hdr->ack;
	seg_len = size - (tcp_hdr->doff >> 4) * 4;
	rdata = (unsigned char *)&data[(tcp_hdr->doff >> 4) * 4];
	if ((tcp_hdr->flags & TH_SYN) || (tcp_hdr->flags & TH_FIN))
		seg_len++;

	/*
	 * TCP State Machine
	 */

	switch (sock->sock_state) {
		case TCP_LISTEN:
			/* RST */
			if (tcp_hdr->flags & TH_RST) return;

			/* ACK */
			if (tcp_hdr->flags & TH_ACK) {
				tcp_prepare_headers(sock, ip, tcp_hdr);
				tcp_hdr->seq = seg_ack;
				tcp_hdr->flags = TH_RST;
				tcp_send(ip, tcp_hdr, NULL);
				return;
			}

			/* SYN */
			if (tcp_hdr->flags & TH_SYN) {
				/* SEQ */
				iss = MCF5282_GPTA_GPTCNT;
				sock->rcv_nxt = seg_seq + 1;
				sock->rcv_unr = sock->rcv_nxt;
				sock->snd_una = iss;
				sock->seq_syn = iss;
				sock->seq_fin = iss - 1;

				/* New connection request */
				sock->remote_ip = ip->source_addr;
				sock->remote_port = tcp_hdr->sport;
				sock->sock_state = TCP_SYN_RECV;

				/* Send SYN, ACK*/
				tcp_prepare_headers(sock, ip, tcp_hdr);
				tcp_hdr->flags = TH_SYN | TH_ACK;
				tcp_hdr->seq = iss;
				tcp_hdr->ack = sock->rcv_nxt;
				tcp_send(ip, tcp_hdr, NULL);
				return;
			}
			return;

		case TCP_SYN_SENT:
			/* ACK */
			if (tcp_hdr->flags & TH_ACK) {
				if ((seg_ack >= sock->snd_una)) {
					if ( !(tcp_hdr->flags & TH_RST) ) {
						tcp_prepare_headers(sock, ip, tcp_hdr);
						tcp_hdr->seq = seg_ack;
						tcp_hdr->flags = TH_RST;
						tcp_send(ip, tcp_hdr, NULL);
					}
					return;
				}
			}

			/* RST */
			if (tcp_hdr->flags & TH_RST) {
				sock->sock_state = TCP_CLOSE;
				return;
			}
			return;
	}

	/* Sequence check */
	if ((seg_seq < sock->rcv_nxt)
		|| (seg_seq > (sock->rcv_nxt + sock->rcv_wnd))) {
			/* Bad sequence - send ACK */
			if ( !(tcp_hdr->flags & TH_RST) ) {
				tcp_prepare_headers(sock, ip, tcp_hdr);
				tcp_hdr->flags = TH_ACK;
				tcp_send(ip, tcp_hdr, NULL);
				return;
			}
	}

	/* RST */
	if (tcp_hdr->flags & TH_RST) switch (sock->sock_state) {
		case TCP_SYN_RECV:
			tcp_sock_listen(sock);
			return;
		default:
			sock->sock_state = TCP_CLOSE;
			return;
	}

	/* SYN */
	if (tcp_hdr->flags & TH_SYN) {
		tcp_prepare_headers(sock, ip, tcp_hdr);
		tcp_hdr->seq = seg_ack;
		tcp_hdr->flags = TH_RST;
		tcp_send(ip, tcp_hdr, NULL);
		return;
	}

	/* !ACK */
	if ( !(tcp_hdr->flags & TH_ACK) ) return;

	switch (sock->sock_state) {
		case TCP_SYN_RECV:
			sock->sock_state = TCP_ESTABLISHED;
			sock->sock_flags |= SF_CONNECTED;
			/* We have ACKed our SYN */
			sock->snd_una++;
			break;

		case TCP_ESTABLISHED:
			sdata.size = seg_ack - sock->snd_una;
			if (sdata.size <= fifo_data_size(&sock->sbuf)) {
				sock->sbuf.start += sdata.size;
				if (sock->sbuf.start >= sock->sbuf.length) sock->sbuf.start -= sock->sbuf.length;
			}
			sock->snd_una = seg_ack;
			break;

		case TCP_LAST_ACK:
			sock->sock_state = TCP_CLOSE;
			return;
	}

	/* FIN */
	if (tcp_hdr->flags & TH_FIN) {
		sock->rcv_nxt = seg_seq + seg_len;
		tcp_prepare_headers(sock, ip, tcp_hdr);
		tcp_hdr->flags = TH_ACK;
		tcp_send(ip, tcp_hdr, NULL);

		switch (sock->sock_state) {
			case TCP_SYN_RECV:
			case TCP_ESTABLISHED:
				sock->sock_state = TCP_CLOSE_WAIT;
				break;
		}

		return;
	}

	/* Segment Data */
	sdata.size = fifo_cdata_size(&sock->sbuf);
	if (seg_len || sdata.size) {
		sock->rcv_nxt = seg_seq + seg_len;
		sock->snd_nxt = sock->sbuf.stop;
		tcp_prepare_headers(sock, ip, tcp_hdr);
		tcp_hdr->flags = TH_ACK;
		/* Receive data */
		if (seg_len) {
			fifo_write(&sock->rbuf, rdata, seg_len);
		}
		/* Transmit data */
		if (sdata.size) {
			if (sock->sock_flags & SF_PUSH) tcp_hdr->flags |= TH_PUSH;
			sdata.data = &sock->sbuf.buf[sock->sbuf.start];
			sdata.next = NULL;
			tcp_send(ip, tcp_hdr, &sdata);
		} else {
			tcp_send(ip, tcp_hdr, NULL);
		}
	}
}

/* *********************************************************************
 * Socket functions
 */

void *tcp_sock_create(struct tcp_socket *sock, uint16 port)
{
	int i;

	if (sock) {
		sock->local_ip = eeprom.ip_addr;
		sock->local_port = port;
		sock->sock_state = TCP_CLOSE;
		sock->sock_flags = 0;

		sock->snd_nxt = sock->sbuf.stop;
	}

	for (i = 0; i < MAX_TCP_SOCKETS; i++) {
		if (!tcp_sockets[i]) {
			tcp_sockets[i] = sock;
			return sock;
		}
	}

	return sock;
}

void tcp_sock_listen(struct tcp_socket *sock)
{
	if (!sock) return;

	sock->remote_ip = 0;
	sock->remote_port = 0;
	sock->sock_state = TCP_LISTEN;
}

void tcp_sock_close(struct tcp_socket *sock)
{
	ip_frame_hdr ip;
	struct tcphdr tcp;

	if (!sock) return;

	sock->sbuf.start = sock->sbuf.stop;
	sock->snd_nxt = sock->sbuf.stop;

	switch (sock->sock_state) {
		case TCP_CLOSE_WAIT:
			/* Send FIN and go to LAST_ACK */
			tcp_prepare_headers(sock, &ip, &tcp);
			tcp.flags = TH_FIN | TH_ACK;
			tcp_send(&ip, &tcp, NULL);
			sock->sock_state = TCP_LAST_ACK;
			break;
	}
}
