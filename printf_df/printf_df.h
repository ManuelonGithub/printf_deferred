

#ifndef PRINTF_DF_H_
#define PRINTF_DF_H_

#include <stdarg.h>

int vprintf_df(const char *fmt, va_list args);

/**
 * @brief 	deferred printf
 * @param	putc callback function that will accept a byte to be processed/outputted
 * @param	fmt printf format string
 * @param	... variable arguments to be processed according to the format
 * @warning	This function is not thread-safe/reentrant 
 * 			due to utilizing a callback function as an output
 */
__attribute__ ((format (printf, 1, 2))) void printf_df(const char* fmt, ...);

#endif // !PRINTF_DF_H_
