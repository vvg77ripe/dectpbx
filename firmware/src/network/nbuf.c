/*
 * File:	nbuf.c
 * Purpose:	Implementation of network buffer scheme.
 *
 * Notes:	These routines implement a static buffer scheme.
 *			The buffer descriptors are as specified by the 
 *			MPC860T/MCF5282 FEC. These routines require that
 *			every packet to be transmitted contains less than
 *			or equal to TX_BUFFER_SIZE bytes.
 *
 *			These routines were written to be used with generic
 *			NE2000 drivers as well as MPC860T/MCF5282 drivers.
 *
 */

#include "mcf5282.h"

#include "nbuf.h"

//#include "src/ethernet/nif.h"

/********************************************************************/

/* Buffer descriptor indexes */
uint8 iTxbd;
uint8 iRxbd;

/* Buffer Descriptors -- must be aligned on a 4-byte boundary but a 
 * 16-byte boundary is recommended. To avoid playing games with the 
 * various compilers and their different extension to ANSI C, these 
 * buffers are aligned by allocating an extra line of data and 
 * adjusting the pointers in nbuf_init().
 */
uint8 unaligned_txbd[(sizeof(NBUF) * NUM_TXBDS) + 16];
uint8 unaligned_rxbd[(sizeof(NBUF) * NUM_RXBDS) + 16];

NBUF *TxNBUF;
NBUF *RxNBUF;

/* Data Buffers -- must be aligned on a 16-byte boundary. To avoid 
 * playing games with the various compilers and their different 
 * extension to ANSI C, these buffers are aligned by allocating an 
 * extra line of data and adjusting the pointers in nbuf_init().
 */
uint8 unaligned_txbuffer[(TX_BUFFER_SIZE * NUM_TXBDS) + 16];
uint8 unaligned_rxbuffer[(RX_BUFFER_SIZE * NUM_RXBDS) + 16];

uint8 *TxBuffer;
uint8 *RxBuffer;

/********************************************************************/
void
nbuf_init ()
{
	uint8 i;

	TxNBUF = (NBUF *)((uint32)(unaligned_txbd + 16) & 0xFFFFFFF0);
	RxNBUF = (NBUF *)((uint32)(unaligned_rxbd + 16) & 0xFFFFFFF0);

	TxBuffer = (uint8 *)((uint32)(unaligned_txbuffer + 16) & 0xFFFFFFF0);
	RxBuffer = (uint8 *)((uint32)(unaligned_rxbuffer + 16) & 0xFFFFFFF0);

	/* Initialize receive descriptor ring */
	for (i = 0; i < NUM_RXBDS; i++)
	{
		RxNBUF[i].status = RX_BD_E;
		RxNBUF[i].length = 0;
		RxNBUF[i].data = &RxBuffer[i * RX_BUFFER_SIZE];
	}
	/* Set the Wrap bit on the last one in the ring */
	RxNBUF[NUM_RXBDS - 1].status |= RX_BD_W;

	/* Initialize transmit descriptor ring */
	for (i = 0; i < NUM_TXBDS; i++)
	{
		TxNBUF[i].status = TX_BD_L | TX_BD_TC;
		TxNBUF[i].length = 0;
		TxNBUF[i].data = &TxBuffer[i * TX_BUFFER_SIZE];
	}
	/* Set the Wrap bit on the last one in the ring */
	TxNBUF[NUM_TXBDS - 1].status |= TX_BD_W;

	/* Initialize the buffer descriptor indexes */
	iTxbd = iRxbd = 0;

	return;
}
/********************************************************************/
uint32
nbuf_get_start(uint8 direction)
{
	/* 
	 * Return the address of the first buffer descriptor in the ring.
	 * This routine is needed by the FEC of the MPC860T and MCF5282
	 * in order to write the Rx/Tx descriptor ring start registers
	 */
	switch (direction){
	case Rx:
		return (uint32)RxNBUF;
	case Tx:
	default:
		return (uint32)TxNBUF;
	}
}

/********************************************************************/
NBUF *
nbuf_rx_allocate ()
{
	/* This routine alters shared data. Disable interrupts! */
	int old_ipl = asm_set_ipl(6);

	/* Return a pointer to the next empty Rx Buffer Descriptor */
	int i = iRxbd;

	/* Check to see if the ring of BDs is full */
	if (RxNBUF[i].status & RX_BD_INUSE)
		return NULL;

	/* Mark the buffer as in use */
	RxNBUF[i].status |= RX_BD_INUSE;
	
	/* increment the circular index */
	iRxbd = (uint8)((iRxbd + 1) % NUM_RXBDS);

	/* Restore previous IPL */
	asm_set_ipl(old_ipl);

	return &RxNBUF[i];
}

/********************************************************************/
NBUF *
nbuf_tx_allocate ()
{
	/* This routine alters shared data. Disable interrupts! */
	int old_ipl = asm_set_ipl(6);

	/* Return a pointer to the next empty Tx Buffer Descriptor */
	int i = iTxbd;

	/* Check to see if ring of BDs is full */
	if ((TxNBUF[i].status & TX_BD_INUSE)
		|| (TxNBUF[i].status & TX_BD_R))
		return NULL;
	
	/* Mark the buffer as Ready (in use) */
	/* FEC must set R bit in transmit routine */
	TxNBUF[i].status |= TX_BD_INUSE;

	/* increment the circular index */
	iTxbd = (uint8)((iTxbd + 1) % NUM_TXBDS);

	/* Restore previous IPL */
	asm_set_ipl(old_ipl);

	return &TxNBUF[i];
}

/********************************************************************/
void
nbuf_rx_release (NBUF* pNbuf)
{
	/* This routine alters shared data. Disable interrupts! */
	int old_ipl = asm_set_ipl(6);

	/* Mark the buffer as empty and not in use */
	pNbuf->status |= RX_BD_E;
	pNbuf->status &= ~RX_BD_INUSE;

	/* Restore previous IPL */
	asm_set_ipl(old_ipl);
}

/********************************************************************/
void
nbuf_tx_release (NBUF* pNbuf)
{
	/* This routine alters shared data. Disable interrupts! */
	int old_ipl = asm_set_ipl(6);

	/* Mark the buffer as not in use */
	pNbuf->status &= ~TX_BD_INUSE;

	/* Restore previous IPL */
	asm_set_ipl(old_ipl);
}

/********************************************************************/
int
nbuf_rx_next_ready()
{
	/****************************************************************
	 This function checks the EMPTY bit of the next Rx buffer to be
	 allocated. If the EMPTY bit is cleared, then the next buffer in
	 the ring has been filled by the FEC and has not already been
	 allocated and passed up the stack. In this case, the next buffer
	 in the ring is ready to be allocated. Otherwise, the  buffer is
	 either empty or not empty but still in use by a higher level
	 protocol. The FEC receive routine uses this function to determine
	 if multiple buffers where filled by the FEC during a single
	 interrupt event.
	 ****************************************************************/

	return ( !(RxNBUF[iRxbd].status & RX_BD_E));
}

/********************************************************************/
void
nbuf_tx_swap(NBUF **buf1, NBUF **buf2)
{
	/****************************************************************
	 This function swaps the length and data pointers of two Tx buffers.
	 ARP calls this routine to put ARP packets in the buffer ring 
	 ahead of IP packets so that proper ordering is maintained in the 
	 buffer ring.  This is only required when using the FEC of the 
	 MCF5282/MPC860T.
	 ****************************************************************/
	NBUF *ptemp;
	NBUF temp;
	
	temp.length = (*buf1)->length;
	temp.data = (*buf1)->data;
	(*buf1)->length = (*buf2)->length;
	(*buf1)->data = (*buf2)->data;
	(*buf2)->length = temp.length;
	(*buf2)->data = temp.data;

	ptemp = *buf1;
	*buf1 = *buf2;
	*buf2 = ptemp;
}
