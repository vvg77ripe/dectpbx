
#include <mcf5282.h>
#include "config.h"

#include "romfs.h"


extern unsigned char __ROMFS_START[];
static struct romfs_file rfile;


struct romfs_file * romfs_find_file(unsigned char *name)
{
	struct romfs_record *rec;

	/* Check if filesystem is present */
	rec = (struct romfs_record *)__ROMFS_START;
	if (rec->type != 'F') return NULL;

	while (rec->type == 'F') {
		/* Compare file names */
		if (!strcmp(rec->name, name)) {
			memset(&rfile, 0, sizeof(rfile));
			rfile.data = (unsigned char *)((uint8 *)rec + sizeof(struct romfs_record));
			rfile.size = rec->size;
			rfile.name = rec->name;
			return &rfile;
		}

		/* Move to next record */
		rec += rec->size + sizeof(struct romfs_record);
	}

	return NULL;
}
