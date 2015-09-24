/*
 * ETSI EN 300 175-3
 * Digital Enhanced Cordless Telecommunications (DECT)
 * Meduim Access Control (MAC) layer
 * implementation for MCF5282
 *
 */

#include <mcf5282.h>
#include "config.h"

#include "term/terminal.h"

#include "dect.h"
#include "dect-mac.h"
#include "dect-server.h"


static uint16 rcrc_table[256] = {
	0x0000, 0x0589, 0x0B12, 0x0E9B, 0x1624, 0x13AD, 0x1D36, 0x18BF,
	0x2C48, 0x29C1, 0x275A, 0x22D3, 0x3A6C, 0x3FE5, 0x317E, 0x34F7,
	0x5890, 0x5D19, 0x5382, 0x560B, 0x4EB4, 0x4B3D, 0x45A6, 0x402F,
	0x74D8, 0x7151, 0x7FCA, 0x7A43, 0x62FC, 0x6775, 0x69EE, 0x6C67,
	0xB120, 0xB4A9, 0xBA32, 0xBFBB, 0xA704, 0xA28D, 0xAC16, 0xA99F,
	0x9D68, 0x98E1, 0x967A, 0x93F3, 0x8B4C, 0x8EC5, 0x805E, 0x85D7,
	0xE9B0, 0xEC39, 0xE2A2, 0xE72B, 0xFF94, 0xFA1D, 0xF486, 0xF10F,
	0xC5F8, 0xC071, 0xCEEA, 0xCB63, 0xD3DC, 0xD655, 0xD8CE, 0xDD47,
	0x67C9, 0x6240, 0x6CDB, 0x6952, 0x71ED, 0x7464, 0x7AFF, 0x7F76,
	0x4B81, 0x4E08, 0x4093, 0x451A, 0x5DA5, 0x582C, 0x56B7, 0x533E,
	0x3F59, 0x3AD0, 0x344B, 0x31C2, 0x297D, 0x2CF4, 0x226F, 0x27E6,
	0x1311, 0x1698, 0x1803, 0x1D8A, 0x0535, 0x00BC, 0x0E27, 0x0BAE,
	0xD6E9, 0xD360, 0xDDFB, 0xD872, 0xC0CD, 0xC544, 0xCBDF, 0xCE56,
	0xFAA1, 0xFF28, 0xF1B3, 0xF43A, 0xEC85, 0xE90C, 0xE797, 0xE21E,
	0x8E79, 0x8BF0, 0x856B, 0x80E2, 0x985D, 0x9DD4, 0x934F, 0x96C6,
	0xA231, 0xA7B8, 0xA923, 0xACAA, 0xB415, 0xB19C, 0xBF07, 0xBA8E,
	0xCF92, 0xCA1B, 0xC480, 0xC109, 0xD9B6, 0xDC3F, 0xD2A4, 0xD72D,
	0xE3DA, 0xE653, 0xE8C8, 0xED41, 0xF5FE, 0xF077, 0xFEEC, 0xFB65,
	0x9702, 0x928B, 0x9C10, 0x9999, 0x8126, 0x84AF, 0x8A34, 0x8FBD,
	0xBB4A, 0xBEC3, 0xB058, 0xB5D1, 0xAD6E, 0xA8E7, 0xA67C, 0xA3F5,
	0x7EB2, 0x7B3B, 0x75A0, 0x7029, 0x6896, 0x6D1F, 0x6384, 0x660D,
	0x52FA, 0x5773, 0x59E8, 0x5C61, 0x44DE, 0x4157, 0x4FCC, 0x4A45,
	0x2622, 0x23AB, 0x2D30, 0x28B9, 0x3006, 0x358F, 0x3B14, 0x3E9D,
	0x0A6A, 0x0FE3, 0x0178, 0x04F1, 0x1C4E, 0x19C7, 0x175C, 0x12D5,
	0xA85B, 0xADD2, 0xA349, 0xA6C0, 0xBE7F, 0xBBF6, 0xB56D, 0xB0E4,
	0x8413, 0x819A, 0x8F01, 0x8A88, 0x9237, 0x97BE, 0x9925, 0x9CAC,
	0xF0CB, 0xF542, 0xFBD9, 0xFE50, 0xE6EF, 0xE366, 0xEDFD, 0xE874,
	0xDC83, 0xD90A, 0xD791, 0xD218, 0xCAA7, 0xCF2E, 0xC1B5, 0xC43C,
	0x197B, 0x1CF2, 0x1269, 0x17E0, 0x0F5F, 0x0AD6, 0x044D, 0x01C4,
	0x3533, 0x30BA, 0x3E21, 0x3BA8, 0x2317, 0x269E, 0x2805, 0x2D8C,
	0x41EB, 0x4462, 0x4AF9, 0x4F70, 0x57CF, 0x5246, 0x5CDD, 0x5954,
	0x6DA3, 0x682A, 0x66B1, 0x6338, 0x7B87, 0x7E0E, 0x7095, 0x751C};

/* B-field scrambling patterns */
static uint8 scr_table[8][40] = {
	{0x3B, 0xCD, 0x21, 0x5D, 0x88, 0x65, 0xBD, 0x44, 0xEF, 0x34,
	 0x85, 0x76, 0x21, 0x96, 0xF5, 0x13, 0xBC, 0xD2, 0x15, 0xD8,
	 0x86, 0x5B, 0xD4, 0x4E, 0xF3, 0x48, 0x57, 0x62, 0x19, 0x6F,
	 0x51, 0x3B, 0xCD, 0x21, 0x5D, 0x88, 0x65, 0xBD, 0x44, 0xEF},
	{0x32, 0xDE, 0xA2, 0x77, 0x9A, 0x42, 0xBB, 0x10, 0xCB, 0x7A,
	 0x89, 0xDE, 0x69, 0x0A, 0xEC, 0x43, 0x2D, 0xEA, 0x27, 0x79,
	 0xA4, 0x2B, 0xB1, 0x0C, 0xB7, 0xA8, 0x9D, 0xE6, 0x90, 0xAE,
	 0xC4, 0x32, 0xDE, 0xA2, 0x77, 0x9A, 0x42, 0xBB, 0x10, 0xCB},
	{0x2D, 0xEA, 0x27, 0x79, 0xA4, 0x2B, 0xB1, 0x0C, 0xB7, 0xA8,
	 0x9D, 0xE6, 0x90, 0xAE, 0xC4, 0x32, 0xDE, 0xA2, 0x77, 0x9A,
	 0x42, 0xBB, 0x10, 0xCB, 0x7A, 0x89, 0xDE, 0x69, 0x0A, 0xEC,
	 0x43, 0x2D, 0xEA, 0x27, 0x79, 0xA4, 0x2B, 0xB1, 0x0C, 0xB7},
	{0x27, 0x79, 0xA4, 0x2B, 0xB1, 0x0C, 0xB7, 0xA8, 0x9D, 0xE6,
	 0x90, 0xAE, 0xC4, 0x32, 0xDE, 0xA2, 0x77, 0x9A, 0x42, 0xBB,
	 0x10, 0xCB, 0x7A, 0x89, 0xDE, 0x69, 0x0A, 0xEC, 0x43, 0x2D,
	 0xEA, 0x27, 0x79, 0xA4, 0x2B, 0xB1, 0x0C, 0xB7, 0xA8, 0x9D},
	{0x19, 0x6F, 0x51, 0x3B, 0xCD, 0x21, 0x5D, 0x88, 0x65, 0xBD,
	 0x44, 0xEF, 0x34, 0x85, 0x76, 0x21, 0x96, 0xF5, 0x13, 0xBC,
	 0xD2, 0x15, 0xD8, 0x86, 0x5B, 0xD4, 0x4E, 0xF3, 0x48, 0x57,
	 0x62, 0x19, 0x6F, 0x51, 0x3B, 0xCD, 0x21, 0x5D, 0x88, 0x65},
	{0x13, 0xBC, 0xD2, 0x15, 0xD8, 0x86, 0x5B, 0xD4, 0x4E, 0xF3,
	 0x48, 0x57, 0x62, 0x19, 0x6F, 0x51, 0x3B, 0xCD, 0x21, 0x5D,
	 0x88, 0x65, 0xBD, 0x44, 0xEF, 0x34, 0x85, 0x76, 0x21, 0x96,
	 0xF5, 0x13, 0xBC, 0xD2, 0x15, 0xD8, 0x86, 0x5B, 0xD4, 0x4E},
	{0x0C, 0xB7, 0xA8, 0x9D, 0xE6, 0x90, 0xAE, 0xC4, 0x32, 0xDE,
	 0xA2, 0x77, 0x9A, 0x42, 0xBB, 0x10, 0xCB, 0x7A, 0x89, 0xDE,
	 0x69, 0x0A, 0xEC, 0x43, 0x2D, 0xEA, 0x27, 0x79, 0xA4, 0x2B,
	 0xB1, 0x0C, 0xB7, 0xA8, 0x9D, 0xE6, 0x90, 0xAE, 0xC4, 0x32},
	{0x79, 0xA4, 0x2B, 0xB1, 0x0C, 0xB7, 0xA8, 0x9D, 0xE6, 0x90,
	 0xAE, 0xC4, 0x32, 0xDE, 0xA2, 0x77, 0x9A, 0x42, 0xBB, 0x10,
	 0xCB, 0x7A, 0x89, 0xDE, 0x69, 0x0A, 0xEC, 0x43, 0x2D, 0xEA,
	 0x27, 0x79, 0xA4, 0x2B, 0xB1, 0x0C, 0xB7, 0xA8, 0x9D, 0xE6}};



/*
 * Setup PMB6610 slot for TX operation.
 * This also setup a blind slot.
 */
static void dect_setup_tx(uint8 sn, uint8 cn, uint8 type)
{
	uint8 psn;

	psn = sn - 1;
	if (psn > 11) psn = 11;

	dect->slots[psn].type = DECT_STYPE_BLIND;

	switch (type) {
		case DECT_TX_IDLE:
			DECT_REG_ADDR = psn;
			DECT_REG_TXD = 0;
			DECT_REG_ADDR = sn;
			DECT_REG_TXD = 0;
			break;

		case DECT_TX_P00:
			DECT_REG_ADDR = psn;
			DECT_REG_TXD = DECT_SLOT_BLIND + 12;
			DECT_REG_TXD = 0x0D;
			DECT_REG_TXD = 0xC0 | (((cn + 5) & 0x0F) << 2);
			DECT_REG_TXD = 0x00;
			DECT_REG_ADDR = sn;
			DECT_REG_TXD = DECT_SLOT_TX_P00 + 3;
			DECT_REG_TXD = 0x00;
			DECT_REG_TXD = 0x07;
			DECT_REG_TXD = 0x00;
			break;

		case DECT_TX_P32:
			DECT_REG_ADDR = psn;
			DECT_REG_TXD = DECT_SLOT_BLIND + 12;
			DECT_REG_TXD = 0x0D;
			DECT_REG_TXD = 0xC0 | (((cn + 5) & 0x0F) << 2);
			DECT_REG_TXD = 0x00;
			DECT_REG_ADDR = sn;
			DECT_REG_TXD = DECT_SLOT_TX_P32 + 3;
			DECT_REG_TXD = 0x00;
			DECT_REG_TXD = 0x07;
			DECT_REG_TXD = 0x00;
			break;
	}
}

/*
 * Setup PMB6610 slot for RX operation.
 * This also setup a blind slot.
 */
static void dect_setup_rx(uint8 sn, uint8 cn, uint8 type)
{
	uint8 psn;

	psn = sn - 1;
	if (psn > 11) psn = 11;

	dect->slots[psn].type = DECT_STYPE_BLIND;

	switch (type) {
		case DECT_RX_IDLE:
			DECT_REG_ADDR = psn + 12;
			DECT_REG_TXD = 0;
			DECT_REG_ADDR = sn + 12;
			DECT_REG_TXD = 0;
			break;

		case DECT_RX_P32:
			DECT_REG_ADDR = psn + 12;
			DECT_REG_TXD = DECT_SLOT_BLIND + 12;
			DECT_REG_TXD = 0x0D;
			DECT_REG_TXD = 0xC0 | (((cn + 5) & 0x0F) << 2) | 2;
			DECT_REG_TXD = 0x00;
			DECT_REG_ADDR = sn + 12;
			DECT_REG_TXD = DECT_SLOT_RX + 3;
			DECT_REG_TXD = 0x00;
			DECT_REG_TXD = 0x01;
			DECT_REG_TXD = 0x00;
			break;
	}
}

static uint8 dect_pscan_next(uint8 cn)
{
	uint8 next_cn;

	next_cn = cn + 1;
	if (next_cn >= 10) next_cn = 0;
	return next_cn;
}

static void dect_qtail(uint8 sn, uint8 *buf)
{
	switch (dect->mframe & 7) {
		case 0:
		case 4:
			/* Static system information */
			buf[1] = sn & 0x0F;
			buf[2] = 0x03;
			buf[3] = 0xFF;	/* 10 rf carriers available */
			buf[4] = dect->slots[sn].cn & 0x3F;
			buf[5] = dect_pscan_next(dect->pscan_cn) & 0x3F;
			break;

		case 1:
		case 5:
			/* Fixed part capabilities */
			buf[1] = 0x38;	/* 08: Extended info present */
			buf[2] = 0x51;	/* 40: Full slot, 10: Page repetition, 01: Basic setup */
			buf[3] = 0x18;	/* 01: In-min-delay, 08: In-normal-delay */
			buf[4] = 0xCF;	/* 80: G.726, 40: GAP speech, 08: StdAuth, 04: StdCip, 02: LogReg, 01: SIM */
			buf[5] = 0x7E;	/* 40: CISS, 20: CLMS, 10: COMS, 08: AccReq, 04: ExtHandover, 02: ConnHandover */
			break;

		case 2:
		case 6:
			/* Extended Fixed part capabilities */
			buf[1] = 0x40;
			buf[2] = 0x10;		/* Prolonged preamble */
			buf[3] = 0x00;
			buf[4] = 0x00;
			buf[5] = 0x10;		/* LRMS */
			break;

		case 3:
		case 7:
			/* Multiframe number */
			buf[1] = 0x6F;
			buf[2] = 0x0F;
			buf[3] = (dect->mframe >> 16) & 0xFF;
			buf[4] = (dect->mframe >> 8) & 0xFF;
			buf[5] = dect->mframe & 0xFF;
			break;
	}
}

static void dect_ptail(uint8 sn, uint8 *buf)
{
	uint8 i;
	uint16 bs;

	buf[1] = dect->rfpi[3] & 0x0F;
	buf[2] = dect->rfpi[4];
	buf[3] = dect->rfpi[5];

	/* Short page message */
	if ((dect->ptail[0] & 0xF0) == 0x10) {
		buf[1] = dect->ptail[0];
		buf[2] = dect->ptail[1];
		buf[3] = dect->ptail[2];
		/* Page repetition */
		dect->ptail[4]--;
		if (dect->ptail[4] == 0) dect->ptail[0] = 0;
	}

	/* Blind slot info */
	bs = 0x1000;
	for (i = 0; i < 12; i++)
		if (dect->slots[i].type == DECT_STYPE_PSCAN)
			bs |= (0x800 >> i);
	buf[4] = bs >> 8;
	buf[5] = bs & 0xFF;
}

/*
 * A-MAP and T-MUX multiplex
 */
static void dect_amap(uint8 sn, uint8 *buf)
{
	dect_slot_t *slot;
	mbc_inst_t *mbc;
	uint8 tmux, bmux;
	uint16 rcrc;

	slot = &dect->slots[sn];
	tmux = DECT_TMUX_NT;

	if ( (dect->frame & 1) || (dect->slots[sn].mtail[0] == 2) ) {
		/* Odd frames: Mt, Ct, Nt priority */
		if (dect->slots[sn].mtail[0]) {
			tmux = DECT_TMUX_MT;
			buf[1] = dect->slots[sn].mtail[1];
			buf[2] = dect->slots[sn].mtail[2];
			buf[3] = dect->slots[sn].mtail[3];
			buf[4] = dect->slots[sn].mtail[4];
			buf[5] = dect->slots[sn].mtail[5];
			dect->slots[sn].mtail[0] = 0;
		}
		if ( (tmux == DECT_TMUX_NT) && (slot->mbc) ) {
			mbc = &dect->mbc[slot->mbc-1];
			if (mbc->cs_send_len) {
				tmux = DECT_TMUX_CT + mbc->cs_send_seq;
				buf[1] = mbc->cs_send[mbc->cs_send_pos+0];
				buf[2] = mbc->cs_send[mbc->cs_send_pos+1];
				buf[3] = mbc->cs_send[mbc->cs_send_pos+2];
				buf[4] = mbc->cs_send[mbc->cs_send_pos+3];
				buf[5] = mbc->cs_send[mbc->cs_send_pos+4];
				mbc->cs_send_pos += 5;
				mbc->cs_send_seq = 1 - mbc->cs_send_seq;
				if (mbc->cs_send_pos >= mbc->cs_send_len) {
					mbc->cs_send_len = 0;
					mbc->cs_send_pos = 0;
				}
			}
		}
	} else {
		/* Pt, Nt priority, except for 8 (Qt) and 14 (Nt) */
		if (dect->frame == 8) {
			tmux = DECT_TMUX_QT;
			dect_qtail(sn, buf);
		}
		if ( (dect->frame == 0) && ((dect->mframe % 5) != 0) ) {
			tmux = DECT_TMUX_PT;
			dect_ptail(sn, buf);
		}
	}

	if (tmux == DECT_TMUX_NT) {
		buf[1] = dect->rfpi[0];
		buf[2] = dect->rfpi[1];
		buf[3] = dect->rfpi[2];
		buf[4] = dect->rfpi[3];
		buf[5] = dect->rfpi[4];
	}

	/* Header field */
	bmux = DECT_BMUX_NONE;
	if (slot->type == DECT_STYPE_TRAFFIC) {
		bmux = 0;
	}
	buf[0] = (tmux << 5) | (bmux << 1);
	if ( (slot->type == DECT_STYPE_TRAFFIC) && (slot->bt == DECT_BEARER_DUPLEX) ) {
		/* Q2 */
		buf[0] |= 1;
	}

	/* R-CRC */
	rcrc = 0;
	rcrc = rcrc_table[rcrc >> 8] ^ (rcrc << 8 | buf[0]);
	rcrc = rcrc_table[rcrc >> 8] ^ (rcrc << 8 | buf[1]);
	rcrc = rcrc_table[rcrc >> 8] ^ (rcrc << 8 | buf[2]);
	rcrc = rcrc_table[rcrc >> 8] ^ (rcrc << 8 | buf[3]);
	rcrc = rcrc_table[rcrc >> 8] ^ (rcrc << 8 | buf[4]);
	rcrc = rcrc_table[rcrc >> 8] ^ (rcrc << 8 | buf[5]);
	rcrc = rcrc_table[rcrc >> 8] ^ (rcrc << 8);
	rcrc = rcrc_table[rcrc >> 8] ^ (rcrc << 8);
	rcrc ^= 1;
	buf[6] = rcrc >> 8;
	buf[7] = rcrc & 0xFF;

	if ( (tmux == DECT_TMUX_MT) || (tmux == DECT_TMUX_CT) || (tmux == (DECT_TMUX_CT+1)) ) {
		term_log_all("DECT TX%X: %X %X %X %X %X %X %X %X\r\n", sn,
			buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7]);
	}

}

/*
 * Setup TX/RX slot pair
 */
static void dect_setup_slot(uint8 sn)
{
	uint8 afield[8];
	uint8 *scr, *data;
	mbc_inst_t *mbc;
	int i;

	mbc = NULL;
	if (dect->slots[sn].mbc) mbc = &dect->mbc[dect->slots[sn].mbc-1];

	switch (dect->slots[sn].type) {
		case DECT_STYPE_IDLE:
			dect_setup_tx(sn, 0, DECT_TX_IDLE);
			dect_setup_rx(sn, 0, DECT_RX_IDLE);
			break;

		case DECT_STYPE_DUMMY:
			dect_amap(sn, afield);
			dect_setup_tx(sn, dect->slots[sn].cn, DECT_TX_P00);
			DECT_REG_TXD = 0xAA;
			DECT_REG_TXD = 0xAA;
			DECT_REG_TXD = 0xE9;
			DECT_REG_TXD = 0x8A;
			for (i = 0; i < 8; i++)
				DECT_REG_TXD = afield[i];
			DECT_REG_TXD = 0;
			dect_setup_rx(sn, 0, DECT_RX_IDLE);
			break;

		case DECT_STYPE_TRAFFIC:
			dect_amap(sn, afield);
			dect_setup_tx(sn, dect->slots[sn].cn, DECT_TX_P32);
			DECT_REG_TXD = 0xAA;
			DECT_REG_TXD = 0xAA;
			DECT_REG_TXD = 0xE9;
			DECT_REG_TXD = 0x8A;
			/* A-field */
			for (i = 0; i < 8; i++)
				DECT_REG_TXD = afield[i];
			/* B-field */
			if (mbc) {
				scr = &scr_table[dect->frame & 7][0];
				data = &mbc->voice_tx[40 - (dect->frame & 1) * 40];
				for (i = 0; i < 40; i++) {
					DECT_REG_TXD = *scr++ ^ *data++;
				}
			}
			DECT_REG_TXD = 0;
			dect_setup_rx(sn, dect->slots[sn].cn, DECT_RX_P32);
			break;

		case DECT_STYPE_PSCAN:
			dect_setup_tx(sn, 0, DECT_TX_IDLE);
			dect_setup_rx(sn, dect->slots[sn].cn, DECT_RX_P32);
			break;
	}
}


/********************************************************************
 * Multi-Bearer Control
 ********************************************************************/

void dect_mbc_init()
{
	int i, sl;
	uint8 vs;

	for (i = 0; i < DECT_MBC_MAX; i++) {
		dect->mbc[i].pmid = 0;
	}

}

static int dect_mbc_assign(uint32 pmid, uint8 ecn, uint8 type)
{
	int i, mbc_id;
	mbc_inst_t *mbc;

	/* Find existing MBC */
	mbc = NULL;
	for (i = 0; i < DECT_MBC_MAX; i++) {
		if ( (dect->mbc[i].pmid == pmid) && (dect->mbc[i].ecn == ecn) ) {
			mbc = &dect->mbc[i];
			mbc_id = i;
			break;
		}
	}

	/* Create new MBC */
	if (!mbc) {
		for (i = 0; i < DECT_MBC_MAX; i++) {
			if (dect->mbc[i].pmid == 0) {
				mbc = &dect->mbc[i];
				mbc_id = i;

				mbc->pmid = pmid;
				mbc->ecn = ecn;
				mbc->uplane = 0;
				mbc->cs_recv_seq = 1;
				mbc->cs_send_seq = 1;
				mbc->cs_recv_len = 0;
				mbc->cs_send_len = 0;
				mbc->cs_send_pos = 0;

				term_log_all("DECT: New MBC ID %X created.\r\n", mbc_id+1);
				break;
			}
		}
	}

	if (!mbc) return -1;

	return mbc_id + 1;
}

static void dect_mbc_release(uint8 mbc_id)
{
	int i, c;

	if ( (mbc_id > DECT_MBC_MAX) || (mbc_id == 0) ) return;
	if (dect->mbc[mbc_id-1].pmid == 0) return;

	c = 0;
	for (i = 0; i < 12; i++)
		if ( (dect->slots[i].type == DECT_STYPE_TRAFFIC) && (dect->slots[i].mbc == mbc_id) )
			c++;

	if (c < 2) {
		dect->mbc[mbc_id-1].pmid = 0;
		term_log_all("DECT: MBC ID %X released.\r\n", mbc_id);
	}
}

static void dect_mbc_cs_recv(uint8 mbc_id, uint8 seq, uint8 *data)
{
	mbc_inst_t *mbc;
	uint16 flen;

	if ( (mbc_id > DECT_MBC_MAX) || (mbc_id == 0) ) return;
	if (dect->mbc[mbc_id-1].pmid == 0) return;
	mbc = &dect->mbc[mbc_id-1];

	/* sequence check */
	if (mbc->cs_recv_seq != seq) return;
	mbc->cs_recv_seq = 1 - mbc->cs_recv_seq;

	if (mbc->cs_recv_len == 0) {
		/* First packet in frame */
		if (data[2] & 1) {
			flen = (data[2] >> 2) + 5;
		} else {
			if (!(data[3] & 1)) return;
			flen = (data[2] >> 2) | ((data[3] >> 2) << 6) + 6;
		}
		if (flen > DECT_CS_MAX_FLEN) return;

		mbc->cs_recv_len = flen;
		mbc->cs_recv_pos = 0;
	}

	/* buffer overflow check */
	if (mbc->cs_recv_pos > (DECT_CS_MAX_FLEN - 5)) {
		mbc->cs_recv_len = 0;
		mbc->cs_recv_pos = 0;
		return;
	}

	mbc->cs_recv[mbc->cs_recv_pos+0] = data[0];
	mbc->cs_recv[mbc->cs_recv_pos+1] = data[1];
	mbc->cs_recv[mbc->cs_recv_pos+2] = data[2];
	mbc->cs_recv[mbc->cs_recv_pos+3] = data[3];
	mbc->cs_recv[mbc->cs_recv_pos+4] = data[4];
	mbc->cs_recv_pos += 5;

	if (mbc->cs_recv_pos >= mbc->cs_recv_len) {
		/* Send complete packet to dect server */
		dect_serv_send_lapc(mbc->pmid, mbc->ecn, mbc->cs_recv, mbc->cs_recv_pos);
		mbc->cs_recv_len = 0;
		mbc->cs_recv_pos = 0;
	}
}

static void dect_mbc_bfield_recv(uint8 mbc_id, uint8 *data, uint16 len)
{
	mbc_inst_t *mbc;

	if ( (mbc_id > DECT_MBC_MAX) || (mbc_id == 0) ) return;
	if (dect->mbc[mbc_id-1].pmid == 0) return;
	mbc = &dect->mbc[mbc_id-1];

	if (mbc->uplane == 1) {
		dect_serv_send_voice(mbc->pmid, mbc->ecn, data, len);
	}
}

void dect_mbc_voice_recv(uint32 pmid, uint8 ecn, uint8 *data, uint16 len)
{
	int i;
	mbc_inst_t *mbc;

	mbc = NULL;
	for (i = 0; i < DECT_MBC_MAX; i++) {
		if ((dect->mbc[i].pmid == pmid) && (dect->mbc[i].ecn == ecn)) {
			mbc = &dect->mbc[i];
			break;
		}
	}

	if (!mbc) return;
	if (len > 160) return;

	for (i = 0; i < len; i++) {
		mbc->voice_tx[i] = data[i];
	}
}

/********************************************************************
 * D-SAP
 ********************************************************************/

void dect_init_slots()
{
	int i, j;

	/* All slots are IDLE by default */
	for (i = 0; i < 12; i++) {
		dect->slots[i].type = DECT_STYPE_IDLE;
		dect->slots[i].sn = i;
	}

	/* Preamble bits */
	for (i = 0; i < 12; i++) {
		DECT_REG_ADDR = i;
		DECT_REG_TXD = 0;
		DECT_REG_TXD = 0;
		DECT_REG_TXD = 0;
		DECT_REG_TXD = 0;
		for (j = 0; j < 60; j++)
			DECT_REG_TXD = 0xAA;
	}

	dect->frame = 0;
	dect->mframe = 0;
	dect->pscan_cn = 0;

	/* Enable dummy bearer */
	dect->slots[11].type = DECT_STYPE_DUMMY;
	dect->slots[11].cn = 5;
	dect->dummypos = 11;

	/* Enable primary scan slots */
	dect->slots[1].type = DECT_STYPE_PSCAN;
	dect->slots[1].cn = dect->pscan_cn;
	dect->slots[3].type = DECT_STYPE_PSCAN;
	dect->slots[3].cn = dect->pscan_cn;
	dect->slots[5].type = DECT_STYPE_PSCAN;
	dect->slots[5].cn = dect->pscan_cn;
	dect->slots[7].type = DECT_STYPE_PSCAN;
	dect->slots[7].cn = dect->pscan_cn;
	dect->slots[9].type = DECT_STYPE_PSCAN;
	dect->slots[9].cn = dect->pscan_cn;

	dect->tmr_ping = 0;
}

void dect_next_frame()
{
	int i;
	dect_slot_t *slot;

	for (i = 0; i < 12; i++) {
		slot = &dect->slots[i];

		/* Check timeout for traffic bearers */
		if (slot->type == DECT_STYPE_TRAFFIC) {
			slot->tmr_timeout++;
			if (slot->tmr_timeout >= DECT_TMR_TIMEOUT) {
				term_log_all("DECT: Traffic bearer in slot %i timed out.\r\n", i);
				dect_mbc_release(slot->mbc);
				slot->mbc = 0;
				slot->type = DECT_STYPE_PSCAN;
			}
		}
		/* Primary scan */
		if (slot->type == DECT_STYPE_PSCAN) {
			slot->cn = dect->pscan_cn;
			dect_setup_slot(i);
		}
	}

	dect->pscan_cn = dect_pscan_next(dect->pscan_cn);

	dect->frame++;
	if (dect->frame >= 16) {
		dect->frame = 0;
		dect->mframe++;
	}

	dect_setup_slot(dect->dummypos);

	dect->tmr_ping++;
	if (dect->tmr_ping >= DECT_TMR_PING) {
		dect->tmr_ping = 0;
		dect_serv_send_ping();
	}
}

void dect_recv(uint8 sn, uint8 *buf)
{
	int mbc_id, i;
	dect_slot_t *slot;
	mbc_inst_t *mbc;
	uint8 *data;
	uint8 ta, ba, rcrc_ok, rx_frame;
	uint16 rcrc, rxd;
	uint16 fmid, my_fmid;
	uint32 pmid;

	slot = &dect->slots[sn];
	ta = (buf[0] >> 5) & 7;
	ba = (buf[0] >> 1) & 7;
	my_fmid = ((dect->rfpi[3] & 0x0F) << 8) | dect->rfpi[4];

	/*
	term_log_all("DECT RX%X: %X %X %X %X %X %X %X %X\r\n", sn,
		buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7]);
	*/

	/* R-CRC */
	rcrc = 0;
	rcrc = rcrc_table[rcrc >> 8] ^ (rcrc << 8 | buf[0]);
	rcrc = rcrc_table[rcrc >> 8] ^ (rcrc << 8 | buf[1]);
	rcrc = rcrc_table[rcrc >> 8] ^ (rcrc << 8 | buf[2]);
	rcrc = rcrc_table[rcrc >> 8] ^ (rcrc << 8 | buf[3]);
	rcrc = rcrc_table[rcrc >> 8] ^ (rcrc << 8 | buf[4]);
	rcrc = rcrc_table[rcrc >> 8] ^ (rcrc << 8 | buf[5]);
	rcrc = rcrc_table[rcrc >> 8] ^ (rcrc << 8);
	rcrc = rcrc_table[rcrc >> 8] ^ (rcrc << 8);
	rcrc ^= 1;
	rcrc_ok = ((rcrc >> 8) == buf[6]) && ((rcrc & 0xFF) == buf[7]);

	if ((ta == DECT_TMUX_FIRST_MT) && (dect->slots[sn].type == DECT_STYPE_PSCAN)) {
		/* First PT transmission received on primary scan */
		if (!rcrc_ok) return;

		if (buf[1] == DECT_MT_BASIC_ACCESS_REQUEST) {
			fmid = (buf[2] << 4) | (buf[3] >> 4);
			if (fmid != my_fmid) return;
			pmid = ((buf[3] & 0x0F) << 16) | (buf[4] << 8) | buf[5];

			term_log_all("DECT RX%X: Access Request from %X:%X:%X\r\n",
				sn, buf[3] & 0x0F, buf[4], buf[5]);

			mbc_id = dect_mbc_assign(pmid, 0xFF, DECT_MBC_ACCESS_REQUEST);
			if (mbc_id > 0) {
				dect->slots[sn].mbc = mbc_id;

				/* Allocate duplex traffic bearer */
				slot->type = DECT_STYPE_TRAFFIC;
				slot->bt = DECT_BEARER_DUPLEX;
				slot->tmr_timeout = 0;

				/* Send BEARER_CONFIRM */
				dect->slots[sn].mtail[0] = 2;
				dect->slots[sn].mtail[1] = DECT_MT_BASIC_BEARER_CONFIRM;
				dect->slots[sn].mtail[2] = buf[2];
				dect->slots[sn].mtail[3] = buf[3];
				dect->slots[sn].mtail[4] = buf[4];
				dect->slots[sn].mtail[5] = buf[5];
			}

		}

		return;
	}

	/* Others PP transmissions are accepted only on traffic bearers */
	if (dect->slots[sn].type != DECT_STYPE_TRAFFIC) return;
	if (dect->slots[sn].mbc == 0) return;
	mbc = &dect->mbc[dect->slots[sn].mbc-1];

	if (!rcrc_ok) {
		/* TODO: Set Q2 bit */
		return;
	}

	/* I channel data */
	if (ba == 0) {
		rx_frame = (dect->frame - 1) & 7;
		data = &mbc->voice_rx[(rx_frame & 1) * 40];
		for (i = 0; i < 40; i++) {
			rxd = DECT_REG_RXD & 0xFF;
			*data++ = rxd ^ scr_table[rx_frame][i];
		}
		if (rx_frame & 1) {
			dect_mbc_bfield_recv(slot->mbc, mbc->voice_rx, 80);
		}
	}

	/* MAC type tail */
	if (ta == DECT_TMUX_MT) {
		switch (buf[1]) {
			case DECT_MT_BASIC_RELEASE:
				fmid = (buf[2] << 4) | (buf[3] >> 4);
				if (fmid != my_fmid) return;

				term_log_all("DECT RX%X: Bearer release from %X:%X:%X\r\n",
					sn, buf[3] & 0x0F, buf[4], buf[5]);

				dect_mbc_release(slot->mbc);
				slot->mbc = 0;

				slot->type = DECT_STYPE_PSCAN;
				slot->cn = dect->pscan_cn;
				break;
		}
	}

	/* CT type tail */
	if ((ta & 0x6) == DECT_TMUX_CT) {
		dect_mbc_cs_recv(slot->mbc, ta & 1, &buf[1]);
	}

	/* NT type tail */
	if (ta == DECT_TMUX_NT) {
		slot->tmr_timeout = 0;
	}
}

void dect_recv_sync(uint8 sn, uint8 *buf)
{
	dect_recv(sn, buf);
	dect_setup_slot(sn);
}

void dect_recv_nosync(uint8 sn)
{
	dect_setup_slot(sn);
}
