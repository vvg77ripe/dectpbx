
#ifndef _NETWORK_TCP_H
#define _NETWORK_TCP_H

#include <stdio.h>

#define MAX_TCP_SOCKETS		4

#define TH_FIN		0x01
#define TH_SYN		0x02
#define TH_RST		0x04
#define TH_PUSH		0x08
#define TH_ACK		0x10
#define TH_URG		0x20

/* Socket flags */
#define SF_CONNECTED	1
#define SF_PUSH			2

enum
{
  TCP_ESTABLISHED = 1,
  TCP_SYN_SENT,
  TCP_SYN_RECV,
  TCP_FIN_WAIT1,
  TCP_FIN_WAIT2,
  TCP_TIME_WAIT,
  TCP_CLOSE,
  TCP_CLOSE_WAIT,
  TCP_LAST_ACK,
  TCP_LISTEN,
  TCP_CLOSING   /* now a valid state */
};


struct tcphdr {
	uint16	sport;
	uint16	dport;
	uint32	seq;
	uint32	ack;
	uint8	doff;
	uint8	flags;
	uint16	window;
	uint16	checksum;
	uint16	urg_ptr;
};

struct tcp_pseudo_hdr {
	uint32	ip_src;
	uint32	ip_dst;
	uint8	zero;
	uint8	ptcl;
	uint16	length;
};

struct tcp_socket {
	uint8	sock_state;
	uint8	sock_flags;
	uint32	remote_ip;
	uint16	remote_port;
	uint32	local_ip;
	uint16	local_port;
	/* RFC 793 */
	uint32	rcv_unr;
	uint32	rcv_nxt;
	uint16	rcv_wnd;
	uint32	snd_una;
	uint32	snd_nxt;
	/* flags positions */
	uint32	seq_syn;
	uint32	seq_fin;
	/* Data buffers */
	fifo_buffer	rbuf;
	fifo_buffer	sbuf;
};


void tcp_init(void);
void tcp_process(void);
void tcp_handler(ip_frame_hdr *ip, uint8 *data, uint32 size);

void *tcp_sock_create(struct tcp_socket *sock, uint16 port);
void tcp_sock_listen(struct tcp_socket *sock);
void tcp_sock_close(struct tcp_socket *sock);

#endif
