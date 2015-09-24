
#ifndef _NETWORK_UDP_H
#define _NETWORK_UDP_H

#include "network/if.h"
#include "network/ip.h"

#define UDP_PORT_ECHO	7
#define UDP_PORT_TFTP	69
#define UDP_PORT_SIP	5060

/* Client ports */
#define UDPC_RTP_START	16384	/* RTP */
#define UDPC_RTP_END	16399
#define UDPC_TFTP_START	16400	/* TFTP */
#define UDPC_TFTP_END	16419

typedef struct
{
	uint16		sport;
	uint16		dport;
	uint16		length;
	uint16		chksum;
} udp_frame_hdr;

typedef struct {
	uint32	ip_src;
	uint32	ip_dst;
	uint8	zero;
	uint8	ptcl;
	uint16	length;
} udp_pseudo_hdr;



void udp_handler(ip_frame_hdr *ip, uint8 *data, uint32 size);
void udp_send(uint32 saddr, uint16 sport, uint32 daddr, uint16 dport, IF_BUFFER *data);

#endif
