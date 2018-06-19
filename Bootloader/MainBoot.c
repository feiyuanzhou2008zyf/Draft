#include "Bootloader/MainBoot.h"
#include "DebugTool/DebugUtil.h"
#include "GlobalDescriptor/DescriptorUtil.h"
#include "Interrupt/InterruptService.h"
#include "Memory/PhysicalMemory.h"
#define INIT(x) ({ \
    KernelPrint("Init %s", #x); \
    if (Init##x()) { KernelPrint(" [OK]\n"); } \
    else { KernelPrint(" [Failed]\n");while(1); } \
})
static uint32_t magic;
MultibootInfo *multibootInfoPtr;
MultibootHeader master_boot_record __attribute__((section(".init.text"))) = {
        BOOT_MAGIC,
        ARCHITECTURE,
        sizeof(MultibootHeader),
        0 - BOOT_MAGIC - ARCHITECTURE - sizeof(MultibootHeader),
        {0, 0, 8}
};
void main() {
    asm volatile ("movl %%eax, %0" : "=c"(magic) :: "eax");
    asm volatile ("movl %%ebx, %0" : "=c"(multibootInfoPtr) :: "ebx");
    runtime_assert(magic == 0x36D76289, "Exception: Magic invalid, cannot load kernel into memory");
    cli();
    KernelPrint("Starting configure the kernel\n");
    KernelConfigure();
    hlt();
}
void KernelConfigure() {
    KernelPrint("Setup the hardware\n");
    INIT(GDT);
    INIT(IDT);
    sti();
    KernelPrint("Preconfigure the software\n");
    INIT(Debug);
    INIT(PhysicManager);
    ClearScreen();
    KernelMain();
}