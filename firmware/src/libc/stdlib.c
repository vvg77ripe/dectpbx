
#include <stdlib.h>


int atoi(const char *nptr)
{
	unsigned char base;
	int res;

	base = 10;
	res = 0;
	while (*nptr) {
		if ((nptr[0] >= '0') && (nptr[0] <= '9')) {
			res = res * base + (nptr[0] - '0');
			nptr++;
			continue;
		}
		break;
	}
	return res;
}
