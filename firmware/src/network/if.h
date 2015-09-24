
#ifndef _NETWORK_IF_H
#define _NETWORK_IF_H

#define ETH_P_IP		0x0800
#define ETH_P_ARP		0x0806


typedef struct if_packet {
	unsigned char addr[6];
	uint16 type;
	unsigned int size;
	uint8 *data;
} IF_PACKET;

typedef struct if_buffer {
	uint8 *data;
	uint16 size;
	struct if_buffer *next;
} IF_BUFFER;

void if_receive(IF_PACKET *pkt);
void if_send(IF_PACKET *pkt, IF_BUFFER *buf);

#endif
