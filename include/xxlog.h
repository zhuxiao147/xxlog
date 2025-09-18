#pragma once
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define XXLOGBFLEN 10 // Buffer Length  >> 8
#define MAXNUMLEN 12 // 数字转字符串最大长度

#define XXLOG_UART (0x01)
#define XXLOG_IIC (0x02)
#define XXLOG_SPI (0x03)

#define XXLOG_INFO  (0x01)
#define XXLOG_DEBUG  (0x02)
#define XXLOG_WARNING  (0x03)
#define XXLOG_ERROR  (0x04)

unsigned int xxlog_print(unsigned int loglevel, unsigned int channel, const char *fmt, ...);