
#ifndef _STDIO_H
#define _STDIO_H

#include <stdarg.h>

typedef struct {
	char *	buf;
	int		length;
	int		start;
	int		stop;
} fifo_buffer;


int sprintf(char *str, const char *format, ...);
int bprintf(fifo_buffer *out, const char *format, ...);

int vbprintf(fifo_buffer *out, const char *format, va_list ap);

int fifo_data_size(fifo_buffer *buf);
int fifo_cdata_size(fifo_buffer *buf);
int fifo_free_size(fifo_buffer *buf);

int fifo_getch(fifo_buffer *buf);
int fifo_write(fifo_buffer *buf, char *data, int len);

#endif
