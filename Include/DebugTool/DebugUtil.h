#pragma once
#ifndef DEBUG_UTIL_H
#define DEBUG_UTIL_H
#include "../Bootloader/MultibootElfSection.h"
#include "../Kernel/CarbonDefine.h"
#include "../Kernel/CarbonKernelPrintUtil.h"
#include "../Kernel/KernelInlineAssembly.h"
#include "../Elf/ELFUtil.h"
Bool InitDebug();
void Panic(const char *msg);
void PrintStackTrace();
#endif // DEBUG_UTIL_H