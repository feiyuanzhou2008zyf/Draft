#pragma once
#ifndef MULTI_BOOT_ELF_SECTION_H
#define MULTI_BOOT_ELF_SECTION_H
#include "../Kernel/CarbonDefine.h"
#include "../Elf/ELFUtil.h"
typedef enum __multiboot_tag_type__ {
    TAG_END = 0,
    TAG_CMDLINE = 1,
    TAG_BOOT_LOADER_NAME = 2,
    TAG_MODULE = 3,
    TAG_BASIC_MEMINFO = 4,
    TAG_BOOTDEV = 5,
    TAG_MMAP = 6,
    TAG_VBE = 7,
    TAG_FRAMEBUFFER = 8,
    TAG_ELF_SECTIONS = 9,
    TAG_APM = 10,
    TAG_EFI32 = 11,
    TAG_EFI64 = 12,
    TAG_SMBIOS = 13,
    TAG_ACPI_OLD = 14,
    TAG_ACPI_NEW = 15,
    TAG_NETWORK = 16,
    TAG_EFI_MMAP = 17,
    TAG_EFI_BS = 18,
    TAG_EFI32_IH = 19,
    TAG_EFI64_IH = 20,
    TAG_LOAD_BASE_ADDR = 21,
} MultibootTagType;
typedef struct __multiboot_tag_elf_symbols__ {
    uint32_t type;
    uint32_t size;
    uint32_t num;
    uint32_t entsize;
    uint32_t shndx;
    ElfSectionHeader sectionHeader[0];
} MultibootTagElfSymbols;
void *FindMultibootTag(MultibootTagType type);
#endif // MULTI_BOOT_ELF_SECTION_H