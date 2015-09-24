
#include "g711.h"

#define AMI_MASK	0x55


short			table_a2lin[256];
unsigned char	table_lin2a[8192];


static inline unsigned char linear2alaw(short int linear)
{
    int mask;
    int seg;
    int pcm_val;
    static int seg_end[8] =
    {
         0xFF, 0x1FF, 0x3FF, 0x7FF, 0xFFF, 0x1FFF, 0x3FFF, 0x7FFF
    };
    
    pcm_val = linear;
    if (pcm_val >= 0)
    {
        /* Sign (7th) bit = 1 */
        mask = AMI_MASK | 0x80;
    }
    else
    {
        /* Sign bit = 0 */
        mask = AMI_MASK;
        pcm_val = -pcm_val;
    }

    /* Convert the scaled magnitude to segment number. */
    for (seg = 0;  seg < 8;  seg++)
    {
        if (pcm_val <= seg_end[seg])
	    break;
    }
    /* Combine the sign, segment, and quantization bits. */
    return  ((seg << 4) | ((pcm_val >> ((seg)  ?  (seg + 3)  :  4)) & 0x0F)) ^ mask;
}

static inline short int alaw2linear(unsigned char alaw)
{
	int i;
	int seg;

	alaw ^= AMI_MASK;
	i = ((alaw & 0x0F) << 4);
	seg = (((int) alaw & 0x70) >> 4);
	if (seg)
		i = (i + 0x100) << (seg - 1);
	return (short int) ((alaw & 0x80)  ?  i  :  -i);
}

void g711_init()
{
	int i;

	for (i = 0; i < 256; i++) {
		table_a2lin[i] = alaw2linear(i);
	}

	for (i = 0; i < 8192; i++) {
		table_lin2a[i] = linear2alaw(i << 3);
	}
}
