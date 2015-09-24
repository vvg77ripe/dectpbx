
#ifndef _G711_H
#define _G711_H


#define alaw_decode(x) table_a2lin[x & 0xFF]
#define alaw_encode(x) table_lin2a[(x >> 3) & 0x1FFF]

extern short table_a2lin[];
extern unsigned char table_lin2a[];


void g711_init();

#endif
