
#include "mcf5282.h"

#include "eeprom.h"
#include "timer.h"
#include "if.h"
#include "ip.h"
#include "arp.h"

#include "icmp.h"
#include "tcp.h"
#include "udp.h"

#include "term/terminal.h"


static void cmd_ip_address(struct terminal *term, int reason)
{
	unsigned int ip, x;

	if (reason == TERM_RSN_HINT) {
		term_help_line(term, "A.B.C.D/M", "IP address and network mask");
		return;
	}

	if (reason == TERM_RSN_EXEC) {
		/* Get system IP address */
		ip = term_get_ip(term);
		if (!ip) {
			bprintf(term->out, "Bad IP address.\r\n");
			return;
		}
		if (eeprom.ip_addr != ip) {
			eeprom.ip_addr = ip;
			arp_init();
			tcp_init();
			telnet_init();
		}
		if (term->line[term->line_pos] != '/') return;

		/* Get network mask */
		term->line_pos++;
		x = term_get_int(term, 10);
		if (x > 32) {
			bprintf(term->out, "Bad network mask (%i)\r\n", x);
			return;
		}
		eeprom.ip_mask = x;

		/* Get default router */
		ip = term_get_ip(term);
		if (!ip) return;
		eeprom.ip_router = ip;
	}
}

void ip_init()
{
	struct term_command *cmd_ip;

	/* Init stack */
	arp_init();
	tcp_init();

	/* Register commands */
	cmd_ip = term_reg_command(NULL, "ip", "Configure internet protocol", NULL);
	term_reg_command(cmd_ip, "address", "Set system IP address", cmd_ip_address);
}

uint16 ip_chksum(uint16 csum, uint16 *data, int num)
{
	int chksum, ichksum;
	uint16 temp;

	chksum = csum;
	for (; num > 0; num-=2, data++)
	{
		temp = *data;
		if (num == 1) temp &= 0xFF00;	/* Zero last byte if odd */
		ichksum = chksum + temp;
		ichksum = ichksum & 0x0000FFFF;
		if ((ichksum < temp) || (ichksum < chksum))
		{
			ichksum += 1;
			ichksum = ichksum & 0x0000FFFF;
		}
		chksum = ichksum;
	}
	return (uint16)~chksum;
}

/*
 * Receive packet handler
 */
void ip_handler(IF_PACKET *pkt)
{
	ip_frame_hdr *ip_hdr;
	uint8 *ip_data;
	uint16 ip_size, ip_csum;

	ip_hdr = (ip_frame_hdr *)pkt->data;

	/* Check to see if addressed to me */
	if (ip_hdr->dest_addr != eeprom.ip_addr) return;

	/* Verify packet checksum */
	ip_csum = ip_hdr->checksum;
	ip_hdr->checksum = 0;
	if (ip_chksum(0, (uint16 *)ip_hdr, IP_IHL(ip_hdr) * 4) != ip_csum) return;

	/* Check packet length */
	if (ip_hdr->total_length > pkt->size) return;
	ip_size = ip_hdr->total_length - IP_IHL(ip_hdr) * 4;
	ip_data = IP_DATA(ip_hdr);

	/* Store MAC address to ARP table for reply packet */
	arp_merge(ip_hdr->source_addr, pkt->addr);

	/* Blink status LED to show network activity */
	/* tmr_gp_blink(100); */

	/* Forward to appropriate handler */
	switch (ip_hdr->protocol) {
		case IP_PROTO_ICMP:
			icmp_handler(ip_hdr, ip_data, ip_size);
			break;
		case IP_PROTO_TCP:
			tcp_handler(ip_hdr, ip_data, ip_size);
			break;
		case IP_PROTO_UDP:
			udp_handler(ip_hdr, ip_data, ip_size);
			break;
	}
}

/*
 *
 */
int ip_send(ip_frame_hdr *hdr, IF_BUFFER *buf)
{
	IF_PACKET pkt;
	IF_BUFFER hdr_buf, *data;
	uint32 send_ip, mask;

	/* Prepare IP header */
	hdr->version_ihl = 0x45;
	hdr->ttl = 64;
	hdr->flags_frag_offset = 0;
	hdr->identification = 0;
	hdr->service_type = 0;
	hdr->source_addr = eeprom.ip_addr;
	hdr->checksum = 0;

	/* Calculate total packet size */
	hdr->total_length = 20;
	data = buf;
	do {
		hdr->total_length += data->size;
	} while (data = data->next);

	/* Calculate checksum */
	hdr->checksum = ip_chksum(0, (uint16 *)hdr, 20);

	/* Prepare ethernet header */
	send_ip = hdr->dest_addr;
	mask = 0xFFFFFFFF << (32 - eeprom.ip_mask);
	if ((send_ip & mask) != (eeprom.ip_addr & mask)) {
		/* Destination IP not in local network */
		send_ip = eeprom.ip_router;
	}
	if (arp_lookup(send_ip, (uint8 *)&pkt.addr)) {
		/* Failed to lookup destination MAC address */
		arp_request(send_ip);
		return 1;
	}
	pkt.type = ETH_P_IP;

	/* Prepare buffer and send frame */
	hdr_buf.data = (uint8 *)hdr;
	hdr_buf.size = 20;
	hdr_buf.next = buf;
	if_send(&pkt, &hdr_buf);
	return 0;
}

/*
 *
 */
void ip_process()
{
	tcp_process();
}
