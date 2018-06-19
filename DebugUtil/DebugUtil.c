#include "DebugTool/DebugUtil.h"
static Elf kernel_elf;
Bool InitDebug() {
    kernel_elf = ElfFromMultiboot();
    return TRUE;
}
void Panic(const char *msg) {
    KernelPrint("*** System panic: %s ***\n", msg);
    PrintStackTrace();
    KernelPrint("*** System panic end ***\n");
    while (1);
}
void PrintStackTrace() {
    KernelPrint("Kernel Stack: \n");
    uint32_t *ebp, *eip;
    asm volatile ("mov %%ebp, %0" : "=r"(ebp));
    while (ebp) {
        eip = ebp + 1;
        KernelPrint("[0x%x] %s\n", *eip, ElfLookupSymbol(*eip, &kernel_elf));
        ebp = (uint32_t *)*ebp;
    }
}