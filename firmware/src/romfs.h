
#ifndef _ROMFS_H
#define _ROMFS_H


struct romfs_file {
	unsigned char *	data;
	unsigned int	size;
	unsigned char *	name;
};

struct romfs_record {
	unsigned char	type;
	unsigned char	res;
	unsigned short	size;
	char			name[16];
} PACKED;


struct romfs_file * romfs_find_file(unsigned char *name);

#endif
