/*
 * File:		nbuf.h
 * Purpose:		Definitions for Network Buffer Allocation.
 *
 * Notes:		These routines implement a static buffer scheme.
 *				The buffer descriptors are as specified by the 
 *				MPC860T/MCF5282 FEC.
 *
 */

#ifndef _NBUF_H
#define _NBUF_H

/********************************************************************/

#define Rx	1
#define Tx	0

/*
 * Buffer sizes in bytes -- The following values were chosen based 
 * on TFTP maximum packet sizes.  These sizes may need to be 
 * increased to implement other protocols.
 */
#define RX_BUFFER_SIZE 1536	/* must be divisible by 16 */
#define TX_BUFFER_SIZE 1536

/* Number of Receive and Transmit Buffers and Buffer Descriptors */
#define NUM_RXBDS 4
#define NUM_TXBDS 2

/* Buffer Descriptor Format */
typedef struct
{
	uint16 status;	/* control and status */
	uint16 length;	/* transfer length */
	uint8  *data;	/* buffer address */
} NBUF;

/********************************************************************/

/*
 * Bit level Buffer Descriptor definitions
 */

#define TX_BD_R			0x8000
#define TX_BD_INUSE		0x4000
#define TX_BD_TO1		0x4000
#define TX_BD_W			0x2000
#define TX_BD_TO2		0x1000
#define TX_BD_L			0x0800
#define TX_BD_TC		0x0400
#define TX_BD_DEF		0x0200
#define TX_BD_HB		0x0100
#define TX_BD_LC		0x0080
#define TX_BD_RL		0x0040
#define TX_BD_UN		0x0002
#define TX_BD_CSL		0x0001

#define RX_BD_E			0x8000
#define RX_BD_INUSE		0x4000
#define RX_BD_R01		0x4000
#define RX_BD_W			0x2000
#define RX_BD_R02		0x1000
#define RX_BD_L			0x0800
#define RX_BD_M			0x0100
#define RX_BD_BC		0x0080
#define RX_BD_MC		0x0040
#define RX_BD_LG		0x0020
#define RX_BD_NO		0x0010
#define RX_BD_SH		0x0008
#define RX_BD_CR		0x0004
#define RX_BD_OV		0x0002
#define RX_BD_TR		0x0001

/*******************************************************************/

/*
 * Functions to manipulate the network buffers.
 */
void
nbuf_init (void);

uint32
nbuf_get_start(uint8);

NBUF *
nbuf_rx_allocate (void);

NBUF *
nbuf_tx_allocate (void);

void
nbuf_rx_release (NBUF *);

void
nbuf_tx_release (NBUF *);

int
nbuf_rx_next_ready(void);

void
nbuf_tx_swap(NBUF **, NBUF **);

/********************************************************************/

#endif 	/* _NBUF_H */
