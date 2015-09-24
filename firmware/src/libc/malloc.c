
#include <mcf5282.h>
#include <stdlib.h>


extern char __SP_INIT[];
static void *mp_begin = __SP_INIT;
static void *mp_next;


void mem_init()
{
	mp_next = mp_begin + 2;
}

void mem_getinfo(unsigned int *mstatic, unsigned int *mdynamic, unsigned int *mfree)
{
	unsigned int ms, md, mf, mt;

	mt = 65536;
	ms = (unsigned int)mp_begin & 0xFFFF;
	md = (unsigned int)(mp_next - mp_begin) & 0xFFFF;
	mf = mt - ms - md;

	if (mstatic) *mstatic = ms;
	if (mdynamic) *mdynamic = md;
	if (mfree) *mfree = mf;
}

void *malloc(unsigned int size)
{
	void *res;

	res = mp_next;
	mp_next += size;
	return res;
}
