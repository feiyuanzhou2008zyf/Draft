#pragma once
#ifndef PHYSICAL_MEMORY_H
#define PHYSICAL_MEMORY_H
#include "../Bootloader/MainBoot.h"
#include "../Kernel/CarbonDefine.h"
#include "../DebugTool/KernelAssert.h"
#define STACK_SIZE 8192
#define PMM_MAX_SIZE 0x20000000
#define PMM_PAGE_SIZE 0x1000
#define PAGE_MAX_SIZE (PMM_MAX_SIZE / PMM_PAGE_SIZE)
#define PHY_PAGE_MASK 0xFFFFF000
extern uint8_t kernel_start[];
extern uint8_t kernel_end[];
extern uint32_t PhysicPageCount;
void ShowMemoryMap();
Bool InitPhysicManager();
uint32_t PhysicAllocPage();
void PhysicFreePage(uint32_t p);
#endif // PHYSICAL_MEMORY_H