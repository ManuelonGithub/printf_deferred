

#include "../sprintf_df/sprintf_df.h"
#include "sprintf_df_parser.h"

#include <stdio.h>

static void test(const char* fmt, ...)
{
	va_list args, arg_copy;
    va_start(args, fmt);
	va_copy(arg_copy, args);

	char dprint_buf[512], test_buf[512];

    int dprint_size = vsprintf_df(dprint_buf, fmt, args);
    int test_size = parse_sprintf_df(test_buf, dprint_buf, dprint_size);

	printf("| test start\n");

	printf("parsed >> %s", test_buf);

	printf("\nprint_df size = %d, parsed size = %d\n\n", dprint_size, test_size);

	printf("printf >> ");
	vprintf(fmt, arg_copy);

	printf("| test end\n\n");

	va_end(args);
}

int main(void)
{
	char buf[512], valid[512];
	int size, size_valid;

	test("the value is %d\n", 0xdeadbeef);
	test("the value is %f\n", 3.141592);
	test("the value is %d\n", 1);
	test("the string is \"%s\"\n", "Hello there :)");
	test("the value is %hhx%hhx%hhx%hhx\n", 0x12, 0x34, 0x56, 0x78);
	test("the string is \"%.5s\"\n", "Hello there :)");
	test("the value is %%d\n", 254);
	test("the value is %*.*d\n", 10, 4, 254);

	// bad formats - output may vary b/w printf & parser
	test("the value is %lhx\n", 0x12L);
	test("the value is %hlx\n", 0x12);
	test("the value is %+ -0#10.4E\n", -3.125);
	test("the value is %+ -0#10.4\n");
	test("the value is *%+ -0#10.4h*\n");

	// size = sprintf_deferred(buf, "the value is %d\n", 0xdeadbeef);
	// size_valid = ftnirps(valid, buf, size);
	// printf("| %s | ", valid);
	// printf("deferred size = %d, processed size = %d\n", size, size_valid);

	// size = sprintf_deferred(buf, "the value is %f\n", 3.141592);
	// size_valid = ftnirps(valid, buf, size);
	// printf("| %s | ", valid);
	// printf("deferred size = %d, processed size = %d\n", size, size_valid);

	// size = sprintf_deferred(buf, "the value is %d\n", 1);
	// size_valid = ftnirps(valid, buf, size);
	// printf("| %s | ", valid);
	// printf("deferred size = %d, processed size = %d\n", size, size_valid);

	// size = sprintf_deferred(buf, "the string is \"%s\"\n", "Hello there :)");
	// size_valid = ftnirps(valid, buf, size);
	// printf("| %s | ", valid);
	// printf("deferred size = %d, processed size = %d\n", size, size_valid);

	// size = sprintf_deferred(buf, "the value is %hhx%hhx%hhx%hhx\n", 0x12, 0x34, 0x56, 0x78);
	// size_valid = ftnirps(valid, buf, size);
	// printf("| %s | ", valid);
	// printf("deferred size = %d, processed size = %d\n", size, size_valid);

	// size = sprintf_deferred(buf, "the string is \"%.5s\"\n", "Hello there :)");
	// size_valid = ftnirps(valid, buf, size);
	// printf("| %s | ", valid);
	// printf("deferred size = %d, processed size = %d\n", size, size_valid);

	// size = sprintf_deferred(buf, "the value is %%d\n", 254);
	// size_valid = ftnirps(valid, buf, size);
	// printf("| %s | ", valid);
	// printf("deferred size = %d, processed size = %d\n", size, size_valid);

	// size = sprintf_deferred(buf, "the value is %*.*d\n", 10, 4, 254);
	// size_valid = ftnirps(valid, buf, size);
	// printf("| %s | ", valid);
	// printf("deferred size = %d, processed size = %d\n", size, size_valid);

	// size = sprintf_deferred(buf, "the value is %lhx\n", 0x12L);
	// size_valid = ftnirps(valid, buf, size);
	// printf("| %s | ", valid);
	// printf("deferred size = %d, processed size = %d\n", size, size_valid);
	
	// size = sprintf_deferred(buf, "the value is %hlx\n", 0x12);
	// size_valid = ftnirps(valid, buf, size);
	// printf("| %s | ", valid);
	// printf("deferred size = %d, processed size = %d\n", size, size_valid);

	// size = sprintf_deferred(buf, "the value is %+ -0#10.4E\n", -3.125);
	// size_valid = ftnirps(valid, buf, size);
	// printf("| %s | ", valid);
	// printf("deferred size = %d, processed size = %d\n", size, size_valid);

	// size = sprintf_deferred(buf, "the value is %+ -0#10.4\n");
	// size_valid = ftnirps(valid, buf, size);
	// printf("| %s | ", valid);
	// printf("deferred size = %d, processed size = %d\n", size, size_valid);

	// size = sprintf_deferred(buf, "the value is *%+ -0#10.4h*\n");
	// size_valid = ftnirps(valid, buf, size);
	// printf("| %s | ", valid);
	// printf("deferred size = %d, processed size = %d\n", size, size_valid);

	return 0;
}