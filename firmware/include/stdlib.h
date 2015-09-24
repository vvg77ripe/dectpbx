
#ifndef _STDLIB_H
#define _STDLIB_H

#ifndef	NULL
#define NULL	0
#endif

/* stdlib.c */
int atoi(const char *nptr);

/* malloc.c */
void mem_init(void);
void mem_getinfo(unsigned int *mstatic, unsigned int *mdynamic, unsigned int *mfree);
void *malloc(unsigned int size);

#endif
