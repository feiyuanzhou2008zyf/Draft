#pragma once
#ifndef CARBON_KERNEL_PRINT_UTIL_H
#define CARBON_KERNEL_PRINT_UTIL_H
#include "CarbonDefine.h"
#include "KernelInlineAssembly.h"
#include "RuntimeLibrary/StringLibrary.h"
typedef char* va_list;
#define va_start(p, first) (p = (va_list)&first + sizeof(first))
#define va_args(p, next) ({ (*(next*)((p += sizeof(next)) - sizeof(next))); })
#define va_end(p) (p = (va_list)NULL)
void ClearScreen();
void WriteScreen(char *str);
void Putchar(char c);
void KernelPrint(const char *format, ...);
int skip_atoi(const char **s);
char *number(char *str, int num, int base, int size, int precision, int type);
int vsprintf(char *buff, const char *format, va_list args);
void move_cursor();
void scroll();
#endif // CARBON_KERNEL_PRINT_UTIL_H