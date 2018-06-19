#pragma once
#ifndef STRING_LIBRARY_H
#define STRING_LIBRARY_H
#include "../Kernel/CarbonDefine.h"
#include "../Kernel/CarbonKernelPrintUtil.h"
#include "../Kernel/KernelInlineAssembly.h"
#include "../DebugTool/KernelAssert.h"
void *memcpy(void *dest, const void *src, size_t count);
void *memset(void *src, int chunk, size_t count);
void *memmove(void *dest, const void *src, size_t n);
int strcmp(const char *str1, const char *str2);
char *strcpy(char *dest, const char *src);
char *strcat(char *dest, const char *src);
int strlen(const char *src);
#endif // STRING_LIBRARY_H