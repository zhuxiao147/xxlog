
#include "../include/xxlog.h"
unsigned int XXLOG_LEVEL = 0; 

/*-------测试使用---------*/
xxlog_test_t  testbuf;

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
    for (i = 0; i < strlen; i++)
    {
        xxlog_putchar(str[i], channel);
        if (str[i] == '\0')
            break;
    }
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

    if (XXLOG_LEVEL > loglevel)
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
            memset(buffer, 0, sizeof(buffer));
            buffer[0] = '%';
            for (i = 1; i < XXLOGBFLEN - 1 && p[0] != '\0' && p[0] != '%'; i++)
            {
                buffer[i] = *p++;
            }
            memset(tmpbuffer, 0, sizeof(tmpbuffer));
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
    xxlog_putchar('\0', channel);

    va_end(args);
    return;
}

void xxlog_print_test(unsigned int loglevel, unsigned int channel, const char *fmt, va_list args)
{
    char buffer[XXLOGBFLEN];
    char tmpbuffer[XXLOGBFLEN + MAXNUMLEN];
    char *p;
    unsigned int needlen = 0;
    size_t i = 0;

    if (XXLOG_LEVEL > loglevel)
        return;
    
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
            memset(buffer, 0, sizeof(buffer));
            buffer[0] = '%';
            for (i = 1; i < XXLOGBFLEN - 1 && p[0] != '\0' && p[0] != '%'; i++)
            {
                buffer[i] = *p++;
            }
            memset(tmpbuffer, 0, sizeof(tmpbuffer));
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
    xxlog_putchar('\0', channel);

    return;
}