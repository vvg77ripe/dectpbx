
#include <stdio.h>
#include <string.h>


struct romfs_file {
	unsigned char	type;
	unsigned char	res;
	unsigned short	size;
	char			name[16];
} __attribute__((__packed__));

static FILE *fs;


static void romfs_append_file(char *name)
{
	struct romfs_file frec;
	FILE *f;
	unsigned int l;
	unsigned char buf[1024];

	/* Open file */
	f = fopen(name, "r");
	if (!f) return;

	/* Fill file header */
	fseek(f, 0, SEEK_END);
	memset(&frec, 0, sizeof(frec));
	frec.type = 'F';
	frec.size = htons(ftell(f));
	fseek(f, 0, SEEK_SET);
	strncpy(frec.name, name, 16);

	/* Write header */
	fwrite(&frec, 1, sizeof(frec), fs);

	/* Write file */
	while (!feof(f)) {
		l = fread(buf, 1, 1024, f);
		fwrite(buf, 1, l, fs);
	}

	/* Close file */
	fclose(f);
}

static void romfs_append_eof()
{
	struct romfs_file frec;

	memset(&frec, 0, sizeof(frec));
	frec.type = 'Z';
	fwrite(&frec, 1, sizeof(frec), fs);
}

int main()
{
	FILE *list;
	char line[100];

	fs = fopen("romfs.bin", "w+");
	if (!fs) {
		printf("FATAL: Cannot create romfs output file.\n");
		return 1;
	}

	list = fopen("filelist", "r");
	if (list) {
		while (!feof(list)) {
			line[0] = 0;
			fgets(line, 100, list);
			strtok(line, "\n\r");
			if (strlen(line)) {
				printf("Appending file '%s'\n", line);
				romfs_append_file(line);
			}
		}
		fclose(list);
	}

	romfs_append_eof();
	fclose(fs);

	return 0;
}
