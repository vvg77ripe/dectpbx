
#ifndef _STRING_H
#define _STRING_H

typedef unsigned int size_t;

int strcmp(const char *s1, const char *s2);
int strlen (const char *str);

void *memset(void *s, int c, size_t n);
void *memcpy(void *d, void *s, size_t n);
int memcmp(const void *S1, const void *S2, size_t N);

#endif
