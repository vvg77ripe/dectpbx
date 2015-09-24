
#ifndef _TIMER_H
#define _TIMER_H

#include "config.h"

#define MAX_TIMERS	16
#define MAX_PID		8		/* Maximum Process ID */

#define TMR_EVENT	1
#define TMR_ACTIVE	2

typedef struct tmr_data {
	uint32 value;
	uint8 flags;
} TIMER;

struct tmr_load {
	uint32		time;
	uint32		load;
	char *		pname;
};

void tmr_init(void);
void tmr_init_terminal(void);
void tmr_process(void);

int tmr_add(TIMER *timer);
int tmr_remove(TIMER *timer);

void tmr_gp_blink(int timeout);
void tmr_gp_wait(int timeout);

uint8 tmr_load_register(char *pname);
uint8 tmr_load_switch(uint8 pid);

#endif
