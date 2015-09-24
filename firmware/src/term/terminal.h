
#ifndef _TERM_TERMINAL_H
#define _TERM_TERMINAL_H

#include <stdio.h>
#include <stdarg.h>

#define MAX_TERMINALS	2

#define MAX_TERM_LINE	80
#define MAX_TERM_WORD	30
#define MAX_TERM_CMDS	32

#define TERM_TYPE_ANSI	1

#define TERM_RSN_EXEC	1
#define TERM_RSN_HINT	2

#define TERM_FLAG_ZERO	1	/* 0 control char received */
#define TERM_FLAG_PASS	2	/* Terminal waiting for password */


struct terminal {
	unsigned char	type;
	char			line[MAX_TERM_LINE];
	unsigned char	line_pos;
	unsigned char	flags;
	fifo_buffer *	in;
	fifo_buffer *	out;
};

typedef void (*cmd_proc)(struct terminal *term, int reason);

struct term_command {
	char *	name;
	char *	descr;
	struct term_command * tree;
	struct term_command * next;
	cmd_proc	proc;
};


void term_init(void);
void term_process(void);

struct terminal *term_create(struct terminal *term);
void term_destroy(struct terminal *term);
void term_char(struct terminal *term, char ch);

struct term_command *term_reg_command(struct term_command *owner, char *name, char *descr, cmd_proc proc);
int term_find(struct term_command **res, char *line, int *pos);

void term_help_line(struct terminal *term, char *cmd, char *help);
void term_vlog(struct terminal *term, char *str, va_list ap);
void term_log_all(char *str, ...);

int term_get_int(struct terminal *term, int base);
unsigned int term_get_ip(struct terminal *term);


#endif
