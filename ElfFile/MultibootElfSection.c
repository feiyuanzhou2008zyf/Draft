#include "Bootloader/MainBoot.h"
void *FindMultibootTag(MultibootTagType type) {
    MultibootBaseTag *tagPtr = multibootInfoPtr->tags;
    while (tagPtr->type != 0) {
        if (tagPtr->type == type) {
            return tagPtr;
        }
        tagPtr = (MultibootBaseTag *)(((int)tagPtr) + ((tagPtr->size + 7) & ~7));
    }
    KernelPrint("Warning: No such Multiboot tag whose type = %d\n", type);
    return NULL;
}