#pragma once
#ifndef MULTI_BOOT_MEMORY_MAP_H
#define MULTI_BOOT_MEMORY_MAP_H
#include "../Kernel/CarbonDefine.h"
typedef enum __multiboot_mmap_type__ {
    AVAILABLE = 1,
    RESERVED = 2,
    ACPI_RECLAIMABLE = 3,
    NVS = 4,
    BADRAM = 5
} MultibootMMapType;
typedef struct __mmap_entry__ {
    uint32_t base_addr_low, base_addr_high;
    uint32_t length_low, length_high;
    MultibootMMapType type;
    uint32_t zero;
} MMapEntry;
typedef struct __multiboot_tag_memory_map__ {
    uint32_t type;
    uint32_t size;
    uint32_t entry_size;
    uint32_t entry_version;
    MMapEntry entries[0];
} MultibootTagMemoryMap;
#endif // MULTI_BOOT_MEMORY_MAP_H