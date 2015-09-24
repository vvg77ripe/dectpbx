
#include <mcf5282.h>

#include "eeprom.h"
#include "timer.h"
#include "if.h"
#include "arp.h"

#include "term/terminal.h"

static arp_table_rec arp_table[MAX_ARP_ENTRIES];


static void cmd_show_arp(struct terminal *term, int reason)
{
	int i;
	arp_table_rec *arp;

	if (reason == TERM_RSN_EXEC) {

		bprintf(term->out, "IP Address\tMAC Address\t\tExpire\r\n");

		for (i = 0; i < MAX_ARP_ENTRIES; i++) {
			if (arp_table[i].arp_flags & ARP_ENTRY_VALID) {
				arp = &arp_table[i];

				bprintf(term->out, "%i.%i.%i.%i\t%X:%X:%X:%X:%X:%X\t%i\r\n",
					(arp->ip_addr >> 24), (arp->ip_addr >> 16) & 0xFF,
					(arp->ip_addr >> 8) & 0xFF, (arp->ip_addr) & 0xFF,
					arp->hw_addr[0], arp->hw_addr[1], arp->hw_addr[2],
					arp->hw_addr[3], arp->hw_addr[4], arp->hw_addr[5],
					arp->arp_expire);
			}
		} /* for */

	}
}

static void arp_update(uint32 ip_addr, uint8 *mac_addr, uint16 timeout)
{
	int i, j;

	/* Try find valid ARP entry */
	for (i = 0; i < MAX_ARP_ENTRIES; i++) {
		if ((arp_table[i].arp_flags & ARP_ENTRY_VALID)
			&& (arp_table[i].ip_addr == ip_addr)) {
			/* found -- update timeout */
				if (arp_table[i].arp_expire < timeout) arp_table[i].arp_expire = timeout;
			return;
		}
	}

	/* Not found - create new */
	for (i = 0; i < MAX_ARP_ENTRIES; i++) {
		if ( !(arp_table[i].arp_flags & ARP_ENTRY_VALID) ) {
			arp_table[i].arp_flags = ARP_ENTRY_VALID;
			arp_table[i].arp_expire = timeout;
			arp_table[i].ip_addr = ip_addr;
			for (j = 0; j < 6; j++)
				arp_table[i].hw_addr[j] = mac_addr[j];
			break;
		}
	}
}


void arp_init()
{
	int i;
	struct term_command *cmd;

	for (i = 0; i < MAX_ARP_ENTRIES; i++)
		arp_table[i].arp_flags = 0;

	term_find(&cmd, "show", NULL);
	if (cmd) {
		term_reg_command(cmd, "arp", "Show arp table entries", cmd_show_arp);
	}
}

void arp_handler(IF_PACKET *pkt)
{
	arp_frame_hdr *rx_arp;
	IF_BUFFER arp_reply;
	int i;

	rx_arp = (arp_frame_hdr *)pkt->data;

	/* Check to see if addressed to me */
	if (rx_arp->ar_tpa != eeprom.ip_addr) return;

	switch (rx_arp->opcode) {
		case ARP_REQUEST:
			/* Copy sender address */
			rx_arp->ar_tpa = rx_arp->ar_spa;
			for (i = 0; i < rx_arp->ar_hln; i++)
				rx_arp->ar_tha[i] = rx_arp->ar_sha[i];

			/* Fill my address fields */
			rx_arp->ar_spa = eeprom.ip_addr;
			for (i = 0; i < 6; i++)
				rx_arp->ar_sha[i] = eeprom.fec_mac[i];

			/* ARP reply */
			rx_arp->opcode = ARP_REPLY;

			/* Setup buffer and send the frame */
			arp_reply.data = (uint8 *)rx_arp;
			arp_reply.next = NULL;
			arp_reply.size = sizeof(arp_frame_hdr);
			if_send(pkt, &arp_reply);
			break;

		case ARP_REPLY:
			arp_update(rx_arp->ar_spa, rx_arp->ar_sha, ARP_EXPIRE_REPLIED);
			break;
	}
}

int arp_lookup(uint32 ip_addr, uint8 *mac_addr)
{
	int i, j;

	for (i = 0; i < MAX_ARP_ENTRIES; i++) {
		if ((arp_table[i].arp_flags & ARP_ENTRY_VALID)
			&& (arp_table[i].ip_addr == ip_addr)) {
			/* Found ARP entry */
			for (j = 0; j < 6; j++)
				mac_addr[j] = arp_table[i].hw_addr[j];
			return 0;
		}
	}

	/* Not Found */
	return 1;
}

void arp_merge(uint32 ip_addr, uint8 *mac_addr)
{
	arp_update(ip_addr, mac_addr, ARP_EXPIRE_MERGED);
}

void arp_request(uint32 ip_addr)
{
	arp_frame_hdr	arp;
	IF_PACKET		pkt;
	IF_BUFFER		req;

	memset(&arp, 0, sizeof(arp_frame_hdr));

	arp.ar_hrd = 1;
	arp.ar_pro = ETH_P_IP;
	arp.opcode = ARP_REQUEST;

	/* hardware address */
	arp.ar_hln = 6;
	memcpy(&arp.ar_sha, &eeprom.fec_mac, 6);

	/* protocol address */
	arp.ar_pln = 4;
	arp.ar_spa = eeprom.ip_addr;
	arp.ar_tpa = ip_addr;

	/* Setup buffer and send the frame */
	memset(pkt.addr, 0xFF, 6);
	pkt.type = ETH_P_ARP;
	req.data = (uint8 *)&arp;
	req.next = NULL;
	req.size = sizeof(arp_frame_hdr);
	if_send(&pkt, &req);
}
