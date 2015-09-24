
#include "mcf5282.h"

#include "eeprom.h"
#include "timer.h"
#include "network/nbuf.h"
#include "network/if.h"
#include "fec.h"

/* Network Process ID */
uint8	net_pid;

/*
 * Read MII register
 * Busy-waits, but transfer time should be short!
 */
int fec_getMII(int phyNumber, int regNumber)
{
	MCF5282_FEC_MMFR = (0x1 << 30)       |
                       (0x2 << 28)       |
                       (phyNumber << 23) |
                       (regNumber << 18) |
                       (0x2 << 16);
	while ((MCF5282_FEC_EIR & MCF5282_FEC_EIR_MII) == 0);
	MCF5282_FEC_EIR = MCF5282_FEC_EIR_MII;
	return MCF5282_FEC_MMFR & 0xFFFF;
}

/*
 * Write MII register
 * Busy-waits, but transfer time should be short!
 */
void fec_setMII(int phyNumber, int regNumber, int value)
{
	MCF5282_FEC_MMFR = (0x1 << 30)       |
                       (0x1 << 28)       |
                       (phyNumber << 23) |
                       (regNumber << 18) |
                       (0x2 << 16)       |
                       (value & 0xFFFF);
	while ((MCF5282_FEC_EIR & MCF5282_FEC_EIR_MII) == 0);
	MCF5282_FEC_EIR = MCF5282_FEC_EIR_MII;
}

/*
 *
 */
void fec_blink(uint8 type)
{
	fec_setMII(0, 20, 0x8A00);
}

/*
 *
 */
int fec_init()
{
	int i;

	/* Reset the FEC - equivalent to a hard reset */
	MCF5282_FEC_ECR = MCF5282_FEC_ECR_RESET;
	/* Wait for the reset sequence to complete */
	while (MCF5282_FEC_ECR & MCF5282_FEC_ECR_RESET);

	/* Disable all FEC interrupts by clearing the EIMR register */
	MCF5282_FEC_EIMR = 0;
	/* Clear any interrupts by setting all bits in the EIR register */
	MCF5282_FEC_EIR = 0xFFFFFFFF;

	/* Enable MIB Counters */
	for (i = 0; i < 57; i++)
		(*(vuint32  *)(void *)(&__IPSBAR[0x1200 + i*4])) = 0;
	MCF5282_FEC_MIBC = 0;

	/* Set the source address for the controller */
	MCF5282_FEC_PALR = (0 
		| (eeprom.fec_mac[0] <<24) 
		| (eeprom.fec_mac[1] <<16)	
		| (eeprom.fec_mac[2] <<8) 
		| (eeprom.fec_mac[3] <<0)); 
	MCF5282_FEC_PAUR = (0
		| (eeprom.fec_mac[4] <<24)
		| (eeprom.fec_mac[5] <<16));

	/* Initialize the hash table registers */
	MCF5282_FEC_IAUR = 0;
	MCF5282_FEC_IALR = 0;

	/* Setup Buffers */
	MCF5282_FEC_EMRBR = (uint16)RX_BUFFER_SIZE;
	MCF5282_FEC_ERDSR = nbuf_get_start(Rx);
	MCF5282_FEC_ETDSR = nbuf_get_start(Tx);

	/* Set the tranceiver interface to MII mode */
	MCF5282_FEC_RCR = (1522 << 16)
		| MCF5282_FEC_RCR_MII_MODE;
	/* Only operate in half-duplex, no heart beat control */
	MCF5282_FEC_TCR = 0;

	/* Enable FEC */
	MCF5282_FEC_ECR = MCF5282_FEC_ECR_ETHER_EN;

	/* Allow interrupts by setting IMR register */
	/* MCF5282_FEC_EIMR = MCF5282_FEC_EIMR_RXF; */

	/* Indicate that there have been empty receive buffers produced */
	MCF5282_FEC_RDAR = 1;

	/* Enable MII control interface and reset PHY */
	MCF5282_FEC_MSCR = 0x001C;
	fec_setMII(0, 0, 0x8000);

	/* Wait for PHY reset */
	tmr_gp_wait(2);

	/* Create network process */
	net_pid = tmr_load_register("Network");

	return 0;
}

static void fec_rx_release(NBUF* pNbuf)
{
	/* Mark the buffer as empty */
	nbuf_rx_release(pNbuf);

	/* Tell the HW that there has been an empty Rx buffer produced */
	MCF5282_FEC_RDAR = 1;
}

static void fec_receive(NBUF *pNbuf)
{
	IF_PACKET pkt;

	pkt.addr[0] = pNbuf->data[6];
	pkt.addr[1] = pNbuf->data[7];
	pkt.addr[2] = pNbuf->data[8];
	pkt.addr[3] = pNbuf->data[9];
	pkt.addr[4] = pNbuf->data[10];
	pkt.addr[5] = pNbuf->data[11];
	pkt.type = (pNbuf->data[12] << 8) | (pNbuf->data[13]);
	pkt.size = pNbuf->length - 14;
	pkt.data = &pNbuf->data[14];
	if_receive(&pkt);
}

/*
 *
 */
void fec_send(IF_PACKET *pkt, IF_BUFFER *buf)
{
	NBUF *tx_buf;
	IF_BUFFER *data_buf;
	uint16 size;
	int i;

	/* Allocate new TX buffer */
	tx_buf = nbuf_tx_allocate();
	if (!tx_buf) return;

	/* Prepare ethernet header */
	tx_buf->data[0] = pkt->addr[0];
	tx_buf->data[1] = pkt->addr[1];
	tx_buf->data[2] = pkt->addr[2];
	tx_buf->data[3] = pkt->addr[3];
	tx_buf->data[4] = pkt->addr[4];
	tx_buf->data[5] = pkt->addr[5];
	tx_buf->data[6] = eeprom.fec_mac[0];
	tx_buf->data[7] = eeprom.fec_mac[1];
	tx_buf->data[8] = eeprom.fec_mac[2];
	tx_buf->data[9] = eeprom.fec_mac[3];
	tx_buf->data[10] = eeprom.fec_mac[4];
	tx_buf->data[11] = eeprom.fec_mac[5];
	tx_buf->data[12] = pkt->type >> 8;
	tx_buf->data[13] = pkt->type & 0xFF;

	/* Copy packet data */
	data_buf = buf;
	size = 14;
	do {
		for (i = 0; i < data_buf->size; i++)
			tx_buf->data[size+i] = data_buf->data[i];
		size += data_buf->size;
	} while (data_buf = data_buf->next);

	/* Set Frame ready for transmit */
	tx_buf->length = size;
	tx_buf->status |= TX_BD_R;

	/* Mark the buffer as not in use */
	nbuf_tx_release(tx_buf);

	/* Indicate that there has been a transmit buffer produced */
	MCF5282_FEC_TDAR = 1;
}

/*
 *
 */
void fec_process()
{
	NBUF *pNbuf;
	uint8 pid;
	int i;

	/* Receive descriptors polling */
	pNbuf = (NBUF *)nbuf_get_start(Rx);
	for (i = 0; i < NUM_RXBDS; i++) {
		if ( !(pNbuf[i].status & RX_BD_E) ) {
			/* Switch to network process */
			pid = tmr_load_switch(net_pid);
			/* Read packet */
			fec_receive(&pNbuf[i]);
			fec_rx_release(&pNbuf[i]);
			/* Switch back */
			tmr_load_switch(pid);
		}
	}
}

char *fec_link()
{
	uint16 status;

	status = fec_getMII(0, MII_STATUS2);
	if ( !(status & MII_STATUS2_LINK) ) {
		return "not present";
	}

	if (status & MII_STATUS2_DUPLEX) {
		if (status & MII_STATUS2_100MBIT) return "100Mbit FD";
		return "10mbit FD";
	} else {
		if (status & MII_STATUS2_100MBIT) return "100Mbit HD";
		return "10mbit HD";
	}

	/* Never reached */
	return "?";
}
