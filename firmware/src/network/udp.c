
#include "mcf5282.h"

#include "eeprom.h"

#include "if.h"
#include "ip.h"
#include "udp.h"
#include "rtp.h"

#include "voip/sip.h"
#include "mod-dect/dect-server.h"
#include "mod-lsic/lsic.h"


/*
 * UDP Receive packet handler
 */
void udp_handler(ip_frame_hdr *ip, uint8 *data, uint32 size)
{
	IF_BUFFER buf;
	udp_frame_hdr *udp;
	uint8 *udp_data;
	uint16 udp_size;

	udp = (udp_frame_hdr *)data;
	udp_data = &data[sizeof(udp_frame_hdr)];

	udp_size = udp->length - sizeof(udp_frame_hdr);
	if (udp_size > size) return;

	switch (udp->dport) {
		case UDP_PORT_ECHO:
			/* Echo port */
			buf.data = udp_data;
			buf.size = udp_size;
			buf.next = NULL;
			udp_send(ip->dest_addr, udp->dport, ip->source_addr, udp->sport, &buf);
			return;

		case UDP_PORT_SIP:
			sip_handler(ip->source_addr, udp->sport, ip->dest_addr, udp->dport,
				udp_data, udp_size);
			return;

		case UDPC_RTP_START:
			rtp_handler(udp_data, udp_size);
			return;

		case UDPC_TFTP_START:
			tftp_handler(udp->sport, udp->dport, udp_data, udp_size);
			return;

		case DECT_CLIENT_PORT:
			dect_serv_handler(ip->source_addr, udp_data, udp_size);
			return;

		case LSIC_CLIENT_PORT:
			lsic_serv_handler(ip->source_addr, udp->sport, udp_data, udp_size);
			return;
	}

}

/*
 *
 */
void udp_send(uint32 saddr, uint16 sport, uint32 daddr, uint16 dport, IF_BUFFER *data)
{
	IF_BUFFER buf, *b;
	ip_frame_hdr ip;
	udp_frame_hdr udp;
	udp_pseudo_hdr pseudo;

	/* IP Header */
	ip.source_addr = saddr;
	if (!saddr) ip.source_addr = eeprom.ip_addr;
	ip.dest_addr = daddr;
	ip.protocol = IP_PROTO_UDP;

	/* Calculate packet size */
	udp.length = sizeof(udp);
	b = data;
	while (b) {
		udp.length += b->size;
		b = b->next;
	}

	/* UDP pseudo header */
	pseudo.ip_src = ip.source_addr;
	pseudo.ip_dst = ip.dest_addr;
	pseudo.length = udp.length;
	pseudo.zero = 0;
	pseudo.ptcl = IP_PROTO_UDP;

	/* UDP Header */
	udp.sport = sport;
	udp.dport = dport;
	udp.chksum = 0;

	/* Calculate checksum */
	udp.chksum = ip_chksum(~ip_chksum(0, (uint16 *)&pseudo, sizeof(pseudo))
		, (uint16 *)&udp, sizeof(udp));
	b = data;
	while (b) {
		udp.chksum = ip_chksum(~udp.chksum, (uint16 *)b->data, b->size);
		b = b->next;
	}

	/* Prepare buffers and send frame */
	buf.data = (uint8 *)&udp;
	buf.size = sizeof(udp);
	buf.next = data;
	ip_send(&ip, &buf);
}
