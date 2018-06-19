#include "Memory/PhysicalMemory.h"
static uint32_t PhysicStack[PAGE_MAX_SIZE + 1];
static uint32_t PhysicStackTop;
uint32_t PhysicPageCount;
static MultibootTagMemoryMap *tagPtr;
void ShowMemoryMap() {
    KernelPrint("Memory map: \n");
    for (MMapEntry *map_entry = tagPtr->entries; ((uint8_t *)map_entry - (uint8_t *)tagPtr->entries) < tagPtr->size - sizeof(MultibootTagMemoryMap); map_entry = (MMapEntry *)(((uint8_t *)map_entry) + tagPtr->entry_size)) {
        KernelPrint("base_addr = 0x%X%08X, length = 0x%X%08X, type = 0x%X\n", (uint32_t)map_entry->base_addr_high, (uint32_t)map_entry->base_addr_low, (uint32_t)map_entry->length_high, (uint32_t)map_entry->length_low, (uint32_t)map_entry->type);
    }
}
Bool InitPhysicManager() {
    tagPtr = FindMultibootTag(TAG_MMAP);
    for (MMapEntry *map_entry = (MMapEntry *)tagPtr->entries;((uint8_t *)map_entry - (uint8_t *)tagPtr->entries) < tagPtr->size - sizeof(MultibootTagMemoryMap); map_entry = (MMapEntry *)(((uint8_t *)map_entry) + tagPtr->entry_size)) {
        if (map_entry->type == 1 && map_entry->base_addr_low == 0x100000) {
            uint32_t page_addr = map_entry->base_addr_low + (uint32_t)(kernel_end - kernel_start);
            uint32_t length = map_entry->base_addr_low + map_entry->length_low;
            while (page_addr < length && page_addr <= PMM_MAX_SIZE) {
                PhysicFreePage(page_addr);
                page_addr += PMM_PAGE_SIZE;
                PhysicPageCount++;
            }
        }
    }
    return TRUE;
}
uint32_t PhysicAllocPage() {
    runtime_assert(PhysicStackTop != 0, "Out of memory");
    uint32_t page = PhysicStack[PhysicStackTop--];
    return page;
}
void PhysicFreePage(uint32_t p) {
    runtime_assert(PhysicStackTop != PAGE_MAX_SIZE, "Out of \"PhysicStack\" Stack");
    PhysicStack[++PhysicStackTop] = p;
}