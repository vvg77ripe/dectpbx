
#include <stdio.h>

#include "cfgfile.h"

static cfg_line_t *config;


static void cfg_line(char *pname, char *pvalue)
{
	int ls;
	cfg_line_t *line, *cfg;

	/* Allocate memory */
	ls = sizeof(cfg_line_t) + strlen(pname) + strlen(pvalue) + 2;
	line = malloc(ls);
	if (!line) return;

	memset(line, 0, ls);

	line->pname = (char *)line + sizeof(cfg_line_t);
	line->pvalue = line->pname + strlen(pname) + 1;

	strcpy(line->pname, pname);
	strcpy(line->pvalue, pvalue);

	/* Add to chain */
	for (cfg = config; cfg; cfg = cfg->next) {
		if (cfg->next == NULL) {
			cfg->next = line;
			return;
		}
	}

	config = line;
}


void cfg_init()
{
	config = NULL;
}

void cfg_done()
{
	cfg_line_t *line, *l;

	line = config;
	while (line) {
		l = line;
		line = line->next;
		free(l);
	}

	config = NULL;
}

int cfg_load(char *file)
{
	FILE *cfg;
	int i, l, x;
	char line[200];
	char *p_name, *p_value;

	cfg = fopen(file, "r");
	if (!cfg) return -1;

	while (!feof(cfg)) {
		/* Read line from config file */
		line[0] = 0;
		fgets(line, 200, cfg);

		/* Skip comments */
		if (line[0] == '#') continue;

		/* Parse line */
		p_name = &line[0];
		p_value = NULL;
		x = 0;
		l = strlen(line);
		for (i = 0; i < l; i++) {
			switch (x) {
				case 0:
					if (line[i] == '=') {
						line[i] = 0;
						x = 1;
					}
					if (line[i] == ' ') {
						line[i] = 0;
					}
					break;

				case 1:
					if (line[i] != ' ') {
						x = 2;
						p_value = &line[i];
					}
					break;

				case 2:
					if ((line[i] == 13) || (line[i] == 10)) {
						line[i] = 0;
					}
					break;
			}
		} /* for (...) */

		/* check parameter */
		if (p_value != NULL) {
			cfg_line(p_name, p_value);
		}
	}

	fclose(cfg);
	return 0;
}

char *cfg_find(char *pname)
{
	cfg_line_t *line;

	for (line = config; line; line = line->next) {
		if (!strcmp(line->pname, pname)) return line->pvalue;
	}

	return NULL;
}
