
#include "nwk.h"


static int iwu_locate_accept_parm(struct nwk_transaction *trans, pp_info_t *pp, unsigned char *data, int len)
{
	unsigned char v[40];

	/* Panasonic sign */
	v[0] = 0xC0;			/* Transmission, Protocol Discriminator = User */
	v[1] = 0x81;			/* PD type = EMC */
	v[2] = 0x05;			/* 2 bytes of EMC */
	v[3] = 0x12;
	/* Phone name */
	v[4] = 0x97;
	v[5] = 0x0B;
	v[6] = 0x00;
	v[7]  = 'I';
	v[8]  = 'T';
	v[9]  = 'C';
	v[10] = 'N';
	v[11] = ' ';
	v[12] = 'D';
	v[13] = 'E';
	v[14] = 'C';
	v[15] = 'T';
	v[16] = ' ';
	/* 95 10 00 14 1F 2E 09 00 FF FF FF 00 27 65 14 00 74 02 */
	v[17] = 0x95;
	v[18] = 0x10;
	v[19] = 0x00;
	v[20] = 0x14;  // 14
	v[21] = 0x1F;  // 1F
	v[22] = 0x2E;  // 2E
	v[23] = 0x09;  // 09
	v[24] = 0x01;  // 00 - b0: AutoAnsweringSystem
	v[25] = 0xFF;  // FF
	v[26] = 0xFF;  // FF
	v[27] = 0xFF;  // FF
	v[28] = 0x00;  // 00
	v[29] = 0x27;  // 27
	v[30] = 0x65;  // 65
	v[31] = 0x14;  // 14
	v[32] = 0x00;  // 00
	v[33] = 0x74;  // 74
	v[34] = 0x02;  // 02
	nwk_reply_parm(trans, P_IWU_TO_IWU, 35, v);
	return 0;
}


int iwu_panasonic(int type, struct nwk_transaction *trans, pp_info_t *pp, unsigned char *data, int len)
{
	switch (type) {
		case IWU_LOCATE_ACCEPT_PARM:
			return iwu_locate_accept_parm(trans, pp, data, len);
	}

	return 0;
}
