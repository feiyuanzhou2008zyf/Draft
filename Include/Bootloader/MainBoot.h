#pragma once
#ifndef MAIN_BOOT_H
#define MAIN_BOOT_H
#define BOOT_MAGIC 0xE85250D6
#define ARCHITECTURE 0
#include "../Kernel/CarbonDefine.h"
#include "MultibootHeader.h"
#include "MultibootMemoryMap.h"
#include "MultibootElfSection.h"
#include "MultibootInfomation.h"
#include "../Kernel/KernelInlineAssembly.h"
#include "../Kernel/CarbonKernelPrintUtil.h"
#include "../DebugTool/KernelAssert.h"
#define main BootMain
extern MultibootInfo *multibootInfoPtr;
void BootMain();
void KernelConfigure();
void KernelMain();
#endif // MAIN_BOOT_H