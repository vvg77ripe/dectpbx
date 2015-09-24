
#ifndef _EEPROM_H
#define _EEPROM_H

#include "config.h"

#define CONFIG_VERSION		1

#define CONFIG_PASS_NONE	0	/* No password */
#define CONFIG_PASS_TEXT	1	/* Clear text password */

struct eeprom_data {
	unsigned char sign;			/* config structure version */
	unsigned char version;		/* Hardware version */

	/* Fast Ethernet Controller */
	unsigned char fec_mac[6];

	/* IP Protocol Data */
	uint32	ip_addr;
	uint8	ip_mask;
	uint32	ip_router;

	/* TFTP Server */
	uint32	tftp_server;

	/* System password */
	uint8	pass_type;			/* Password data type */
	uint8	pass_data[16];		/* Password data */
} PACKED;

extern struct eeprom_data eeprom;

int eeprom_init(void);
int eeprom_read(uint8 chip, uint16 pos, uint8 *buf, uint16 len);
int eeprom_write(uint8 chip, uint16 pos, uint8 *buf, uint8 len);

uint8 i2c_read(uint8 addr, uint8 *buf, uint16 len);
uint8 i2c_write(uint8 addr, uint8 *buf, uint8 len);
void i2c_stop(void);

#endif
