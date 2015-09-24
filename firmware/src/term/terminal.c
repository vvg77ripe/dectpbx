
#include <mcf5282.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "config.h"
#include "eeprom.h"
#include "flash.h"
#include "timer.h"
#include "fec.h"
#include "network/tftp.h"
#include "terminal.h"
#include "module.h"

static struct terminal *term_list[MAX_TERMINALS];

static struct term_command *cmd_list;

static TIMER tt_flash;
static tftp_client tftp;


static void term_prompt(struct terminal *term)
{
	if (term->flags & TERM_FLAG_PASS) {
		bprintf(term->out, "Password:");
	} else {
		bprintf(term->out, "ema#%s", term->line);
	}
}

static void term_print_help(struct terminal *term, struct term_command *root)
{
	struct term_command *cmd;

	if (!root) {
		cmd = cmd_list;
	} else {
		if (root->proc) root->proc(term, TERM_RSN_HINT);
		cmd = root->tree;
	}
	while (cmd) {
		term_help_line(term, cmd->name, cmd->descr);
		cmd = cmd->next;
	}
}

static void term_command(struct terminal *term)
{
	struct term_command *cmd;
	int res, pos;

	/* Check password */
	if (term->flags & TERM_FLAG_PASS) {
		switch (eeprom.pass_type) {
			case CONFIG_PASS_TEXT:
				if (strcmp(term->line, eeprom.pass_data)) {
					bprintf(term->out, "Bad password.\r\n\r\n");
					return;
				}
				break;
		}
		/* Enter normal mode */
		term->flags &= ~TERM_FLAG_PASS;
		return;
	}

	/* Ignore empty line */
	if (!term->line[0]) return;

	res = term_find(&cmd, term->line, &pos);
	term->line_pos = pos;

	if (!res || cmd) {
		if (cmd->proc) {
			cmd->proc(term, TERM_RSN_EXEC);
		} else {
			bprintf(term->out, "%% Incomplete command.\r\n");
		}
	} else {
		if (cmd) {
			term_print_help(term, cmd);
		} else {
			bprintf(term->out, "%% Command not found, use ? to list commands.\r\n");
		}
	}
}

static void term_help(struct terminal *term)
{
	struct term_command *cmd;

	term_find(&cmd, term->line, NULL);

	term_print_help(term, cmd);
}

/* ========== System Level Commands ==========
 *
 */
static void cb_tftp_recv(int code, uint8 *data, int len)
{
	uint32 f_addr;
	uint32 *f_data;
	int i;

	if (code > 0) {
		if (code == 1) {
			term_log_all("Programming FLASH. Please wait...\r\n");
			flash_init();
			flash_erase_block(1);
		}

		f_addr = 0x00040000 + code * 512 - 512;
		f_data = (uint32 *)data;
		for (i = 0; i < ((len + 3) >> 2); i++) {
			flash_write(f_addr + i*4, f_data[i]);
		}

		if (len < 512) {
			term_log_all("Programming done, the system will now restart.\r\n");
			/* Start reset timer */
			tt_flash.value = 1000;
			tt_flash.flags = TMR_ACTIVE;
			tmr_add(&tt_flash);
		}
	}
}

static void cmd_system_update(struct terminal *term, int reason)
{
	if (reason == TERM_RSN_EXEC) {
		/* Execute */
		bprintf(term->out, "Sending TFTP request...\r\n");
		memset(&tftp, 0, sizeof(tftp));
		tftp.cbfunc = cb_tftp_recv;
		tftp_start(&tftp, "fwrom.bin");
	}
}

static void cmd_system_restart(struct terminal *term, int reason)
{
	if (reason == TERM_RSN_EXEC) {
		/* Software reset */
		MCF5282_RESET_RCR = MCF5282_RESET_RCR_SOFTRST;
	}
}

static void cmd_system_save(struct terminal *term, int reason)
{
	if (reason == TERM_RSN_EXEC) {
		if (eeprom_write(0, 0, (uint8 *)&eeprom, sizeof(eeprom)) > 0) {
			mod_save();
			bprintf(term->out, "Configuration saved.\r\n");
		} else {
			bprintf(term->out, "Failed to write EEPROM.\r\n");
		}
	}
}

static void cmd_system_mac(struct terminal *term, int reason)
{
	uint8 mac[6];

	if (reason == TERM_RSN_EXEC) {
		/* Get MAC address */
		mac[0] = term_get_int(term, 16);
		if (term->line[term->line_pos] != ':') {
			bprintf(term->out, "Cant read 2 byte\r\n");
			return;
		}
		term->line_pos++;
		mac[1] = term_get_int(term, 16);
		if (term->line[term->line_pos] != ':') {
			bprintf(term->out, "Cant read 3 byte\r\n");
			return;
		}
		term->line_pos++;
		mac[2] = term_get_int(term, 16);
		if (term->line[term->line_pos] != ':') {
			bprintf(term->out, "Cant read 4 byte\r\n");
			return;
		}
		term->line_pos++;
		mac[3] = term_get_int(term, 16);
		if (term->line[term->line_pos] != ':') {
			bprintf(term->out, "Cant read 5 byte\r\n");
			return;
		}
		term->line_pos++;
		mac[4] = term_get_int(term, 16);
		if (term->line[term->line_pos] != ':') {
			bprintf(term->out, "Cant read 6 byte\r\n");
			return;
		}
		term->line_pos++;
		mac[5] = term_get_int(term, 16);

		/* Modify and save configuration */
		eeprom.fec_mac[0] = mac[0];
		eeprom.fec_mac[1] = mac[1];
		eeprom.fec_mac[2] = mac[2];
		eeprom.fec_mac[3] = mac[3];
		eeprom.fec_mac[4] = mac[4];
		eeprom.fec_mac[5] = mac[5];
		cmd_system_save(term, reason);

		/* Restart system */
		cmd_system_restart(term, reason);
	}
}

static void cmd_system_passwd(struct terminal *term, int reason)
{
	char *pass;

	if (reason == TERM_RSN_EXEC) {
		pass = &term->line[term->line_pos];
		if (strlen(pass) > 15) {
			bprintf(term->out, "Maximum password length is 15 characters.\r\n");
			return;
		}
		if (pass[0]) {
			memcpy(&eeprom.pass_data, pass, 16);
			eeprom.pass_type = CONFIG_PASS_TEXT;
		} else {
			eeprom.pass_type = CONFIG_PASS_NONE;
		}
	}
}

static void cmd_show_system(struct terminal *term, int reason)
{
	unsigned int mstatic, mdynamic, mfree;

	if (reason == TERM_RSN_EXEC) {
		/* network information */
		bprintf(term->out, "Ethernet address is %X:%X:%X:%X:%X:%X, Link is %s\r\n",
			eeprom.fec_mac[0], eeprom.fec_mac[1], eeprom.fec_mac[2],
			eeprom.fec_mac[3], eeprom.fec_mac[4], eeprom.fec_mac[5],
			fec_link());
		bprintf(term->out, "IP address is %i.%i.%i.%i/%i, router %i.%i.%i.%i\r\n",
			(eeprom.ip_addr >> 24) & 0xFF, (eeprom.ip_addr >> 16) & 0xFF,
			(eeprom.ip_addr >> 8) & 0xFF, (eeprom.ip_addr) & 0xFF,
			eeprom.ip_mask,
			(eeprom.ip_router >> 24) & 0xFF, (eeprom.ip_router >> 16) & 0xFF,
			(eeprom.ip_router >> 8) & 0xFF, (eeprom.ip_router) & 0xFF);
		/* memory information */
		mem_getinfo(&mstatic, &mdynamic, &mfree);
		bprintf(term->out, "Memory usage: %i bytes static, %i bytes dynamic, %i bytes free.\r\n",
			mstatic, mdynamic, mfree);
	}
}

/*
 *
 */
void term_init()
{
	int i;
	struct term_command *cmd_show, *cmd_sys;

	for (i = 0; i < MAX_TERMINALS; i++)
		term_list[i] = NULL;

	cmd_list = NULL;

	/* Timers */
	tt_flash.flags = 0;

	/* Register commands */
	cmd_show = term_reg_command(NULL, "show", "Show running system information", NULL);
	cmd_sys = term_reg_command(NULL, "system", "System level commands", NULL);

	term_reg_command(cmd_show, "system", "Show system status", cmd_show_system);

	term_reg_command(cmd_sys, "update", "Update firmware from TFTP server", cmd_system_update);
	term_reg_command(cmd_sys, "restart", "Restart system", cmd_system_restart);
	term_reg_command(cmd_sys, "save", "Save system configuration", cmd_system_save);
	term_reg_command(cmd_sys, "mac", "Change system MAC address", cmd_system_mac);
	term_reg_command(cmd_sys, "passwd", "Change system password", cmd_system_passwd);
}

/*
 *
 */
void term_process()
{
	int i, ch;
	struct terminal *term;

	for (i = 0; i < MAX_TERMINALS; i++) {
		if (term = term_list[i]) while (1) {
				ch = fifo_getch(term->in);
				if (ch < 0) break;

				term_char(term, ch);
		}
	}

	if (tt_flash.flags & TMR_EVENT) {
		tt_flash.flags = 0;
		fec_blink(1);
		flash_copy();
	}
}

/*
 *
 */
struct terminal * term_create(struct terminal *term)
{
	if (!term) return NULL;

	term->type = TERM_TYPE_ANSI;
	term->line[0] = 0;

	term->flags = 0;
	if (eeprom.pass_type != CONFIG_PASS_NONE) term->flags = TERM_FLAG_PASS;

	bprintf(term->out, "Ethernet Multimedia Adaptor Console\r\n");
	bprintf(term->out, "Software version %s; http://vvg.pp.ru.\r\n", FIRMWARE_VERSION);
	bprintf(term->out, "\r\n");
	term_prompt(term);

	/* FIXX */
	term_list[0] = term;

	return term;
}

/*
 *
 */
void term_destroy(struct terminal *term)
{
	term_list[0] = NULL;
}

/*
 *
 */
void term_char(struct terminal *term, char ch)
{
	int l, q;

	if (!term) return;

	if (term->flags & TERM_FLAG_ZERO) {
		/* Control char */
		term->flags &= ~TERM_FLAG_ZERO;
		return;
	}

	/* Quiet mode */
	q = term->flags & TERM_FLAG_PASS;

	switch (ch) {
		case 0:
			term->flags |= TERM_FLAG_ZERO;
			break;
		/* backspace */
		case 8:
			l = strlen(term->line);
			if (l > 0) {
				term->line[l-1] = 0;
				if (!q) bprintf(term->out, "\b \b");
			}
			break;
		/* LF */
		case 10:
			break;
		/* CR */
		case 13:
			bprintf(term->out, "\r\n");
			term_command(term);
			term->line[0] = 0;
			term_prompt(term);
			break;
		/* ESC */
		case 27:
			break;
		case '?':
			if (!q) {
				bprintf(term->out, "\r\n");
				term_help(term);
				term_prompt(term);
			}
			break;
		/* Skip TELNET IAC */
		case 255:
			break;
		default:
			if (ch >= 32) {
				l = strlen(term->line);
				if (l < (MAX_TERM_LINE-1)) {
					term->line[l] = ch;
					term->line[l+1] = 0;
					if (!q) bprintf(term->out, "%c", ch);
				}
			}
			break;
	}
}

/*
 *
 */
struct term_command *term_reg_command(struct term_command *owner, char *name, char *descr, cmd_proc proc)
{
	int i;
	struct term_command *cmd, **ins;

	/* Allocate memory for command structure  */
	cmd = malloc(sizeof(struct term_command));
	memset(cmd, 0, sizeof(struct term_command));

	if (cmd) {
		/* Fill command structure */
		cmd->name = name;
		cmd->descr = descr;
		cmd->proc = proc;

		/* Select appropriate chain */
		if (owner) {
			ins = &owner->tree;
		} else {
			ins = &cmd_list;
		}

		/* Insert into chain */
		do {
			if (*ins) {
				/* maintain alphabetical order */
				if (strcmp((*ins)->name, cmd->name) > 0) {
					cmd->next = *ins;
					*ins = cmd;
					break;
				}
			} else {
				/* end of chain - insert into end */
				*ins = cmd;
				break;
			}

			ins = &(*ins)->next;
		} while (1);
	}

	return cmd;
}

/*
 *
 */
int term_find(struct term_command **res, char *line, int *pos)
{
	char cmd_word[MAX_TERM_WORD];
	struct term_command *cmd;
	char c;
	int l, ll;

	if (!res) return 1;
	*res = NULL;
	if (pos) *pos = 0;

	cmd_word[0] = 0;
	cmd = cmd_list;
	ll = strlen(line) + 1;
	while (ll--) {
		c = *line++;
		if (pos) *pos = *pos + 1;
		/* Copy next command word to tmp buffer */
		if ((c != 0) && (c != ' ')) {
			l = strlen(cmd_word);
			if (l < (MAX_TERM_WORD-1)) {
				cmd_word[l] = c;
				cmd_word[l+1] = 0;
			}
			continue;
		}

		if (!c) *pos = *pos - 1;
		if (!cmd_word[0]) continue;

		/* Find word in the command tree */
		while (cmd) {
			if (!strcmp(cmd->name, cmd_word)) {
				if (cmd->tree) {
					/* Command has subtree - go to next word */
					*res = cmd;
					cmd = cmd->tree;
					cmd_word[0] = 0;
					break;
				} else {
					/* Found! */
					*res = cmd;
					return 0;
				}
			}
			cmd = cmd->next;
		}

		if (!cmd) return 2;
	}

	/* Not found or has subtree */
	return 2;
}

void term_vlog(struct terminal *term, char *str, va_list ap)
{
	if ( !(term->flags & TERM_FLAG_PASS) ) {
		bprintf(term->out, "\r");
		vbprintf(term->out, str, ap);
		term_prompt(term);
	}
}

void term_log_all(char *str, ...)
{
	va_list ap;
	int i;

	va_start(ap, str);
	for (i = 0; i < MAX_TERMINALS; i++) {
		if (term_list[i]) term_vlog(term_list[i], str, ap);
	}
	va_end(ap);
}

void term_help_line(struct terminal *term, char *cmd, char *help)
{
	if (strlen(cmd) > 4) {
		bprintf(term->out, "   %s\t%s\r\n", cmd, help);
	} else {
		bprintf(term->out, "   %s\t\t%s\r\n", cmd, help);
	}
}

int term_get_int(struct terminal *term, int base)
{
	char c;
	int n, x;

	x = 0;
	/* Skip leading spaces */
	while (c = term->line[term->line_pos]) {
		if (c == ' ') {
			term->line_pos++;
			continue;
		}
		break;
	}

	/* Parse number */
	while (c = term->line[term->line_pos]) {
		n = -1;
		if ((c >= '0') && (c <= '9')) n = c - '0';
		if ((c >= 'A') && (c <= 'Z')) n = c - 'A' + 10;
		if ((c >= 'a') && (c <= 'z')) n = c - 'a' + 10;
		if ((n < 0) || (n >= base)) break;
		x = x * base + n;

		term->line_pos++;
	}

	return x;
}

unsigned int term_get_ip(struct terminal *term)
{
	unsigned int ip, x;

	/* 1 */
	ip = term_get_int(term, 10);
	if ((ip == 0) || (ip > 255)) return 0;
	if (term->line[term->line_pos] != '.') return 0;
	term->line_pos++;
	/* 2 */
	x = term_get_int(term, 10);
	if (x > 255) return 0;
	if (term->line[term->line_pos] != '.') return 0;
	term->line_pos++;
	ip = (ip << 8) + x;
	/* 3 */
	x = term_get_int(term, 10);
	if (x > 255) return 0;
	if (term->line[term->line_pos] != '.') return 0;
	term->line_pos++;
	ip = (ip << 8) + x;
	/* 4 */
	x = term_get_int(term, 10);
	if (x > 255) return 0;
	ip = (ip << 8) + x;
	return ip;
}
