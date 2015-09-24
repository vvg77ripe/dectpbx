
#include "mcf5282.h"

#include "if.h"
#include "ip.h"
#include "icmp.h"

/*
 * ICMP Receive packet handler
 */
void icmp_handler(ip_frame_hdr *ip, uint8 *data, uint32 size)
{
	IF_BUFFER icmp_buf;
	icmp_message *msg;

	msg = (icmp_message *)data;

	switch (msg->type) {
		case ICMP_ECHO:
			/* Generate echo reply */
			msg->type = ICMP_ECHO_REPLY;
			msg->chksum = 0;
			ip->dest_addr = ip->source_addr;

			/* Calculate checksum */
			msg->chksum = ip_chksum(0, (uint16 *)msg, size);

			/* Prepare buffers and send frame */
			icmp_buf.data = (uint8 *)msg;
			icmp_buf.size = size;
			icmp_buf.next = NULL;
			ip_send(ip, &icmp_buf);
			break;
	}
}
