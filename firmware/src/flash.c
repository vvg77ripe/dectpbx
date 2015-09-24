
#include <mcf5282.h>

#include "flash.h"


#define CFM_WRITE		0x20
#define CFM_MASSERASE	0x41


void flash_init()
{
	uint32 *ptr;

	/* Disable FLASHBAR write-protect */
	asm_wr_flashbar(0x0021);

	/* Setup CFM clock */
	MCF5282_CFM_CFMCLKD = 0x54;
}

void flash_erase_block(uint8 block)
{
	uint32 *ptr;

	ptr = (uint32 *)0x44000000;

	/* Wait for previous command to complete */
	while ( !(MCF5282_CFM_CFMUSTAT & MCF5282_CFM_CFMUSTAT_CBEIF) );

	/* Clear prev status bits */
	MCF5282_CFM_CFMUSTAT = MCF5282_CFM_CFMUSTAT_PVIOL;
	MCF5282_CFM_CFMUSTAT = MCF5282_CFM_CFMUSTAT_ACCERR;

	/* Write address to CFM */
	switch (block) {
		case 0:
			ptr[0] = 0;
			break;
		case 1:
			ptr[0x00010000] = 0;
			break;
		default:
			return;
	}

	/* Erase command */
	MCF5282_CFM_CFMCMD = CFM_MASSERASE;

	/* GO */
	MCF5282_CFM_CFMUSTAT = MCF5282_CFM_CFMUSTAT_CBEIF;
}

void flash_write(uint32 addr, uint32 data)
{
	uint32 *ptr;

	ptr = (uint32 *)0x44000000;

	/* Wait for previous command to complete */
	while ( !(MCF5282_CFM_CFMUSTAT & MCF5282_CFM_CFMUSTAT_CBEIF) );

	/* Clear prev status bits */
	MCF5282_CFM_CFMUSTAT = MCF5282_CFM_CFMUSTAT_PVIOL;
	MCF5282_CFM_CFMUSTAT = MCF5282_CFM_CFMUSTAT_ACCERR;

	/* Write address to CFM */
	ptr[addr >> 2] = data;

	/* Erase command */
	MCF5282_CFM_CFMCMD = CFM_WRITE;

	/* GO */
	MCF5282_CFM_CFMUSTAT = MCF5282_CFM_CFMUSTAT_CBEIF;
}

void flash_copy()
{
	uint32 *ptr;
	int i;

	ptr = (uint32 *)0x00040000;

	flash_erase_block(0);
	for (i = 0; i < 0x10000; i++) {
		flash_write(i * 4, ptr[i]);
		if (!(i % 1000)) {
			MCF5282_WTM_WSR = 0x5555;
			MCF5282_WTM_WSR = 0xAAAA;
		}
	}

	/* Software reset */
	MCF5282_RESET_RCR = MCF5282_RESET_RCR_SOFTRST;
}
