
#include "../include/xxlog.h"

static void xxlog_putchar(char c, unsigned int channel)
{
    switch (channel)
    {
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
}

unsigned int xxlog_print(unsigned int loglevel, unsigned int channel, const char *fmt, ...)
{
    char buffer[XXLOGBFLEN];
    char tmpbuffer[XXLOGBFLEN + MAXNUMLEN];
    char* p;
    unsigned int bf_head = 0;
    unsigned int needlen = 0;
    size_t i = 0;
    va_list args;
    va_start(args, fmt);

    p = (char * )fmt;
    while (p[0] != '\0')
    {
        if (p[0] != '%')
        {
            xxlog_putchar(p[0], channel);
            p++;
            continue;
        }
        p++;
        if(p[0] == '\0')
            break;
        if (p[0] != '%')
        {
            memset(buffer, 0, sizeof(buffer));
            buffer[0] = '%';
            for ( i = 1; i < XXLOGBFLEN-1 && p[0] != '\0' && p[0] != '%' ; i++)
            {
                buffer[i] = *p++;
            }
            memset(tmpbuffer, 0, sizeof(tmpbuffer));
            needlen = vsnprintf(tmpbuffer, sizeof(tmpbuffer), buffer, args);
            xxlog_putstr(tmpbuffer, needlen, channel);
            continue;    
        }else{
            xxlog_putchar(p[0], channel);
            p++;
            continue;
        }
    }
    xxlog_putchar('\0', channel);
    
    va_end(args);
}