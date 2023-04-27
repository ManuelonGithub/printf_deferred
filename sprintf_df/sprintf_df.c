
#include <string.h>
#include "sprintf_df.h"

#define DEFAULT_LEN sizeof(unsigned int)

#define skip_copy(a,b) (*a++ = *b++)
#define skip_ncopy(a, b, n) (a = (char*)memcpy(a, b, (n)) + (n))

int vsprintf_df(char* buf, const char *fmt, va_list args)
{
	char* s;
	int num, len;

	const char* fmt_head;
	char* str = buf;

    while(*fmt) {
		if (*fmt != '%') {
			skip_copy(str, fmt);
			continue;
		}

		fmt_head = fmt+1;

		while (1) {
			switch (*fmt_head++) {
			case 'c':
				// data-saving trick - if just %c don't bother with the '%c' bit
				if (*(fmt_head-2) != '%') {
					skip_ncopy(str, fmt, fmt_head-fmt);
				}
				*str++ = (unsigned char)va_arg(args, int);
				break;
			case 's':
				s = va_arg(args, char *);
				if (*(fmt_head-2) != '%') {
					skip_ncopy(str, fmt, fmt_head-fmt);
					while (skip_copy(str, s) != 0) {} // copy until '\0' inclusive
				}
				else {
					// data-saving trick - if just %s don't bother with the '%s' bit
					while (*s) {skip_copy(str, s);} // copy until '\0' non-inclusive
				}
				break;
			case 'e':
			case 'E':
			case 'f':
			case 'F':
			case 'g':
			case 'G':
				skip_ncopy(str, fmt, fmt_head-fmt);
				// apparently va_args automatically promote all floats to double...
				float fnum = (float)va_arg(args, double);
				skip_ncopy(str, &fnum, sizeof(float));
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
				skip_ncopy(str, fmt, fmt_head-fmt-1);

				if (0 <= num && num <= 255) {
					*str++ = *(fmt_head-1) + 128;
					len = 1;
				}
				else {
					*str++ = *(fmt_head-1);
				}
				skip_ncopy(str, &num, len);
				break;
			case '%':
				skip_ncopy(str, fmt, fmt_head-fmt);
				break;
			case '\0':
				*str++ = '\0';
				fmt_head--;
				break;
			case '*':
				skip_ncopy(str, fmt, fmt_head-fmt);
				*str++ = (unsigned char)va_arg(args, int);
				fmt = fmt_head;
			default:
				continue;
			}

			fmt = fmt_head;
			break;
		}
	}
	return str-buf;
}


int sprintf_df(char* dst, const char* fmt, ...)
{
	va_list args;
    va_start(args, fmt);
    int ret = vsprintf_df(dst, fmt, args);
    va_end(args);

	return ret;
}
