
#ifndef _CFGFILE_H
#define _CFGFILE_H

typedef struct cfg_line cfg_line_t;

struct cfg_line {
	cfg_line_t *	next;
	char *			pname;
	char *			pvalue;
};


void cfg_init();
void cfg_done();
int cfg_load(char *file);
char *cfg_find(char *pname);

#endif
