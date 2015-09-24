
#include <mcf5282.h>
#include <time.h>

#include "term/terminal.h"
#include "timer.h"

static uint8 tmr_prev;
static TIMER *tmr_list[MAX_TIMERS];

/* System performance counter */
static uint32	tmr_counter, tmr_loops;

/* Date and Time counters */
static uint16	dt_msec;
static uint32	dt_timestamp;		/* Unix timestamp */

/* general purpose timers */
static TIMER tt_blink;
static TIMER tt_wait;

/* number of days in months */
static uint8	mdays[12] =
	{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

/* Processor load measurement */
static struct tmr_load	pid_table[MAX_PID];
static uint8			pid_count;
static uint8			pid_current;
static uint32			pid_timestamp;


/* ==================================================================
 * = terminal commands
 */

static void cmd_show_system_load(struct terminal *term, int reason)
{
	int i;

	if (reason == TERM_RSN_EXEC) {
		bprintf(term->out, "PID  Load  Description\r\n");
		bprintf(term->out, "==================================================\r\n");
		for (i = 0; i < pid_count; i++) {
			bprintf(term->out, " %i   %2i.%i  %s\r\n", i,
				pid_table[i].load / 10, pid_table[i].load % 10, pid_table[i].pname);
		}
	}
}

/* ==================================================================
 * = Initialization procedures
 */

/* tmr_init()
 *   Initialize timer API
 */
void tmr_init()
{
	int i;

	/* Clear all timers */
	for (i = 0; i < MAX_TIMERS; i++)
		tmr_list[i] = NULL;

	/* Enable GPTA */
	MCF5282_GPTA_GPTSCR1 = 0x80;
	/* Set timer prescaler to %128 */
	MCF5282_GPTA_GPTSCR2 = 0x07;

	tmr_prev = MCF5282_GPTA_GPTCNT >> 8;
	dt_timestamp = 0;

	/* General purpose timers */
	tt_blink.flags = 0;
	tmr_add(&tt_blink);
	tt_wait.flags = 0;
	tmr_add(&tt_wait);

	/* Processor load */
	pid_count = 0;
	pid_current = 0;
	tmr_load_register("System IDLE");
}

/* tmr_init_terminal()
 *   Register terminal commands
 */
void tmr_init_terminal()
{
	struct term_command *cmd_show_system;

	term_find(&cmd_show_system, "show system", NULL);
	term_reg_command(cmd_show_system, "load", "Show processor load", cmd_show_system_load);
}

void tmr_process()
{
	uint8 tmr_count, tmr_time;
	int i;

	tmr_counter++;

	/* Process every 1ms interval */
	tmr_count = MCF5282_GPTA_GPTCNT >> 8;
	if (tmr_count == tmr_prev) return;

	tmr_load_switch(0);

	tmr_time = tmr_count - tmr_prev;
	tmr_prev = tmr_count;

	for (i = 0; i < MAX_TIMERS; i++) {
		/* Return if last timer found */
		if (!tmr_list[i]) break;

		if (tmr_list[i]->flags & TMR_ACTIVE) {
			/* decrement timer counters */
			if (tmr_list[i]->value <= tmr_time) {
				/* Clear active flag and generate event */
				tmr_list[i]->value = 0;
				tmr_list[i]->flags &= ~TMR_ACTIVE;
				tmr_list[i]->flags |= TMR_EVENT;
			} else {
				tmr_list[i]->value -= tmr_time;
			}
		}
	}

	/* Process date and time */
	dt_msec += tmr_time;
	if (dt_msec > 1000) {
		dt_msec -= 1000;

		/* One second elapsed */
		tmr_loops = tmr_counter;
		tmr_counter = 0;
		MCF5282_FEC_RMON_T_DROP = tmr_loops;

		/* Processor load snapshot */
		for (i = 0; i < pid_count; i++) {
			pid_table[i].load = pid_table[i].time >> 8;
			pid_table[i].time = 0;
		}

		dt_timestamp++;
	}

	/* Process general purpose timers */
	if (tt_blink.flags & TMR_EVENT) {
		MCF5282_GPIO_PORTB = 0x10;
		tt_blink.flags = 0;
	}
}

/* ==================================================================
 * = Standard libc time functions
 */

time_t time(time_t *T)
{
	if (T) *T = dt_timestamp;
	return dt_timestamp;
}

struct tm *gmtime(const time_t clock, struct tm *res)
{
	time_t		tms, tms_n;

	if (!res) return NULL;

	tms_n = 0;
	res->tm_year = 70;
	res->tm_mon = 0;
	res->tm_mday = 1;

	do {
		tms = tms_n;
		/* increment year */
		res->tm_year++;
		tms_n += 365 * 24 * 3600;
	} while (tms_n < clock);

	return res;
}

time_t timegm(struct tm *tm)
{
	time_t	tms;
	int		i;

	if (!tm) return 0;
	if (tm->tm_year < 70) return 0;

	/* year */
	tms = (tm->tm_year - 70) * 365 * 24 * 3600;
	tms += (tm->tm_year / 4) * 24 * 3600;

	/* month */
	for (i = 0; i < tm->tm_mon; i++) {
		tms += mdays[i] * 24 * 3600;
	}

	/* day */
	tms += (tm->tm_mday-1) * 24 * 3600;

	/* day time */
	tms += tm->tm_hour * 3600 + tm->tm_min * 60 + tm->tm_sec;

	return tms;
}

/* ==================================================================
 * = Timers supporting functions
 */

int tmr_add(TIMER *timer)
{
	int i;

	for (i = 0; i < MAX_TIMERS; i++) {
		if (!tmr_list[i]) {
			tmr_list[i] = timer;
			return 0;
		}
	}

	/* Out of resources */
	return 1;
}

int tmr_remove(TIMER *timer)
{
	int i;

	for (i = 0; i < MAX_TIMERS; i++) {
	}
	return 0;
}


void tmr_gp_blink(int timeout)
{
	tt_blink.value = timeout;
	tt_blink.flags = TMR_ACTIVE;
	MCF5282_GPIO_PORTB = 0;
}

void tmr_gp_wait(int timeout)
{
	tt_wait.value = timeout;
	tt_wait.flags = TMR_ACTIVE;

	do {
		tmr_process();
	} while ( !(tt_wait.flags & TMR_EVENT) );

	tt_wait.flags = 0;
}

/* ==================================================================
 * = Processor load measurement functions
 */

uint8 tmr_load_register(char *pname)
{
	if (pid_count < (MAX_PID-1)) {
		pid_table[pid_count].load = 0;
		pid_table[pid_count].time = 0;
		pid_table[pid_count].pname = pname;
		pid_count++;
		return pid_count-1;
	}

	/* Out of resources */
	return 0;
}

uint8 tmr_load_switch(uint8 pid)
{
	uint16 tms, td;
	uint8 pid_prev;

	/* Calculate elapsed interval */
	tms = MCF5282_GPTA_GPTCNT;
	td = tms - pid_timestamp;
	pid_timestamp = tms;

	/* Increment current process time counter */
	pid_table[pid_current].time += td;

	/* Change current PID */
	pid_prev = pid_current;
	if (pid < pid_count) pid_current = pid;

	return pid_prev;
}
