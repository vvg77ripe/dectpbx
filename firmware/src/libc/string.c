
#include <stdlib.h>
#include <string.h>


int strcmp(const char *s1, const char *s2)
{
	do {
		if (s1[0] < s2[0]) return -1;
		if (s1[0] > s2[0]) return 1;
		if (!s1[0]) break;

		s1++;
		s2++;
	} while (1);

	return 0;
}

int strlen (const char *str)
{
	char *s = (char *)str;
	int len = 0;

	if (s == NULL) return 0;

	while (*s++ != 0) ++len;

	return len;
}

void *memset(void *s, int c, size_t n)
{
	/* Not optimized, but very portable */
	unsigned char *sp = (unsigned char *)s;

	if ((s != NULL) && (n > 0))
	{
		while (n--)
		{
			*sp++ = (unsigned char)c;
		}
	}
	return s;
}

void *memcpy(void *d, void *s, size_t n)
{
	unsigned char *sp = (unsigned char *)s;
	unsigned char *dp = (unsigned char *)d;

	while (n--) {
		*dp++ = *sp++;
	}
}

int memcmp(const void *S1, const void *S2, size_t N)
{
	unsigned char *s1 = (unsigned char *)S1;
	unsigned char *s2 = (unsigned char *)S2;

	while (N--) {
		if (*s1 < *s2) return -1;
		if (*s1++ > *s2++) return 1;
	}
	return 0;
}
