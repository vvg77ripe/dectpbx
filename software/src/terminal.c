
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "terminal.h"


static struct terminal *term_list;
static struct term_cmd *cmd_list;

/********************************************************************
 *
 */

static void term_prompt(struct terminal *term)
{
	unsigned char buf[200];

	snprintf(buf, 200, "\rcli>%s", term->line);
	term_write(term, buf);
}

static void term_exec(struct terminal *term)
{
	int l;
	struct term_cmd *cmd;

	if (!term) return;

	l = strlen(term->line);
	if (!l) return;

	for (cmd = cmd_list; cmd; cmd = cmd->next) {
		if (!strcmp(cmd->command, term->line)) {
			cmd->func(term, TERM_RSN_EXEC);
		}
	}
}


/********************************************************************
 * Terminal commands
 */

static void cmd_exit(struct terminal *term, int reason)
{
	if (reason == TERM_RSN_EXEC) term->f_quit = 1;
}

/********************************************************************
 * Terminal API
 */

void term_init()
{
	cmd_list = NULL;

	term_reg_command("exit", cmd_exit);
}

void term_done()
{
	struct term_cmd *cmd;

	for (cmd = cmd_list; cmd; cmd = cmd->next) {
	}
}

struct terminal * term_create()
{
	struct terminal *term;

	/* Allocate memory for terminal structure */
	term = (struct terminal *)malloc(sizeof(struct terminal));
	if (!term) return NULL;

	/* Init structure */
	memset(term, 0, sizeof(struct terminal));
	term->file_in = -1;
	term->file_out = -1;

	term_list = term;

	return term;
}

void term_destroy(struct terminal *term)
{
	if (!term) return;

	free(term);
}

void term_start(struct terminal *term)
{
	term_prompt(term);
}

void term_char(struct terminal *term, unsigned char ch)
{
	unsigned char tmp[10];
	int l;

	if (!term) return;

	switch (ch) {
		/* Backspace */
		case 8:
			l = strlen(term->line);
			if (l > 0) {
				term_write(term, "\b \b");
				term->line[l-1] = 0;
			}
			break;

		/* New Line */
		case 10:
			term_write(term, "\n");
			term_exec(term);
			term->line[0] = 0;
			term_prompt(term);
			break;

		default:
			if (ch >= 32) {
				l = strlen(term->line);
				if (l < (TERM_MAX_LINE-2)) {
					term->line[l] = ch;
					term->line[l+1] = 0;
					tmp[0] = ch;
					tmp[1] = 0;
					term_write(term, tmp);
				}
			}
			break;
	}
}

void term_log(struct terminal *term, unsigned char *s)
{
	unsigned char tmp[10];

	if (!term) return;

	term_write(term, "\r");
	term_write(term, s);
	term_prompt(term);
}

void log_print(unsigned int level, const unsigned char *msg, ...)
{
	unsigned char buf[2048];
	va_list ap;

	va_start(ap, msg);
	vsnprintf(buf, 2048, msg, ap);
	va_end(ap);

	term_log(term_list, buf);
}

void term_write(struct terminal *term, unsigned char *s)
{
	if (term->file_out != -1)
		write(term->file_out, s, strlen(s));
}

struct term_cmd * term_reg_command(char *name,
	void (*func)(struct terminal *term, int reason)
	)
{
	struct term_cmd *cmd;

	cmd = malloc(sizeof(struct term_cmd));
	if (!cmd) return NULL;

	memset(cmd, 0, sizeof(struct term_cmd));
	cmd->command = name;
	cmd->func = func;

	cmd->next = cmd_list;
	cmd_list = cmd;

	return cmd;
}
