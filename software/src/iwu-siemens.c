
#include "nwk.h"


static cmd_test = 0;


static int iwu_locate_accept(struct nwk_transaction *trans, pp_info_t *pp, unsigned char *data, int len)
{
	unsigned char v[40];

	nwk_reply(trans, 0x62);

	/* SIEMENS */
	v[0] = 0x81;			/* PD type = EMC */
	v[1] = 0x00;			/* 2 bytes of EMC */
	v[2] = 0x02;

	/* Date and Time */
	v[3] = 0x3B;
	v[4] = 0x09;
	v[5] = 0x03;			/* ? */
	v[6] = 0x07;			/* D */
	v[7] = 0x02;			/* M */
	v[8] = 0x06;			/* Y */
	v[9] = 0x00;
	v[10] = 0x04;
	v[11] = 0x02;			/* H */
	v[12] = 0x19;			/* M */
	v[13] = 0x01;			/* S */


	v[14] = 0x54;
	v[15] = 0x0A;
	v[16] = 0x01;
	v[17] = 'I';
	v[18] = 'T';
	v[19] = 'C';
	v[20] = 'N';
	v[21] = ' ';
	v[22] = 'D';
	v[23] = 'E';
	v[24] = 'C';
	v[25] = 'T';

	/* Portable name */
	/*
	v[3] = 0x54;
	v[4] = 0x0D;
	v[5]  = 0x01;
	v[6]  = 0x1B;
	v[7]  = 0x2D;
	v[8]  = 0x4C;
	v[9]  = 'I';
	v[10] = 'T';
	v[11] = 'C';
	v[12] = 'N';
	v[13] = ' ';
	v[14] = 'D';
	v[15] = 'E';
	v[16] = 'C';
	v[17] = 'T';
	*/

	/* Text Out */
	/*
	v[3] = 0x58;
	v[4] = 0x1E;
	v[5]  = 0x03;
	v[6]  = 0x1C;
	v[7]  = 0x0C;

	v[8]  = 0x91;
	v[9]  = 0x02;
	v[10] = 0x02;
	v[11] = 0x0B;
	v[12] = 0x1B;
	v[13] = 0x2D;
	v[14] = 0x4C;
	v[15] = 0xBF;
	v[16] = 0xD5;
	v[17] = 0xE0;
	v[18] = 0xD5;
	v[19] = 0xD4;
	v[20] = 0xD0;
	v[21] = 0xE7;
	v[22] = 0xD0;
	v[23] = 0x0A;

	v[24] = 0x91;
	v[25] = 0x02;
	v[26] = 0x02;
	v[27] = 0x07;
	v[28] = 0x1B;
	v[29] = 0x2D;
	v[30] = 0x4C;
	v[31] = 0x31;
	v[32] = 0x32;
	v[33] = 0x33;
	v[34] = 0x34;
	*/

	nwk_reply_parm(trans, P_PROPRIETARY, 26, v);

	nwk_send_command(trans, 0x63);
	usleep(500000);
	return 0;
}

int iwu_siemens(int type, struct nwk_transaction *trans, pp_info_t *pp, unsigned char *data, int len)
{
	switch (type) {
		case IWU_LOCATE_ACCEPT:
			return iwu_locate_accept(trans, pp, data, len);
	}

	return 0;
}
