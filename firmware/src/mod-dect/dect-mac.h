
#define DECT_TX_IDLE	0
#define DECT_TX_P00		1
#define DECT_TX_P32		2

#define DECT_RX_IDLE	0
#define DECT_RX_P32		1

#define DECT_MT_BASIC_ACCESS_REQUEST		0x00
#define DECT_MT_BASIC_BEARER_HANDOVER		0x01
#define DECT_MT_BASIC_CONNECTION_HANDOVER	0x02
#define DECT_MT_BASIC_BEARER_CONFIRM		0x04
#define DECT_MT_BASIC_WAIT					0x05
#define DECT_MT_BASIC_RELEASE				0x0F

#define DECT_MBC_ACCESS_REQUEST			0
#define DECT_MBC_BEARER_HANDOVER		1
#define DECT_MBC_CONNECTION_HANDOVER	2


void dect_init_slots(void);
void dect_next_frame(void);
void dect_recv(uint8 sn, uint8 *buf);
void dect_recv_sync(uint8 sn, uint8 *buf);
void dect_recv_nosync(uint8 sn);

void dect_mbc_init(void);
void dect_mbc_voice_recv(uint32 pmid, uint8 ecn, uint8 *data, uint16 len);
