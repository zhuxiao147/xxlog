
#include "../include/xxlog.h"
unsigned int XXLOG_LEVEL = 0; 

/*-------测试使用---------*/
xxlog_testbf_t  testbuf;

static void xxlog_putchar(char c, unsigned int channel)
{
    switch (channel)
    {
    case XXLOG_TEST:
        testbuf.xxlog_testbuffer[testbuf.i] = c; //测试，可注释
        testbuf.i++;
        break;
    case XXLOG_UART:
        putchar(c);
        break;
    case XXLOG_IIC:
        putchar(c);
        break;
    case XXLOG_SPI:
        putchar(c);
        break;

    default:
        break;
    }
    return;
}

static void xxlog_putstr(char *str, unsigned int strlen, unsigned int channel)
{
    size_t i = 0;
    for (i = 0; i < strlen || str[i] != '\0'; i++)
        xxlog_putchar(str[i], channel);
    return;
}

void xxlog_print(unsigned int loglevel, unsigned int channel, const char *fmt, ...)
{
    char buffer[XXLOGBFLEN];
    char tmpbuffer[XXLOGBFLEN + MAXNUMLEN];
    char *p;
    unsigned int needlen = 0;
    size_t i = 0;
    va_list args;

    if (XXLOG_LEVEL > loglevel || fmt == NULL)
        return;
    
    va_start(args, fmt);

    p = (char *)fmt;
    while (p[0] != '\0')
    {
        if (p[0] != '%')
        {
            xxlog_putchar(p[0], channel);
            p++;
            continue;
        }
        p++;
        if (p[0] == '\0')
            break;
        if (p[0] != '%')
        {
            buffer[0] = '%';
            for (i = 1; i < XXLOGBFLEN - 1 && p[0] != '\0' && p[0] != '%'; i++)
            {
                buffer[i] = *p++;
            }
            buffer[i] = '\0';
            needlen = vsnprintf(tmpbuffer, sizeof(tmpbuffer), buffer, args);
            xxlog_putstr(tmpbuffer, needlen, channel);
            continue;
        }
        else
        {
            xxlog_putchar(p[0], channel);
            p++;
            continue;
        }
    }

    va_end(args);
    return;
}

void xxlog_print_args(unsigned int loglevel, unsigned int channel, const char *fmt, va_list in_args)
{
    char buffer[XXLOGBFLEN];
    char tmpbuffer[XXLOGBFLEN + MAXNUMLEN];
    char *p;
    unsigned int needlen = 0;
    size_t i = 0;
    va_list args;

    if (XXLOG_LEVEL > loglevel || fmt == NULL)
        return;
    
    va_copy(args, in_args);
    
    p = (char *)fmt;
    while (p[0] != '\0')
    {
        if (p[0] != '%')
        {
            xxlog_putchar(p[0], channel);
            p++;
            continue;
        }
        p++;
        if (p[0] == '\0')
            break;
        if (p[0] != '%')
        {
            buffer[0] = '%';
            for (i = 1; i < XXLOGBFLEN - 1 && p[0] != '\0' && p[0] != '%'; i++)
            {
                buffer[i] = *p++;
            }
            buffer[i] = '\0';
            needlen = vsnprintf(tmpbuffer, sizeof(tmpbuffer), buffer, args);
            xxlog_putstr(tmpbuffer, needlen, channel);
            continue;
        }
        else
        {
            xxlog_putchar(p[0], channel);
            p++;
            continue;
        }
    }

    va_end(args);
    return;
}