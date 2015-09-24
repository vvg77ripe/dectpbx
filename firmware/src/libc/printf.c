
#include <stdio.h>
#include <stdarg.h>


static int out_char(fifo_buffer *out, char ch)
{
	int i;

	i = out->stop;
	out->buf[i] = ch;
	if (++i == out->length) i = 0;
	if (i != out->start) out->stop = i;
	return 0;
}

static void out_num(fifo_buffer *out, int num, int rad, int size, char fill_char)
{
	char tmp[20];
	int n, i;
	char c;

	n = num;
	for (i = 0; i < 20; i++) {
		tmp[i] = n % rad;
		n = n / rad;
		if (!n) break;
	}

	for (n = i; n < size-1; n++) {
		out_char(out, fill_char);
	}

	for (n = i; n >= 0; n--) {
		c = tmp[n] + '0';
		if (tmp[n] > 9) c = tmp[n] + 'A' - 10;
		out_char(out, c);
	}
}

/*
 *
 */
int vbprintf(fifo_buffer *out, const char *format, va_list ap)
{
	char *p, *sval;
	int nval, maxlen;
	char c, c_fill;

	/*
	 * Start parsing apart the format string and display appropriate
	 * formats and data.
	 */
	for (p = (char *)format; (c = *p) != 0; p++)
	{
		if (c != '%') {
			out_char(out, c);
			continue;
		}

		c_fill = ' ';
		maxlen = 0;

		/* Check for fill modificator */
		if (*(p+1) == '0') c_fill = '0';

		/* Check for size modificators */
		while (c = *++p) {
			if (c < '0') break;
			if (c > '9') break;

			maxlen = maxlen * 10 + (c - '0');
		}
		p--;

		/*
		 * Now we're ready to examine the format.
		 */
		switch (c = *++p)
		{
			case 'i':
				nval = (int)va_arg(ap, int);
				out_num(out, nval, 10, maxlen, c_fill);
				break;

			case 'X':
				nval = (int)va_arg(ap, int);
				out_num(out, nval, 16, 2, '0');
				break;

			case 's':
				sval = (char *)va_arg(ap, char *);
				if (sval) {
					while (c = *sval++) out_char(out, c);
				}
				break;

			case 'c':
				c = (char)va_arg(ap, int);
				out_char(out, c);
				break;

			default:
				out_char(out, c);
				break;
		}
	}
	return 0;
}

/*
 *
 */
int bprintf(fifo_buffer *out, const char *format, ...)
{
	va_list ap;
	int r;

	va_start(ap, format);
	r = vbprintf(out, format, ap);
	va_end(ap);

	return r;
}
/*
 *
 */
int sprintf(char *str, const char *format, ...)
{
	fifo_buffer out;
	va_list ap;
	int r;

	out.buf = str;
	out.length = 0;
	out.start = 0;
	out.stop = 0;

	va_start(ap, format);
	r = vbprintf(&out, format, ap);
	va_end(ap);
	out_char(&out, 0);

	return r;
}
