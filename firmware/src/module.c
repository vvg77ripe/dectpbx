
#include <mcf5282.h>

#include "eeprom.h"
#include "module.h"
#include "term/terminal.h"

#include "mod-dect/dect.h"
#include "mod-lsic/lsic.h"


static struct module_config modcfg;
static struct module_func *	modfunc;


static void cmd_module_id(struct terminal *term, int reason)
{
	int mod_type;

	if (reason == TERM_RSN_EXEC) {
		if (modcfg.type != 0) {
			bprintf(term->out, "Cannot overwrite module type.\r\n");
			return;
		}

		/* Get module type */
		mod_type = term_get_int(term, 10);
		if (mod_type <= 0) {
			bprintf(term->out, "Please specify module type.\r\n");
			return;
		}

		/* Initialize module structure */
		memset(&modcfg, 0, sizeof(modcfg));
		modcfg.sign = 0x52;
		modcfg.type = mod_type;

		/* Set module description */
		switch (modcfg.type) {
			/* DECT */
			case MODULE_TYPE_DECT:
				sprintf(modcfg.name, "DECT Radio Fixed Part");
				break;
			/* LSIC */
			case MODULE_TYPE_LSIC:
				sprintf(modcfg.name, "Low Speed Interface Card");
				break;
		}

		/* Write structure to module */
		eeprom_write(1, 0, (uint8 *)&modcfg, sizeof(modcfg));

		/* Reset module type */
		modcfg.type = 0;
	}
}

static void cmd_show_module(struct terminal *term, int reason)
{
	if (reason == TERM_RSN_EXEC) {
		bprintf(term->out, "No  ID  Rev Description\r\n");
		bprintf(term->out, "==================================================\r\n");

		if (modcfg.type == 0) {
			bprintf(term->out, "01  --  --  Empty slot\r\n");
		} else {
			bprintf(term->out, "01  %X  %X  %s\r\n", modcfg.type, modcfg.rev, modcfg.name);
		}
	}
}

void mod_init()
{
	struct term_command *cmd_module, *cmd_show;

	/* Initialize module structure */
	memset(&modcfg, 0, sizeof(modcfg));

	/* Register terminal commands */
	term_find(&cmd_show, "show", NULL);
	term_reg_command(cmd_show, "module", "Show module information", cmd_show_module);

	cmd_module = term_reg_command(NULL, "module", "Expansion module commands", NULL);
	term_reg_command(cmd_module, "id", "Set module ID", cmd_module_id);


	/* Read module information */
	eeprom_read(1, 0, (uint8 *)&modcfg, sizeof(modcfg));

	/* Check signature */
	if ( (modcfg.zero != 0) || (modcfg.sign != 0x52) ) {
		memset(&modcfg, 0, sizeof(modcfg));
		return;
	}

	/* Initialize module */
	modfunc = NULL;
	switch (modcfg.type) {
		/* DECT */
		case MODULE_TYPE_DECT:
			mod_dect_init();
			break;
		/* LSIC */
		case MODULE_TYPE_LSIC:
			mod_lsic_init();
			break;
	}
}

void mod_set_callbacks(struct module_func *func)
{
	modfunc = func;
}

void mod_process()
{
	if (!modfunc) return;
	if (!modfunc->mod_process) return;
	modfunc->mod_process();
}

int mod_save()
{
	if (!modfunc) return 0;
	if (!modfunc->mod_save) return 0;
	return modfunc->mod_save();
}
