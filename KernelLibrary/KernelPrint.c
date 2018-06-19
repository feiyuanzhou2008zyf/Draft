#include "Kernel/CarbonKernelPrintUtil.h"
#define is_digit(c) ((c) >= '0' && (c) <= '9')
#define ZEROPAD	1
#define SIGN 2
#define PLUS 4
#define SPACE 8
#define LEFT 16
#define SPECIAL 32
#define SMALL 64
#define do_div(n,base) ({ int __res;asm volatile ("divl %4" : "=a" (n),"=d" (__res):"0"(n),"1"(0),"r"(base));__res; })
uint16_t *video_memory = (uint16_t *)(0xB8000);
uint8_t cursor_x = 0;
uint8_t cursor_y = 0;
int skip_atoi(const char **s) {
    int i = 0;
    while (is_digit(**s)) { i = i * 10 + *((*s)++) - '0'; }
    return i;
}
char *number(char *str, int num, int base, int size, int precision, int type) {
    char c, sign, tmp[36];
    const char *digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i;
    if (type & SMALL) { digits = "0123456789abcdefghijklmnopqrstuvwxyz"; }
    if (type & LEFT) { type &= ~ZEROPAD; }
    if (base < 2 || base > 36) { return 0; }
    c = (type & ZEROPAD) ? '0' : ' ';
    if (type & SIGN && num < 0) {
        sign = '-';
        num = -num;
    }
    else { sign = (type & PLUS) ? '+' : ((type & SPACE) ? ' ' : 0); }
    if (sign) { size--; }
    if (type & SPECIAL) {
        if (base == 16) { size -= 2; }
        else if (base == 8) { size--; }
    }
    i = 0;
    if (num == 0) { tmp[i++] = '0'; }
    else { while (num != 0) { tmp[i++] = digits[do_div(num, base)]; } }
    if (i > precision) { precision = i; }
    size -= precision;
    if (!(type & (ZEROPAD + LEFT))) { while (size-- > 0) { *str++ = ' '; } }
    if (sign) { *str++ = sign; }
    if (type & SPECIAL) {
        if (base == 8) { *str++ = '0'; }
        else if (base == 16) {
            *str++ = '0';
            *str++ = digits[33];
        }
    }
    if (!(type & LEFT)) { while (size-- > 0) { *str++ = c; } }
    while (i < precision--) { *str++ = '0'; }
    while (i-- > 0) { *str++ = tmp[i]; }
    while (size-- > 0) { *str++ = ' '; }
    return str;
}
int vsprintf(char *buff, const char *format, va_list args) {
    int len;
    int i;
    char *str;
    char *s;
    int *ip;
    int flags;
    int field_width;
    int precision;
    for (str = buff; *format; ++format) {
        if (*format != '%') {
            *str++ = *format;
            continue;
        }
        flags = 0;
        repeat:
        ++format;
        switch (*format) {
            case '-':
                flags |= LEFT;
                goto repeat;
            case '+':
                flags |= PLUS;
                goto repeat;
            case ' ':
                flags |= SPACE;
                goto repeat;
            case '#':
                flags |= SPECIAL;
                goto repeat;
            case '0':
                flags |= ZEROPAD;
                goto repeat;
        }
        field_width = -1;
        if (is_digit(*format)) { field_width = skip_atoi(&format); }
        else if (*format == '*') {
            field_width = va_args(args, int);
            if (field_width < 0) {
                field_width = -field_width;
                flags |= LEFT;
            }
        }
        precision = -1;
        if (*format == '.') {
            ++format;
            if (is_digit(*format)) { precision = skip_atoi(&format); }
            else if (*format == '*') { precision = va_args(args, int); }
            if (precision < 0) { precision = 0; }
        }
        if (*format == 'h' || *format == 'l' || *format == 'L') { ++format; }
        switch (*format) {
            case 'c':
                if (!(flags & LEFT)) {
                    while (--field_width > 0) { *str++ = ' '; }
                }
                *str++ = (uint8_t)va_args(args, int);
                while (--field_width > 0) { *str++ = ' '; }
                break;
            case 's':
                s = va_args(args, char *);
                len = strlen(s);
                if (precision < 0) { precision = len; }
                else if (len > precision) { len = precision; }
                if (!(flags & LEFT)) { while (len < field_width--) { *str++ = ' '; } }
                for (i = 0; i < len; ++i) { *str++ = *s++; }
                while (len < field_width--) { *str++ = ' '; }
                break;
            case 'o':
                str = number(str, va_args(args, int), 8, field_width, precision, flags);
                break;
            case 'p':
                if (field_width == -1) {
                    field_width = 8;
                    flags |= ZEROPAD;
                }
                str = number(str, (uint32_t)va_args(args, void *), 16, field_width, precision, flags);
                break;
            case 'x':
                flags |= SMALL;
            case 'X':
                str = number(str, va_args(args, int), 16, field_width, precision, flags);
                break;
            case 'd': case 'i':
                flags |= SIGN;
            case 'u':
                str = number(str, va_args(args, int), 10, field_width, precision, flags);
                break;
            case 'b':
                str = number(str, va_args(args, int), 2, field_width, precision, flags);
                break;
            case 'n':
                ip = va_args(args, int *);
                *ip = (str - buff);
                break;
            default:
                if (*format != '%') { *str++ = '%'; }
                if (*format) { *str++ = *format; }
                else { --format; }
                break;
        }
    }
    *str = '\0';
    return (str - buff);
}
void move_cursor() {
    uint16_t cursorLocation = cursor_y * 80 + cursor_x;
    outb(0x3D4, 14);
    outb(0x3D5, cursorLocation >> 8);
    outb(0x3D4, 15);
    outb(0x3D5, cursorLocation);
}
void scroll() {
    uint8_t attribute_byte = (0 << 4) | (0x5 & 0x0F);
    uint16_t blank = 0x20 | (attribute_byte << 8);
    if (cursor_y >= 25) {
        int i;
        for (i = 0 * 80; i < 24 * 80; i++)
            video_memory[i] = video_memory[i + 80];
        for (i = 24 * 80; i < 25 * 80; i++)
            video_memory[i] = blank;
        cursor_y = 24;
    }
}