#pragma once
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define XXLOGBFLEN 120 // Buffer Length  >> 8
#define MAXNUMLEN 120 // 数字转字符串最大长度

#define XXLOG_TEST (0x00)
#define XXLOG_UART (0x01)
#define XXLOG_IIC (0x02)
#define XXLOG_SPI (0x03)

#define XXLOG_INFO  (0x01)
#define XXLOG_DEBUG  (0x02)
#define XXLOG_WARNING  (0x03)
#define XXLOG_ERROR  (0x04)



/*-------测试buffer结构体---------*/
#define XXLOG_TESTLEN  (1024)
typedef struct 
{
    char xxlog_testbuffer[XXLOG_TESTLEN];
    int i;
}xxlog_test_t;

void xxlog_print(unsigned int loglevel, unsigned int channel, const char *fmt, ...);
void xxlog_print_test(unsigned int loglevel, unsigned int channel, const char *fmt, va_list args);