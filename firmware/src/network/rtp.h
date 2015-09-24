
#ifndef _NETWORK_RTP_H
#define _NETWORK_RTP_H

#define RTP_BUFFER_SIZE		256
#define RTP_BUFFER_MASK		0x00FF

typedef struct {
	uint8	flags;
	uint8	ptype;
	uint16	seq;
	uint32	timestamp;
	uint32	ssrc;
} rtp_frame_hdr;

void rtp_init(void);
void rtp_handler(uint8 *data, uint16 size);

uint8 *rtp_get_rx_buffer(void);

#endif
