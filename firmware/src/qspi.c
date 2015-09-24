
#include <mcf5282.h>

#include "timer.h"
#include "qspi.h"
#include "dphone/kxt.h"


static uint8 qspi_last;		/* Last processed QSPI frame */
static uint8 qspi_pid;


void qspi_init()
{
	int i;

	/* Enable QSPI I/O pins (DOUT, DIN, CLK, CS0, CS1) */
	MCF5282_GPIO_PQSPAR = 0x1F;

	/* 1.024 MHz, 16 bit */
	MCF5282_QSPI_QMR = MCF5282_QSPI_QMR_MSTR
		| MCF5282_QSPI_QMR_CPOL
		| MCF5282_QSPI_QMR_CPHA
		| 32;

	/* 16 commands in queue, wrap mode */
	MCF5282_QSPI_QWR = MCF5282_QSPI_QWR_WREN | MCF5282_QSPI_QWR_CSIV | 0x0F00;
	qspi_last = 0;

	/* Disable and clear interrupts */
	MCF5282_QSPI_QIR = 0x000F;

	/* Write commands */
	MCF5282_QSPI_QAR = 0x20;
	for (i = 0; i < 16; i++) {
		/* Panasonic KX-T interface */
		MCF5282_QSPI_QDR = MCF5282_QSPI_QCR_BITSE | MCF5282_QSPI_QCR_DT | (0xE00);
	}

	/* Write Test data */
	MCF5282_QSPI_QAR = 0x00;
	for (i = 0; i < 16; i++) {
		/* Panasonic KX-T interface */
		MCF5282_QSPI_QDR = 0x0300;
	}

	/* Start QSPI, 223-halfbit delay */
	MCF5282_QSPI_QDLYR = MCF5282_QSPI_QDLYR_SPE | 223;

	/* Create QSPI process */
	qspi_pid = tmr_load_register("QSPI Process");
}

void qspi_process()
{
	uint8	qspi_crnt, pid;
	uint16	data;

	qspi_crnt = (MCF5282_QSPI_QWR & 0x00F0) >> 4;
	if (qspi_last == qspi_crnt) return;

	/* Switch to QSPI process */
	pid = tmr_load_switch(qspi_pid);

	/* Process data */
	do {
		/* Seek to next slot (modulo 16) */
		qspi_last = (qspi_last + 1) & 0xF;

		/* Receive memory */
		MCF5282_QSPI_QAR = 0x10 + qspi_last;
		data = MCF5282_QSPI_QDR;

		data = kxt_process_data(data);

		/* Transmit memory */
		MCF5282_QSPI_QAR = 0x00 + qspi_last;
		MCF5282_QSPI_QDR = data;
	} while (qspi_last != qspi_crnt);

	/* Switch back */
	tmr_load_switch(pid);
}
