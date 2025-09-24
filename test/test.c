#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "../include/xxlog.h"

// 测试结果统计
typedef struct {
    int total_tests;
    int passed_tests;
    int failed_tests;
} TestStats;

TestStats stats = {0, 0, 0};
extern xxlog_test_t  testbuf;

// 比较函数输出的辅助函数
int compare_printf_output(const char *format, ...)
{
    char buffer1[XXLOG_TESTLEN];
    char buffer2[XXLOG_TESTLEN];

    va_list arg1,args2;
    va_start(arg1, format);
    memset(testbuf.xxlog_testbuffer, 0, XXLOG_TESTLEN);
    testbuf.i = 0;
    xxlog_print_test(XXLOG_INFO, XXLOG_TEST, format, arg1);
    memcpy(buffer1, testbuf.xxlog_testbuffer, XXLOG_TESTLEN);
    va_end(arg1);

    // 使用标准 printf (通过 snprintf 模拟)
    va_start(args2, format);
    vsprintf(buffer2, format, args2);
    va_end(args2);
    
    // 比较结果
    int result = (strcmp(buffer1, buffer2) == 0);
    
    if (!result) {
        printf("FAIL: Format: %s\n", format);
        printf("  Expected: '%s' \n", buffer2);
        printf("  Got:      '%s' \n", buffer1);
    }
    
    return result;
}

// 测试用例运行器
void run_test(int (*test_func)(void), const char *test_name)
{
    stats.total_tests++;
    printf("Running test: %s... ", test_name);
    
    if (test_func()) {
        stats.passed_tests++;
        printf("PASS\n");
    } else {
        stats.failed_tests++;
        printf("FAIL\n");
    }
}

// 基础格式化测试
int test_basic_formatting() {
    return compare_printf_output("Hello, World!");
}

int test_integers() {
    int results = 1;
    results &= compare_printf_output("%d", 42);
    results &= compare_printf_output("%i", -123);
    results &= compare_printf_output("%u", 4294967295U);
    results &= compare_printf_output("%+d", 100);
    results &= compare_printf_output("% d", 50);
    return results;
}

int test_floats() {
    int results = 1;
    results &= compare_printf_output("%f", 3.14159);
    results &= compare_printf_output("%.2f", 3.14159);
    results &= compare_printf_output("%10.3f", 3.14159);
    results &= compare_printf_output("%e", 12345.6789);
    results &= compare_printf_output("%g", 12345.6789);
    return results;
}

int test_strings() {
    int results = 1;
    results &= compare_printf_output("%s", "Hello");
    results &= compare_printf_output("%10s", "Hello");
    results &= compare_printf_output("%-10s", "Hello");
    results &= compare_printf_output("%.3s", "Hello");
    return results;
}

int test_chars() {
    int results = 1;
    results &= compare_printf_output("%c", 'A');
    results &= compare_printf_output("%c", ' ');
    results &= compare_printf_output("%c", '\n');
    return results;
}

int test_hex_octal() {
    int results = 1;
    results &= compare_printf_output("%x", 255);
    results &= compare_printf_output("%X", 255);
    results &= compare_printf_output("%o", 63);
    results &= compare_printf_output("%#x", 255);
    results &= compare_printf_output("%#X", 255);
    return results;
}

int test_pointers() {
    int results = 1;
    int x = 42;
    void *ptr = &x;
    results &= compare_printf_output("%p", ptr);
    results &= compare_printf_output("%p", NULL);
    return results;
}

int test_width_precision() {
    int results = 1;
    results &= compare_printf_output("%10d", 123);
    results &= compare_printf_output("%-10d", 123);
    results &= compare_printf_output("%010d", 123);
    results &= compare_printf_output("%.5d", 123);
    results &= compare_printf_output("%10.5d", 123);
    return results;
}

int test_multiple_args() {
    return compare_printf_output("Name: %s, Age: %d, Score: %.2f", "Alice", 25, 95.5);
}

int test_special_cases() {
    int results = 1;
    results &= compare_printf_output("%%");  // 百分号
    results &= compare_printf_output("");    // 空字符串
    results &= compare_printf_output("%s", ""); // 空字符串参数
    results &= compare_printf_output(NULL);  // NULL 格式字符串（边界测试）
    return results;
}

int test_edge_cases() {
    int results = 1;
    results &= compare_printf_output("%d", 0);
    results &= compare_printf_output("%d", -2147483647);
    results &= compare_printf_output("%f", 0.0);
    results &= compare_printf_output("%f", -0.0);
    results &= compare_printf_output("%s", NULL); // NULL 字符串指针
    return results;
}

int test_performance() {
    clock_t start, end;
    double myprintf_time, printf_time;
    int iterations = 10000;
    
    // 测试 xxlog_print 性能
    memset(testbuf.xxlog_testbuffer, 0, XXLOG_TESTLEN);
    testbuf.i = 0;
    start = clock();
    for (int i = 0; i < iterations; i++) {
        testbuf.i = 0;
        xxlog_print(XXLOG_INFO, XXLOG_TEST, "Iteration %d: %f", i, i * 3.14159);
    }
    end = clock();
    myprintf_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    // 测试标准 printf 性能
    start = clock();
    for (int i = 0; i < iterations; i++) {
        char buffer[100];
        sprintf(buffer, "Iteration %d: %f", i, i * 3.14159);
    }
    end = clock();
    printf_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    printf("Performance: myprintf=%.4fs, printf=%.4fs\n", myprintf_time, printf_time);
    
    // 允许 20% 的性能差异
    return (myprintf_time <= printf_time * 2);
}

int test_large_output() {
    char large_format[1024];
    char large_arg[1024];
    
    // 生成大字符串
    memset(large_format, 'A', sizeof(large_format)-1);
    large_format[sizeof(large_format)-1] = '\0';
    memset(large_arg, 'B', sizeof(large_arg)-1);
    large_arg[sizeof(large_arg)-1] = '\0';
    
    return compare_printf_output("%s", large_arg);
}

int main() {
    printf("Starting myprintf vs printf compatibility tests...\n\n");
    // 运行测试套件
    run_test(test_basic_formatting, "Basic formatting");
    run_test(test_integers, "Integer formatting");
    run_test(test_floats, "Float formatting");
    run_test(test_strings, "String formatting");
    run_test(test_chars, "Character formatting");
    run_test(test_hex_octal, "Hex/Octal formatting");
    run_test(test_pointers, "Pointer formatting");
    run_test(test_width_precision, "Width/Precision");
    run_test(test_multiple_args, "Multiple arguments");
    run_test(test_special_cases, "Special cases");
    run_test(test_edge_cases, "Edge cases");
    run_test(test_performance, "Performance test");
    run_test(test_large_output, "Large output test");

    // 输出测试结果摘要
    printf("\n=== TEST SUMMARY ===\n");
    printf("Total tests:  %d\n", stats.total_tests);
    printf("Passed:       %d\n", stats.passed_tests);
    printf("Failed:       %d\n", stats.failed_tests);
    printf("Success rate: %.1f%%\n", 
           (float)stats.passed_tests / stats.total_tests * 100);
    
    if (stats.failed_tests == 0) {
        printf("\n✅ ALL TESTS PASSED! xxlog_print is compatible with printf.\n");
        return 0;
    } else {
        printf("\n❌ SOME TESTS FAILED! xxlog_print needs fixes.\n");
        return 1;
    }
}
