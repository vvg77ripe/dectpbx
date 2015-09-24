
#include "mcf5282.h"

#include "eeprom.h"
#include "timer.h"
#include "term/terminal.h"

struct eeprom_data eeprom;


static void eeprom_defaults()
{
	memset(&eeprom, 0, sizeof(eeprom));

	/* Hardware Version */
	eeprom.sign = CONFIG_VERSION;
	eeprom.version = 1;

	/* Fast Ethernet Controller */
	eeprom.fec_mac[0] = 0x00;
	eeprom.fec_mac[1] = 0x52;
	eeprom.fec_mac[2] = 0x42;
	eeprom.fec_mac[3] = 0x02;
	eeprom.fec_mac[4] = 0x00;
	eeprom.fec_mac[5] = 0x01;

	/* IP Protocol */
	eeprom.ip_addr = (172 << 24) | (21 << 16) | (96 << 8) | (160);
	eeprom.ip_mask = 24;
	eeprom.ip_router = (172 << 24) | (21 << 16) | (96 << 8) | (131);

	/* TFTP Server */
	eeprom.tftp_server = (85 << 24) | (159 << 16) | (40 << 8) | (50);
}

static void i2c_init()
{
	int i;

	/* Enable I2C at 100kHz */
	MCF5282_I2C_I2FDR = 0x15;
    MCF5282_I2C_I2ADR = 0x6A;
	MCF5282_I2C_I2CR = MCF5282_I2C_I2CR_IEN;
	if (MCF5282_I2C_I2SR & MCF5282_I2C_I2SR_IBB) {
		/* Reset I2C */
		MCF5282_I2C_I2CR = 0x00;
		MCF5282_I2C_I2CR = 0xA0;
		i = MCF5282_I2C_I2DR;
		MCF5282_I2C_I2SR = 0x00;
		MCF5282_I2C_I2CR = 0x00;
		/* Wait and init */
		tmr_gp_wait(100);
		MCF5282_I2C_I2CR = MCF5282_I2C_I2CR_IEN;
	}
}

uint8 i2c_write(uint8 addr, uint8 *buf, uint8 len)
{
	int i, timeout;

	/* Clear all interrupts */
	MCF5282_I2C_I2SR = 0;
	tmr_gp_wait(1);

	/* Start condition */
	if (MCF5282_I2C_I2CR & MCF5282_I2C_I2CR_MSTA) {
		MCF5282_I2C_I2CR |= (MCF5282_I2C_I2CR_RSTA | MCF5282_I2C_I2CR_MTX);
	} else {
		MCF5282_I2C_I2CR |= (MCF5282_I2C_I2CR_MSTA | MCF5282_I2C_I2CR_MTX);
	}

	/* Wait for I2SR[IBB] (bus busy) to be set */
	timeout = 0;
	while ( !(MCF5282_I2C_I2SR & MCF5282_I2C_I2SR_IBB) )
		if (timeout++ == 30000) {
			return 0;
		}

	/* Slave address & write */
	MCF5282_I2C_I2DR = addr & 0xFE;

	/* Wait to complete */
	timeout = 0;
	while ( !(MCF5282_I2C_I2SR & MCF5282_I2C_I2SR_IIF) )
		if (timeout++ == 30000) {
			MCF5282_I2C_I2CR = MCF5282_I2C_I2CR_IEN;
			return 0;
		}
	MCF5282_I2C_I2SR &= ~MCF5282_I2C_I2SR_IIF;

	/* Check for errors */
	if (MCF5282_I2C_I2SR & MCF5282_I2C_I2SR_RXAK) {
		MCF5282_I2C_I2CR = MCF5282_I2C_I2CR_IEN;
		return 0;
	}

	for (i = 0; i < len; i++) {
		/* Send byte */
		MCF5282_I2C_I2DR = buf[i];

		/* Wait to complete */
		timeout = 0;
		while ( !(MCF5282_I2C_I2SR & MCF5282_I2C_I2SR_IIF) )
			if (timeout++ == 30000) {
				MCF5282_I2C_I2CR = MCF5282_I2C_I2CR_IEN;
				return 0;
			}
		MCF5282_I2C_I2SR &= ~MCF5282_I2C_I2SR_IIF;
	}

	return len;
}

uint8 i2c_read(uint8 addr, uint8 *buf, uint16 len)
{
	int i, timeout;

	/* Clear all interrupts */
	MCF5282_I2C_I2SR = 0;

	/* Start condition */
	if (MCF5282_I2C_I2CR & MCF5282_I2C_I2CR_MSTA) {
		MCF5282_I2C_I2CR |= (MCF5282_I2C_I2CR_RSTA | MCF5282_I2C_I2CR_MTX);
	} else {
		MCF5282_I2C_I2CR |= (MCF5282_I2C_I2CR_MSTA | MCF5282_I2C_I2CR_MTX);
	}

	/* Wait for I2SR[IBB] (bus busy) to be set */
	timeout = 0;
	while ( !(MCF5282_I2C_I2SR & MCF5282_I2C_I2SR_IBB) )
		if (timeout++ == 30000) {
			return 0;
		}

	/* Slave address & read */
	MCF5282_I2C_I2DR = addr | 0x01;

	/* Wait to complete */
	timeout = 0;
	while ( !(MCF5282_I2C_I2SR & MCF5282_I2C_I2SR_IIF) )
		if (timeout++ == 30000) {
			MCF5282_I2C_I2CR = MCF5282_I2C_I2CR_IEN;
			return 0;
		}
	MCF5282_I2C_I2SR &= ~MCF5282_I2C_I2SR_IIF;

	/* Check for errors */
	if (MCF5282_I2C_I2SR & MCF5282_I2C_I2SR_RXAK) {
		MCF5282_I2C_I2CR = MCF5282_I2C_I2CR_IEN;
		return 0;
	}

	/* Read mode */
	MCF5282_I2C_I2CR &= ~MCF5282_I2C_I2CR_MTX;
	i = MCF5282_I2C_I2DR;

	for (i = 0; i < len; i++) {
		/* Wait to complete */
		timeout = 0;
		while ( !(MCF5282_I2C_I2SR & MCF5282_I2C_I2SR_IIF) )
			if (timeout++ == 30000) {
				MCF5282_I2C_I2CR = MCF5282_I2C_I2CR_IEN;
				return 0;
			}
		MCF5282_I2C_I2SR &= ~MCF5282_I2C_I2SR_IIF;

		/* Check for last byte */
		if (i == (len-2)) MCF5282_I2C_I2CR |= MCF5282_I2C_I2CR_TXAK;
		if (i == (len-1)) MCF5282_I2C_I2CR &= ~MCF5282_I2C_I2CR_MSTA;

		/* Read byte */
		buf[i] = MCF5282_I2C_I2DR;
	}

	MCF5282_I2C_I2CR = MCF5282_I2C_I2CR_IEN;
	return len;
}

void i2c_stop()
{
	MCF5282_I2C_I2CR = MCF5282_I2C_I2CR_IEN;
}


int eeprom_init()
{
	i2c_init();
	eeprom_read(0, 0, (uint8 *)&eeprom, sizeof(eeprom));

	/* Check for valid configuration in EEPROM */
	if (eeprom.sign != CONFIG_VERSION) {
		eeprom_defaults();
	}

	return 0;
}

int eeprom_read(uint8 chip, uint16 pos, uint8 *buf, uint16 len)
{
	uint8 addr;
	uint8 b[2];

	/* 1ms sync */
	tmr_gp_wait(1);

	/* Calculate chip address */
	addr = 0xA0 | (chip << 1);
	b[0] = pos >> 8;
	b[1] = pos & 0xFF;

	/* Write start position */
	if (i2c_write(addr, b, 2) != 2) return 0;

	/* Read */
	return i2c_read(addr, buf, len);
}

static int eeprom_write_byte(uint8 chip, uint16 pos, uint8 byte)
{
	uint8 addr;
	uint8 b[3];
	int timeout;

	/* Calculate chip address */
	addr = 0xA0 | (chip << 1);
	b[0] = pos >> 8;
	b[1] = pos & 0xFF;
	b[2] = byte;

	/* Write byte */
	if (i2c_write(addr, b, 3) != 3) return 0;
	i2c_stop();

	/* Wait for complete */
	for (timeout = 0; timeout < 50; timeout++) {
		if (i2c_write(addr, b, 1) == 1) {
			i2c_stop();
			return 1;
		}
		i2c_stop();
	}

	/* Timed out */
	return 0;
}

int eeprom_write(uint8 chip, uint16 pos, uint8 *buf, uint8 len)
{
	int i;

	/* 1ms sync */
	tmr_gp_wait(1);

	/* write data */
	for (i = 0; i < len; i++) {
		if (eeprom_write_byte(chip, pos+i, buf[i]) == 0) return 0;
	}

	return len;
}
