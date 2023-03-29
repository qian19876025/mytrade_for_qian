#include "memory_log.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string>

Memory_log::Memory_log(uint32_t log_size)
{
    #if 0
    if (!log_size < 200)
        printf("error memory log buf size too small size %d \r\n", log_size);
    buff = new char[log_size];
    if (!buff)
        return;
    buf_size = log_size;
    memset(buff, 0, log_size * sizeof(char));
    #endif
}

static unsigned long m_pow(int x, int y)
{

    unsigned long sum = 1;
    while (y--)
    {
        sum *= x;
    }
    return sum;
}
int Memory_log::log_input(char *str, ...)
{

#if 0
    va_list ap; // 定义一个可变 参数的（字符指针）
    int val, r_val;
    char count, ch;
    char *s = NULL;
    int res = 0; // 返回值

    va_start(ap, str);   // 初始化ap
    while ('\0' != *str) // str为字符串,它的最后一个字符肯定是'\0'（字符串的结束符）
    {
        switch (*str)
        {
        case '%': // 发送参数
            str++;
            switch (*str)
            {
            case 'd': // 10进制输出
                val = va_arg(ap, int);
                r_val = val;
                count = 0;
                while (r_val)
                {
                    count++; // 整数的长度
                    r_val /= 10;
                }
                res += count;
                // 返回值长度增加​
                r_val = val;
                while (count)
                {
                    ch = r_val / m_pow(10, count - 1);
                    r_val %= m_pow(10, count - 1);
                    m_putchar(ch + '0');
                    // 数字到字符的转换
                    count--;
                }
                break;
            case 'x': // 16进制输出
                val = va_arg(ap, int);
                r_val = val;
                count = 0;
                while (r_val)
                {
                    count++; // 整数的长度
                    r_val /= 16;
                }
                res += count;
                // 返回值长度增加​
                r_val = val;
                while (count)
                {
                    ch = r_val / m_pow(16, count - 1);
                    r_val %= m_pow(16, count - 1);
                    if (ch <= 9)
                        m_putchar(ch + '0');
                    // 数字到字符的转换
                    else
                        m_putchar(ch - 10 + 'a');
                    count--;
                }
                break;
            case 's': // 发送字符串
                s = va_arg(a, char *);
                m_putstr(s);
                // 字符串,返回值为字符指针
                res += strlen(s);
                // 返回值长度增加 ​
                break;
            case 'c' m_putchar((char)va_arg(ap, int)); // 大家猜为什么不写char，而要写int
                res += 1;
                break;
                default:;
            }
            break;
        case '\n':
            m_putchar('\n');
            res += 1;
            break;
        case '\r':
            m_putchar('\r');
            res += 1;
            break;

        default: // 显示原来的第一个参数的字符串(不是..里的参数o)
            m_putchar(*str);
            res += 1;
        }
        str++;
    }
    va_end(ap);
    return res;
    #else
    printf("%s",str);
    #endif
    return 0;
}