

#include "printf_df.h"
#include <string.h>

#define DEFAULT_LEN sizeof(unsigned int)

/*
 * Why the nonsense wrapper functions? 
 * Because printf should be modified so it calls the output function directlyinstead of 
 */

static inline void _PUTC(char c)
{
	;
}

static inline void _PUT(const char* s, int l)
{
	while (l) {
		_PUTC(*s++);
		l--;
	}
}

int vprintf_df(const char *fmt, va_list args)
{
	char* s;
	int num, len;
	
	const char* fmt_head;
    while(*fmt) {
		if (*fmt != '%') {
			_PUTC(*fmt++);
			continue;
		}

		fmt_head = fmt+1;

		while (1) {
			switch (*fmt_head++) {
			case 'c':
				if (*(fmt_head-2) != '%') {
					_PUT(fmt, fmt_head-fmt);
				}
				_PUTC((unsigned char)va_arg(args, int));
				break;
			case 's':
				s = va_arg(args, char *);
				if (*(fmt_head-2) != '%') {
					_PUT(fmt, fmt_head-fmt);
					do {_PUTC(*s);} while (*s++); // copy until '\0' inclusive
				}
				else {
					while (*s) {_PUTC(*s++);} // copy until '\0' non-inclusive
				}
				break;
			case 'e':
			case 'E':
			case 'f':
			case 'F':
			case 'g':
			case 'G':
				_PUT(fmt, fmt_head-fmt);
				float fnum = (float)va_arg(args, double);
				_PUT((char*)&fnum, sizeof(float));
				break;
			case 'd':
			case 'i':
			case 'o':
			case 'x':
			case 'X':
			case 'u':
				len = 4;
				num = va_arg(args, int);
				if (*(fmt_head-2) == 'h') {
					len = 2;
					if (*(fmt_head-3) == 'h') {
						len = 1;
					} 
				}
				_PUT(fmt, fmt_head-fmt-1);
				if (0 <= num && num <= 255) {
					// _PUTC(&(*(fmt_head-1) + 128));
					len = 1;
				}
				else {
					_PUTC(*(fmt_head-1));
				}
				_PUT((char*)&num, len);
				break;
			case '%':
				_PUT(fmt, fmt_head-fmt);
				break;
			case '\0':
				_PUTC('\0');
				fmt_head--;
				break;
			case '*':
				_PUT(fmt, fmt_head-fmt);
				_PUTC((unsigned char)va_arg(args, int));
				fmt = fmt_head;
			default:
				continue;
			}

			fmt = fmt_head;
			break;
		}
	}
}

void printf_df(const char* fmt, ...)
{
	va_list args;
    va_start(args, fmt);
    vprintf_df(fmt, args);
    va_end(args);
}
