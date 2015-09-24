
#include <stdio.h>


int fifo_data_size(fifo_buffer *buf)
{
	if (buf->stop >= buf->start) {
		return buf->stop - buf->start;
	} else {
		return buf->length - buf->start + buf->stop;
	}
}

int fifo_cdata_size(fifo_buffer *buf)
{
	if (buf->stop >= buf->start) {
		return buf->stop - buf->start;
	} else {
		return buf->length - buf->start;
	}
}

int fifo_free_size(fifo_buffer *buf)
{
	if (buf->stop < buf->start) {
		return buf->start - buf->stop - 1;
	} else {
		return buf->length - buf->stop + buf->start - 1;
	}
}


int fifo_write(fifo_buffer *buf, char *data, int len)
{
	int i, n;

	n = buf->stop;
	for (i = 0; i < len; i++) {
		buf->buf[n] = data[i];
		if (++n == buf->length) n = 0;
		if (n != buf->start) {
			buf->stop = n;
		} else {
			break;
		}
	}

	return i;
}

int fifo_getch(fifo_buffer *buf)
{
	char ch;

	if (buf->start == buf->stop) return -1;
	ch = buf->buf[buf->start];

	if (buf->start == (buf->length - 1)) {
		buf->start = 0;
	} else {
		buf->start++;
	}

	return ch;
}
