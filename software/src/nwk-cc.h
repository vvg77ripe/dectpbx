
#ifndef _NWK_CC_H
#define _NWK_CC_H

#define DECT_CC_ALERTING		0x01
#define DECT_CC_CALL_PROC		0x02
#define DECT_CC_SETUP			0x05
#define DECT_CC_CONNECT			0x07
#define DECT_CC_SETUP_ACK		0x0D
#define DECT_CC_CONNECT_ACK		0x0F
#define DECT_CC_SERVICE_CHANGE	0x20
#define DECT_CC_SERVICE_ACCEPT	0x21
#define DECT_CC_SERVICE_REJECT	0x23
#define DECT_CC_RELEASE			0x4D
#define DECT_CC_RELEASE_COM		0x5A
#define DECT_CC_IWU_INFO		0x60
#define DECT_CC_FACILITY		0x62
#define DECT_CC_NOTIFY			0x6E
#define DECT_CC_INFO			0x7B

char * cc_dump_cmd(unsigned char cmd);
void cc_command(struct nwk_transaction *trans, unsigned char cmd, unsigned char *data, int len);
void cc_setup_incoming(nwk_trans_t *trans, pp_info_t *pp, int type, void *ptr);

#endif
