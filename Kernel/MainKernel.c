#include "Bootloader/MainBoot.h"
#include "DebugTool/DebugUtil.h"
#include "Memory/PhysicalMemory.h"
void KernelMain() {
    KernelPrint("Kernel running...\n");
    ShowMemoryMap();
    KernelPrint("The count of physic page: %u\n", PhysicPageCount);
    uint32_t alloc_addr = NULL;
    KernelPrint("Test physical memory alloc: \n");
    alloc_addr = PhysicAllocPage();
    KernelPrint("Alloc physic address: 0x%08X\n", alloc_addr);
    alloc_addr = PhysicAllocPage();
    KernelPrint("Alloc physic address: 0x%08X\n", alloc_addr);
    alloc_addr = PhysicAllocPage();
    KernelPrint("Alloc physic address: 0x%08X\n", alloc_addr);
    alloc_addr = PhysicAllocPage();
    KernelPrint("Alloc physic address: 0x%08X\n", alloc_addr);
    while (1);
}