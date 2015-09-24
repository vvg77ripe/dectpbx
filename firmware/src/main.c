/********************************************************************
 * Ethernet Multimedia Adaptor Firmware
 * Written by Vasiliy Voropaev :: http://vvg.pp.ru/
 *
 *
 ********************************************************************/

#include <mcf5282.h>
#include <stdlib.h>

#include "network/if.h"
#include "network/ip.h"
#include "fec.h"
#include "network/nbuf.h"
#include "eeprom.h"
#include "timer.h"
#include "qspi.h"

#include "network/telnet.h"
#include "network/rtp.h"
#include "network/tftp.h"
#include "term/terminal.h"

#include "dphone/kxt.h"
#include "module.h"


/* Code in RAM */
extern char __RAMTEXT_LOAD[];
extern char __RAMTEXT_START[];
extern char __RAMTEXT_SIZE[];
static char *rt_lma;
static char *rt_vma;
static int	rt_size;

/* BSS */
extern char __BSS_START[];
extern char __BSS_END[];

/*
 * I dont know what this function for, but gcc
 * uses this symbol.
 */
void __main(void);
void __main()
{
}

/* irq_handler()
 *
 */
void irq_handler(void);
void irq_handler()
{
}

int main(void)
{
	/* PLL config -- MFD = 2 (8x), RFD = 0 (%1) */
	MCF5282_CLOCK_SYNCR = 0x2000;
	while (!(MCF5282_CLOCK_SYNSR & MCF5282_CLOCK_SYNSR_LOCK));

	/* Flash setup */
	MCF5282_CFM_CFMPROT = 0;
	MCF5282_CFM_CFMSACC = 0;
	MCF5282_CFM_CFMDACC = 0;

	/* RAM Memory Setup */
	MCF5282_SCM_RAMBAR = 0x10000000 | MCF5282_SCM_RAMBAR_BDE;
	rt_lma = __RAMTEXT_LOAD;
	rt_vma = __RAMTEXT_START;
	rt_size = (int)__RAMTEXT_SIZE;
	while (rt_size--) {
		*rt_vma++ = *rt_lma++;
	}
	memset(__BSS_START, 0, (uint32)__BSS_END - (uint32)__BSS_START);
	mem_init();

	/* CS0 setup */
	MCF5282_CS0_CSAR = 0x1001;
	MCF5282_CS0_CSMR = MCF5282_CS_CSMR_BAM_64K | MCF5282_CS_CSMR_V;
	MCF5282_CS0_CSCR = MCF5282_CS_CSCR_AA | MCF5282_CS_CSCR_PS_8;

	/* LED on port B4 */
	MCF5282_GPIO_PBCDPAR = 0;
	MCF5282_GPIO_DDRB = 0x10;

	/* Enable MDC, MDIO, SCL, SDA */
	MCF5282_GPIO_PASPAR = 0x0F0F;
	/* Enable FEC MII */
	MCF5282_GPIO_PEHLPAR = 0x00C0;

	/* Initalize timers and wait 100ms */
	/* for power stabilization */
	tmr_init();
	tmr_gp_wait(100);

	eeprom_init();
	qspi_init();
	term_init();
	tmr_init_terminal();

	/* Network Initialization */
	nbuf_init();
	fec_init();
	ip_init();
	rtp_init();
	tftp_init();

	/* Services */
	telnet_init();

	/* Peripherals */
	kxt_init();
	mod_init();

	do {
		tmr_process();
		qspi_process();

		fec_process();
		ip_process();
		telnet_process();
		term_process();

		mod_process();

		MCF5282_WTM_WSR = 0x5555;
		MCF5282_WTM_WSR = 0xAAAA;
	} while (1);

	/* Never reached */
	return 0;
}
