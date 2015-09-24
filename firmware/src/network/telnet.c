
#include <mcf5282.h>
#include <stdio.h>

#include "if.h"
#include "ip.h"
#include "tcp.h"

#include "term/terminal.h"

#include "telnet.h"

#define TELNET_RCV_SIZE		64
#define TELNET_SND_SIZE		512

static struct tcp_socket sock_telnet;
static uint8 telnet_rcv_buffer[TELNET_RCV_SIZE];
static uint8 telnet_snd_buffer[TELNET_SND_SIZE];

static struct terminal telnet_term;


static telnet_send_opt(fifo_buffer *out, char code, char opt)
{
	char buf[3];

	buf[0] = TELNET_IAC;
	buf[1] = code;
	buf[2] = opt;
	fifo_write(out, buf, 3);
}


void telnet_init()
{
	sock_telnet.rbuf.buf = telnet_rcv_buffer;
	sock_telnet.rbuf.length = TELNET_RCV_SIZE;
	sock_telnet.rbuf.start = 0;
	sock_telnet.rbuf.stop = 0;

	sock_telnet.sbuf.buf = telnet_snd_buffer;
	sock_telnet.sbuf.length = TELNET_SND_SIZE;
	sock_telnet.sbuf.start = 0;
	sock_telnet.sbuf.stop = 0;

	tcp_sock_create(&sock_telnet, 23);
	tcp_sock_listen(&sock_telnet);
}

void telnet_process()
{
	if (sock_telnet.sock_flags & SF_CONNECTED) {
		/* Just connected */
		sock_telnet.sock_flags &= ~SF_CONNECTED;
		sock_telnet.sock_flags |= SF_PUSH;

		telnet_send_opt(&sock_telnet.sbuf, TELNET_DO, TELNET_OPT_GOAHEAD);
		telnet_send_opt(&sock_telnet.sbuf, TELNET_WILL, TELNET_OPT_GOAHEAD);
		telnet_send_opt(&sock_telnet.sbuf, TELNET_WILL, TELNET_OPT_ECHO);

		//bprintf(&sock_telnet.sbuf, "Testing...\r\n");
		telnet_term.in = &sock_telnet.rbuf;
		telnet_term.out = &sock_telnet.sbuf;
		term_create(&telnet_term);
	}

	switch (sock_telnet.sock_state) {
		case TCP_CLOSE_WAIT:
			term_destroy(&telnet_term);
			tcp_sock_close(&sock_telnet);
			break;

		case TCP_CLOSE:
			tcp_sock_listen(&sock_telnet);
			break;
	}
}
