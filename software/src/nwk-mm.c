
#include <stdlib.h>
#include <string.h>

#include "nwk.h"
#include "nwk-mm.h"
#include "sql.h"

#include "iwu-panasonic.h"
#include "iwu-siemens.h"

static void mm_locate_request(struct nwk_transaction *trans, unsigned char *data, int len)
{
	unsigned char v[40];
	unsigned char *val;
	int vlen, i;
	pp_info_t *pp;
	char q[100];

	log_print(0, "MM Start:\n");

	/* SQL needed */
	if (!trans->sql) trans->sql = sql_create();
	if (!trans->sql) {
		nwk_reply(trans, DECT_MM_LOCATE_REJECT);
		v[0] = REJECT_NO_RESOURCES;
		nwk_reply_parm(trans, P_REJECT_REASON, 1, v);
		nwk_send_reply(trans);
		return;
	}

	/* Check portable identity */
	val = nwk_find_parm(P_PORTABLE_IDENTITY, &vlen, data, len);
	if (!val) {
		nwk_reply(trans, DECT_MM_LOCATE_REJECT);
		v[0] = REJECT_INFORMATION_ELEMENT;
		nwk_reply_parm(trans, P_REJECT_REASON, 1, v);
		nwk_send_reply(trans);
		return;
	}
	if ( (vlen < 3) || (val[0] != 0x80) ) {
		nwk_reply(trans, DECT_MM_LOCATE_REJECT);
		v[0] = REJECT_INFORMATION_ELEMENT;
		nwk_reply_parm(trans, P_REJECT_REASON, 1, v);
		nwk_send_reply(trans);
		return;
	}

	/* Check subsciption */
	pp = pp_find(trans, val, vlen);
	if (!pp) {
		nwk_reply(trans, DECT_MM_LOCATE_REJECT);
		v[0] = REJECT_IPUI_NOT_ACCEPTED;
		nwk_reply_parm(trans, P_REJECT_REASON, 1, v);
		nwk_send_reply(trans);
		return;
	}

	/* Update location information */
	sprintf(q, "UPDATE hdb SET last_seen=UNIX_TIMESTAMP() WHERE tpui = '%i'", pp->tpui);
	sql_query(trans->sql, q, NULL);

	pp_iwu(IWU_LOCATE_ACCEPT, trans, pp, data, len);

	/* Locate Accept */
	nwk_reply(trans, DECT_MM_LOCATE_ACCEPT);
	nwk_reply_parm(trans, P_PORTABLE_IDENTITY, 0, NULL);
	v[0] = 0x64;
	nwk_reply_parm(trans, P_LOCATION_AREA, 1, v);
	pp_iwu(IWU_LOCATE_ACCEPT_PARM, trans, pp, data, len);
	nwk_send_reply(trans);

	pp_free(pp);
}

static void mm_access_rights_request(struct nwk_transaction *trans, unsigned char *data, int len)
{
	unsigned char v[40];
	char ipui_str[50];
	unsigned char *val;
	void *sql_res;
	char **row;
	char q[200];
	int vlen, i;

	/* Portable Identity */
	val = nwk_find_parm(P_PORTABLE_IDENTITY, &vlen, data, len);
	if (!val) {
		nwk_reply(trans, DECT_MM_ACCESS_RIGHTS_REJECT);
		v[0] = REJECT_INFORMATION_ELEMENT;
		nwk_reply_parm(trans, P_REJECT_REASON, 1, v);
		nwk_send_reply(trans);
		return;
	}
	sprintf(ipui_str, "%02i:", val[1] & 0x7F);
	for (i = 2; i < vlen; i++) {
		sprintf(&ipui_str[i*2 - 1], "%02X", val[i]);
	}

	/* SQL needed */
	if (!trans->sql) trans->sql = sql_create();
	if (!trans->sql) {
		nwk_reply(trans, DECT_MM_ACCESS_RIGHTS_REJECT);
		v[0] = REJECT_NO_RESOURCES;
		nwk_reply_parm(trans, P_REJECT_REASON, 1, v);
		nwk_send_reply(trans);
		return;
	}

	do {
		snprintf(q, 200,
			"SELECT regtable.phone, MAX(hdb.tpui)+1 FROM regtable,hdb WHERE tms > (UNIX_TIMESTAMP() - 30) GROUP BY regtable.phone");
		sql_res = NULL;
		sql_query(trans->sql, q, &sql_res);
		if (!sql_res) break;

		row = sql_fetch_result(sql_res);
		if (row) {
			/* Add subscription */
			snprintf(q, 200,
				"INSERT INTO hdb (tpui, ipui, phone) VALUES(%s, '%s', '%s')",
				row[1], ipui_str, row[0]);
			sql_query(trans->sql, q, NULL);
			/* Signal */
			snprintf(q, 200,
				"UPDATE regtable SET tpui = %s WHERE phone = '%s'", row[1], row[0]);
			sql_query(trans->sql, q, NULL);
			sql_free_result(sql_res);
		} else {
			sql_free_result(sql_res);
			break;
		}

		nwk_reply(trans, DECT_MM_ACCESS_RIGHTS_ACCEPT);
		/* Portable Identity */
		nwk_reply_parm(trans, P_PORTABLE_IDENTITY, vlen, val);
		/* Fixed Identity */
		v[0] = 0xA0; /* Type = PARK */
		v[1] = 0xA0; /* Len = 32bits */
		v[2] = 0x15;
		v[3] = 0x24;
		v[4] = 0x20;
		v[5] = 0x01;
		nwk_reply_parm(trans, P_FIXED_IDENTITY, 6, v);
		nwk_send_reply(trans);
		return;
	} while (0);

	nwk_reply(trans, DECT_MM_ACCESS_RIGHTS_REJECT);
	nwk_send_reply(trans);
}

char * mm_dump_cmd(unsigned char cmd)
{
	switch (cmd) {
		case DECT_MM_LOCATE_REQUEST:
			return "LOCATE-REQUEST";
		case DECT_MM_LOCATE_ACCEPT:
			return "LOCATE-ACCEPT";
		case DECT_MM_LOCATE_REJECT:
			return "LOCATE-REJECT";
		case DECT_MM_DETACH:
			return "DETACH";

		case DECT_MM_AUTHENTICATION_REQUEST:
			return "AUTHENTICATION-REQUEST";

		case DECT_MM_ACCESS_RIGHTS_REQUEST:
			return "ACCESS-RIGHTS-REQUEST";
		case DECT_MM_ACCESS_RIGHTS_ACCEPT:
			return "ACCESS-RIGHTS-ACCEPT";
		case DECT_MM_ACCESS_RIGHTS_REJECT:
			return "ACCESS-RIGHTS-REJECT";
		case DECT_MM_ACCESS_TERM_REQUEST:
			return "ACCESS-RIGHTS-TERM-REQUEST";
		case DECT_MM_ACCESS_TERM_ACCEPT:
			return "ACCESS-RIGHTS-TERM-ACCEPT";
		case DECT_MM_ACCESS_TERM_REJECT:
			return "ACCESS-RIGHTS-TERM-REJECT";
	}
	return "<UNKNOWN>";
}

void mm_command(struct nwk_transaction *trans, unsigned char cmd, unsigned char *data, int len)
{
	switch (cmd) {
		case DECT_MM_LOCATE_REQUEST:
			mm_locate_request(trans, data, len);
			break;

		case DECT_MM_ACCESS_RIGHTS_REQUEST:
			mm_access_rights_request(trans, data, len);
			break;
	}
}
