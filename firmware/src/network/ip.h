
#ifndef _NETWORK_IP_H
#define _NETWORK_IP_H

#include "network/if.h"

/* Defined IP protocols */
#define IP_PROTO_ICMP	1
#define IP_PROTO_TCP	6
#define IP_PROTO_UDP	17

/* Definition of an IP packet header */
typedef struct
{
	uint8		version_ihl;
	uint8		service_type;
	uint16		total_length;
	uint16		identification;
	uint16		flags_frag_offset;
	uint8		ttl;
	uint8		protocol;
	uint16		checksum;
	uint32		source_addr;
	uint32		dest_addr;
	uint8		options;	/* actually an array of undetermined length */
} ip_frame_hdr;

/* Macros for accessing an IP datagram.  */
#define IP_VERSION(a)	((a->version_ihl & 0x00F0) >> 4)
#define IP_IHL(a)		((a->version_ihl & 0x000F))
#define IP_DATA(a)		(&((uint8 *)a)[IP_IHL(a) * 4])


void ip_init(void);
void ip_process(void);
void ip_handler(IF_PACKET *pkt);

uint16 ip_chksum(uint16 csum, uint16 *data, int num);
int ip_send(ip_frame_hdr *hdr, IF_BUFFER *buf);

#endif
