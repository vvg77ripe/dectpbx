
#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <math.h>

#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <netinet/in.h>

#include "version.h"
#include "cfgfile.h"
#include "terminal.h"
#include "server.h"
#include "dlc.h"
#include "nwk.h"
#include "sip.h"

#include "g711.h"


#define CONFIG_FILE		"./dect.conf"


#define RECV_BUFFER_LEN		1500
static unsigned char buf[RECV_BUFFER_LEN];


int main()
{
	int		s_dect, s_sip;
	int		r, len, salen;
	fd_set	rfds;
	struct	timeval tv;
	struct	sockaddr_in sa;
	char	f_exit, s_in[5];
	struct termios	term;
	struct terminal *console;

	term_init();

	/* Pring hello and load config file */
	printf("DECT Server daemon version %s. http://vvg.pp.ru.\n", VERSION_STRING);
	cfg_init();
	if (cfg_load(CONFIG_FILE)) {
		printf("FATAL: Cannot load config file '%s'.\n", CONFIG_FILE);
		return 1;
	}

	/* Disable local echo and line buffering */
	tcgetattr(0, &term);
	term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, 0, &term);

	/* Initialize console */
	console = term_create();
	console->file_in = 0;
	console->file_out = 1;
	term_start(console);

	dlc_init();
	nwk_init();

	g711_init();

	s_dect = socket(AF_INET, SOCK_DGRAM, 0);
	dect_server_init(s_dect);
	s_sip = socket(AF_INET, SOCK_DGRAM, 0);
	sip_init(s_sip);

	f_exit = 0;
	while (!f_exit) {
		FD_ZERO(&rfds);
		FD_SET(s_dect, &rfds);
		FD_SET(s_sip, &rfds);
		FD_SET(0, &rfds);

		tv.tv_sec = 0;
		tv.tv_usec = 100000;
		r = select(s_sip+1, &rfds, NULL, NULL, &tv);
		if (r < 0) break;

		if (FD_ISSET(s_dect, &rfds)) {
			salen = sizeof(sa);
			len = recvfrom(s_dect, buf, RECV_BUFFER_LEN, 0, (struct sockaddr *)&sa, &salen);
			if (len > 0) {
				dect_server_recv(buf, len, &sa);
			}
		}

		if (FD_ISSET(s_sip, &rfds)) {
			salen = sizeof(sa);
			len = recvfrom(s_sip, buf, RECV_BUFFER_LEN, 0, (struct sockaddr *)&sa, &salen);
			if (len > 0) {
				sip_server_recv(buf, len, &sa);
			}
		}

		/* Keyboard input */
		if (FD_ISSET(0, &rfds)) {
			if (read(0, s_in, 1) == 1) {
				term_char(console, s_in[0]);
			}
		}

		sip_timers();
		page_timers();

		if (console) {
			if (console->f_quit) break;
		}
	}

	printf("\rExiting...\n");


	sip_done();
	dect_server_done();
	dlc_done();

	if (console) {
		term_destroy(console);
	}
	term_done();

	cfg_done();
	return 0;
}
