

#define SIP_TMP_SIZE		512

#define MAX_SDP_BODY		150

#define SIP_METHOD_INVITE	1
#define SIP_METHOD_CANCEL	2
#define SIP_METHOD_ACK		3
#define SIP_METHOD_BYE		4


typedef struct {
	/* Transport address */
	uint32	saddr;
	uint16	sport;
	uint32	daddr;
	uint16	dport;
	/* Request/response line */
	uint8	method_id;
	char *	method_name;
	char *	sip_uri;
	uint16	response_code;
	/* Header value pointers */
	char *	hvia;
	char *	hfrom;
	char *	hto;
	char *	hcallid;
	char *	hcseq;
} sip_header;


void sip_handler(uint32 saddr, uint16 sport, uint32 daddr, uint16 dport, uint8 *data, uint16 size);
