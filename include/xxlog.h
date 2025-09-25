#if !defined(_XXLOG_H_)
#define _XXLOG_H_

#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define XXLOGBFLEN (120) /* Buffer Length  >> 8 */
#define MAXNUMLEN (1024) /* %* 字符串最大长度 */

#define XXLOG_TEST  (0x00)
#define XXLOG_UART  (0x01)
#define XXLOG_IIC   (0x02)
#define XXLOG_SPI   (0x03)

#define XXLOG_INFO      (0x01)
#define XXLOG_DEBUG     (0x02)
#define XXLOG_WARNING   (0x03)
#define XXLOG_ERROR     (0x04)

#if !defined(_COPY_VA_LIST_H_)
#define _COPY_VA_LIST_H_

/* C99 及以上：直接用标准 va_copy */
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
#define VA_COPY(dst, src) va_copy(dst, src)
#define VA_END_COPY(args) va_end(args)

/* GCC/Clang 私有内建 */
#elif defined(__GNUC__) || defined(__clang__)
#define VA_COPY(dst, src) __va_copy(dst, src)
#define VA_END_COPY(args) va_end(args)

/* MSVC 老版本（< C99）*/
#elif defined(_MSC_VER) && (_MSC_VER < 1800)
#define VA_COPY(dst, src) ((dst) = (src)) /* MSVC 早期可直接赋值 */
#define VA_END_COPY(args)                 /* 空，MSVC 不需要 va_end 复制本 */

/* IAR/ARMCC 等私有内建 */
#elif defined(__ICCARM__) || defined(__CC_ARM)
#define VA_COPY(dst, src) __va_copy(dst, src)
#define VA_END_COPY(args) va_end(args)

/* 编译错误提示 */
#else
#error "va_list copy not supported on this C89 compiler"
#endif

#endif /* _COPY_VA_LIST_H_ */

#ifndef TINY_VFMT_H
#define TINY_VFMT_H

/* ① C99 及以上：直接用 vsnprintf */
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
#define VSNPRINTF_BUF(buf, size, fmt, ap) vsnprintf(buf, size, fmt, ap)

/* ② C89/C90：退化到 vsprintf，但手动加 '\0' 截断 */
#else
#define VSNPRINTF_BUF(buf, size, fmt, ap) \
    ((void)(size), vsprintf(buf, fmt, ap)) /* size 被吃掉，避免警告 */
#endif

#endif /* TINY_VFMT_H */

/*-------测试buffer结构体---------*/
#define XXLOG_TESTLEN (4096) /*test buffer len*/
typedef struct
{
    char xxlog_testbuffer[XXLOG_TESTLEN];
    int i;
} xxlog_testbf_t;

void xxlog_print(unsigned int loglevel, unsigned int channel, const char *fmt, ...);
void xxlog_print_args(unsigned int loglevel, unsigned int channel, const char *fmt, va_list args);

#endif
