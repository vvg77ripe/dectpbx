
#ifndef _TERMNINAL_H
#define _TERMNINAL_H

#define TERM_MAX_LINE	80

#define TERM_RSN_EXEC	1


struct terminal {
	struct terminal *	next;
	int					file_in;
	int					file_out;
	unsigned char		f_quit;
	unsigned char		line[TERM_MAX_LINE];
	int					line_pos;
};

struct term_cmd {
	struct term_cmd *	next;
	char *				command;
	void (*func)(struct terminal *term, int reason);
};

void term_init(void);
void term_done(void);
struct terminal * term_create(void);
void term_destroy(struct terminal *term);

void term_start(struct terminal *term);
void term_char(struct terminal *term, unsigned char ch);

void term_log(struct terminal *term, unsigned char *s);
void log_print(unsigned int level, const unsigned char *msg, ...);
void term_write(struct terminal *term, unsigned char *s);

struct term_cmd * term_reg_command(char *name,
	void (*func)(struct terminal *term, int reason));

#endif
