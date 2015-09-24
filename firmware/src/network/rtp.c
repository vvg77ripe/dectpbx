
#include <mcf5282.h>
#include <stdio.h>

#include "if.h"
#include "ip.h"
#include "udp.h"

#include "rtp.h"


static uint8 rtp_rxbuffer[RTP_BUFFER_SIZE];
static fifo_buffer rtp_rxfifo;


void rtp_init()
{
	rtp_rxfifo.buf = rtp_rxbuffer;
	rtp_rxfifo.length = RTP_BUFFER_SIZE;
	rtp_rxfifo.start = 0;
	rtp_rxfifo.stop = 0;
}

void rtp_handler(uint8 *data, uint16 size)
{
	rtp_frame_hdr *rtp;
	uint8 *rtp_data;
	uint16 hdr_len, rtp_size;

	rtp = (rtp_frame_hdr *)data;

	/* Calculate RTP header size */
	hdr_len = (rtp->flags & 0x0F) * 4 + sizeof(rtp_frame_hdr);
	if (size <= hdr_len) return;

	rtp_data = &data[hdr_len];
	rtp_size = size - hdr_len;

	while (rtp_size--) {
		rtp_rxbuffer[rtp_rxfifo.stop] = *rtp_data++;
		rtp_rxfifo.stop = (++rtp_rxfifo.stop) & RTP_BUFFER_MASK;
	}
}

uint8 *rtp_get_rx_buffer()
{
	return rtp_rxbuffer;
}
