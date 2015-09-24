
#include "mcf5282.h"

#include "if.h"
#include "../fec.h"

#include "ip.h"
#include "arp.h"


void if_receive(IF_PACKET *pkt)
{
	switch (pkt->type) {
		case ETH_P_IP:
			ip_handler(pkt);
			break;
		case ETH_P_ARP:
			arp_handler(pkt);
			break;
	}
}

void if_send(IF_PACKET *pkt, IF_BUFFER *buf)
{
	fec_send(pkt, buf);
}
