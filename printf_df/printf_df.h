#ifndef D_PRINTF_H_
#define D_PRINTF_H_

#include <stdarg.h>

int vprintf_df(void (*putc)(char), const char *fmt, va_list args);

/**
 * @brief 	deferred printf
 * @param	putc callback function that will accept a byte to be processed/outputted
 * @param	fmt printf format string
 * @param	... variable arguments to be processed according to the format
 * @warning	This function is not thread-safe/reentrant 
 * 			due to utilizing a callback function as an output
 */
__attribute__ ((format (printf, 2, 3))) void printf_df(void (*putc)(char), const char* fmt, ...);


int vsprintf_df(char* buf, const char *fmt, va_list args);

/**
 * @brief deferred sprintf
 * @param	dst byte buffer to insert processed data into - output is not a c-string!
 * @param	fmt printf format string
 * @param	... variable arguments to be processed according to the format
 * @return	length of the content in dst
 * @note	This function is fully thread-safe/reetrant.
 * @warning	dst will not be c-string compatible. 
 */
__attribute__ ((format (printf, 2, 3))) int sprintf_df(char* dst, const char* fmt, ...);

#endif // !D_PRINTF_H_
