
#ifndef _FEC_H
#define _FEC_H

#include "network/if.h"

/* MII register defilions */
#define MII_STATUS2				17

/* Status register 2 bitmap */
#define MII_STATUS2_ERROR		0x0008
#define MII_STATUS2_PAUSE		0x0010
#define MII_STATUS2_POLARITY	0x0020
#define MII_STATUS2_AN_COMPLETE	0x0080
#define MII_STATUS2_AN_ENABLE	0x0100
#define MII_STATUS2_DUPLEX		0x0200
#define MII_STATUS2_LINK		0x0400
#define MII_STATUS2_COLLISION	0x0800
#define MII_STATUS2_RECEIVE		0x1000
#define MII_STATUS2_TRANSMIT	0x2000
#define MII_STATUS2_100MBIT		0x4000

int fec_init(void);

int fec_getMII(int phyNumber, int regNumber);
void fec_setMII(int phyNumber, int regNumber, int value);
void fec_blink(uint8 type);
char *fec_link(void);

void fec_send(IF_PACKET *pkt, IF_BUFFER *buf);

void fec_process(void);

#endif
