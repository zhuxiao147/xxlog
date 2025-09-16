#pragma once
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define XXLOGBFLEN 128 // Buffer Length
#define MAXNUMLEN 12 // 数字转字符串最大长度

#define XXLOG_UART (0x01)
#define XXLOG_IIC (0x02)
#define XXLOG_SPI (0x03)

#define XXLOG_INFO  (0x01)
#define XXLOG_DEBUG  (0x02)
#define XXLOG_WARNING  (0x03)
#define XXLOG_ERROR  (0x04)

static void xxlog_putchar(char c, unsigned int channel)
{
    switch (channel)
    {
    case XXLOG_UART :
            putchar(c);
        break;
    case XXLOG_IIC :
            putchar(c);
        break;
    case XXLOG_SPI :
            putchar(c);
        break;
    
    default:
        break;
    }

}

static void xxlog_putstr(char* str,unsigned int strlen ,unsigned int channel)
{
    size_t i = 0;
    for (i = 0; i < strlen; i++)
    {
        xxlog_putchar(str[i], channel);
        if(str[i] == '\0')
            break;
    }
}

unsigned int xxlog_print(unsigned int loglevel, unsigned int channel, const char *fmt, ...)
{
    char buffer[XXLOGBFLEN];
    unsigned int bf_head = 0;
    unsigned int needlen = 0;
    size_t i = 0;
    va_list args;
    va_start(args, fmt);

    needlen = vsnprintf(buffer, XXLOGBFLEN, fmt, args);

    xxlog_putstr(buffer, XXLOGBFLEN, channel);

    if (needlen > XXLOGBFLEN)
    {
        xxlog_putstr("\nXXLOGBFLEN too small\n", 23, channel);
    }

    va_end(args);
}