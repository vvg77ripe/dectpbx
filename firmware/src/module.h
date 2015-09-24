
#ifndef _MODULE_H
#define _MODULE_H

#include "config.h"


#define MODULE_TYPE_DECT		0x0001		/* DECT Fixed Part */
#define MODULE_TYPE_LSIC		0x0002		/* Low Speed Interface Card */


struct module_config {
	unsigned char	zero;		/* 0x00 */
	unsigned char	sign;		/* 0x52 */
	unsigned short	type;		/* Module Type */
	unsigned short	rev;		/* Hardware revision number */
	unsigned short	flags;		/* Reserved for flags */
	char			name[56];	/* Module name */
} PACKED;

struct module_func {
	void (*mod_process)(void);	/* IDLE processing */
	int (*mod_save)(void);		/* Save configuration */
};

void mod_init(void);
void mod_set_callbacks(struct module_func *func);

void mod_process(void);
int mod_save(void);

#endif
