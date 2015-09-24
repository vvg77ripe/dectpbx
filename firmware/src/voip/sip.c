
#include <mcf5282.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "network/if.h"
#include "network/ip.h"
#include "network/udp.h"

#include "term/terminal.h"

#include "sip.h"

static char sdp_body[MAX_SDP_BODY];


/*
 *
 */
static int sdp_handler(sip_header *sip, fifo_buffer *reply)
{
	/* Test reply */
	bprintf(reply, "v=0\r\n");
	bprintf(reply, "o=TEST 1 1 IN IP4 85.159.40.55\r\n");
	/* session description*/
	bprintf(reply, "s=MCF VoIP Session\r\n");
	/* contact ip address */
	bprintf(reply, "c=IN IP4 85.159.40.55\r\n");
	/* time */
	bprintf(reply, "t=0 0\r\n");
	/* media stream: rtp audio payload 8 */
	bprintf(reply, "m=audio 16384 RTP/AVP 8\r\n");
	/* rtpmap */
	bprintf(reply, "a=rtpmap:8 PCMA/8000/1\r\n");
	return 0;
}


static char *sip_reply_msg(uint16 code)
{
	switch (code) {
		case 100:
			return "Trying";
		case 180:
			return "Ringing";
		case 200:
			return "OK";
		case 486:
			return "Busy Here";
	}

	return "No description of this code";
}

static void sip_send_reply(sip_header *hdr, uint16 code, IF_BUFFER *body)
{
	fifo_buffer reply;
	IF_BUFFER send;
	uint8 buf[SIP_TMP_SIZE];

	/* Prepare circular buffer */
	reply.buf = buf;
	reply.length = SIP_TMP_SIZE;
	reply.start = 0;
	reply.stop = 0;

	/* Reply code */
	bprintf(&reply, "SIP/2.0 %i %s\r\n", code, sip_reply_msg(code));
	hdr->response_code = code;

	/* Headers */
	if (hdr->hvia)
		bprintf(&reply, "Via: %s\r\n", hdr->hvia);
	if (hdr->hfrom)
		bprintf(&reply, "From: %s\r\n", hdr->hfrom);
	if (hdr->hto)
		bprintf(&reply, "To: %s\r\n", hdr->hto);
	if (hdr->hcseq)
		bprintf(&reply, "CSeq: %s\r\n", hdr->hcseq);
	if (hdr->hcallid)
		bprintf(&reply, "Call-ID: %s\r\n", hdr->hcallid);

	if (body) {
		/* We send only sdp body */
		bprintf(&reply, "Content-Type: application/sdp\r\n");
		bprintf(&reply, "Content-Length: %i\r\n", body->size);
	} else {
		bprintf(&reply, "Content-Length: 0\r\n");
	}
	bprintf(&reply, "\r\n");

	/* Debug log */
	term_log_all("SIP Reply: %i\r\n", code);

	/* Prepare buffers and send reply */
	send.data = reply.buf;
	send.size = reply.stop;
	send.next = body;
	udp_send(hdr->saddr, hdr->sport, hdr->daddr, hdr->dport, &send);
}

static int sip_parse(uint8 *data, uint16 size, sip_header *hdr)
{
	char *hdr_name, *hdr_value;

	memset(hdr, 0, sizeof(sip_header));
	hdr->method_name = data;

	while (size) {
		if (data[0] == ' ') break;
		data++; size--;
	}
	if (size < 2) return 1;

	/* Method name found */
	data[0] = 0;
	data++; size--;

	if (!strcmp(hdr->method_name, "SIP/2.0")) {
		/* This is a response packet */
		hdr->method_name = NULL;

		/* Parse response code */
		if (data[3] != ' ') return 1;
		data[3] = 0;
		hdr->response_code = atoi(data);
		if (!hdr->response_code) return 1;
		data += 4; size -= 4;
	} else {
		if (!strcmp(hdr->method_name, "INVITE"))
			hdr->method_id = SIP_METHOD_INVITE;
		if (!strcmp(hdr->method_name, "CANCEL"))
			hdr->method_id = SIP_METHOD_CANCEL;
		if (!strcmp(hdr->method_name, "ACK"))
			hdr->method_id = SIP_METHOD_ACK;
		if (!strcmp(hdr->method_name, "BYE"))
			hdr->method_id = SIP_METHOD_BYE;

		hdr->sip_uri = data;
	}

	/* Go to next line */
	while (size) {
		if ((data[0] == 13) && (data[1] == 10)) break;
		if (data[0] == ' ') data[0] = 0;
		data++; size--;
	}
	if (size < 2) return 1;
	data += 2; size -= 2;

	/* Parse headers */
	hdr_name = data;
	hdr_value = NULL;
	while (size) {
		if ((hdr_name == (char *)data) && (data[0] == 13)) {
			/* Empty line - end of headers */
			return 0;
		}
		if (data[0] == 13) {
			/* End of line */
			data[0] = 0;

			/* Fill appropriate value pointers */
			if (!strcmp(hdr_name, "Via")) {
				if (!hdr->hvia) hdr->hvia = hdr_value;
			}
			if (!strcmp(hdr_name, "From")) hdr->hfrom = hdr_value;
			if (!strcmp(hdr_name, "To")) hdr->hto = hdr_value;
			if (!strcmp(hdr_name, "CSeq")) hdr->hcseq = hdr_value;
			if (!strcmp(hdr_name, "Call-ID")) hdr->hcallid = hdr_value;

			/* Skip LF */
			data += 2; size -= 2;
			hdr_name = data;
			hdr_value = NULL;
			continue;
		}

		if (!hdr_value) {
			if ((data[0] == ' ') || (data[0] == ':')) {
				data[0] = 0;
				data++; size--;
				/* seek to header value */
				while ((data[0] == ' ') || (data[0] == ':')) {
					data++; size--;
					if (!size) return 1;
				}
				hdr_value = data;
			}
		}

		data++; size--;
	}

	return 1;
}

void sip_handler(uint32 saddr, uint16 sport, uint32 daddr, uint16 dport, uint8 *data, uint16 size)
{
	sip_header sip;
	IF_BUFFER sip_body;
	fifo_buffer sdp;
	int r;

	/* Parse SIP header */
	if (sip_parse(data, size, &sip)) return;

	/*
	 * User Agent Client
	 */
	if (sip.response_code) {
		return;
	}

	/* Debug log */
	term_log_all("SIP Request: %s '%s'\r\n", sip.method_name, sip.sip_uri);

	/*
	 * User Agent Server
	 */
	switch (sip.method_id) {
		case SIP_METHOD_INVITE:
			/* Parse SDP and generate response */
			sdp.buf = sdp_body;
			sdp.length = MAX_SDP_BODY;
			sdp.start = 0;
			sdp.stop = 0;

			r = sdp_handler(&sip, &sdp);

			/* Send response*/
			sip.saddr = daddr;
			sip.sport = dport;
			sip.daddr = saddr;
			sip.dport = sport;
			if (!r) {
				sip_body.data = sdp_body;
				sip_body.size = sdp.stop;
				sip_body.next = NULL;
				sip_send_reply(&sip, 200, &sip_body);
			} else {
				/* Not acceptable here */
				sip_send_reply(&sip, 486, NULL);
			}
			return;

		case SIP_METHOD_BYE:
			sip.saddr = daddr;
			sip.sport = dport;
			sip.daddr = saddr;
			sip.dport = sport;
			sip_send_reply(&sip, 200, NULL);
			return;
	}
}
