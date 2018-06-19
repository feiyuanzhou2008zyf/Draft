cmake_minimum_required(VERSION 3.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include_directories(Include)
file(GLOB KERNEL_SOURCE ./*/*.c)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/Build)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-c -Wall -m32 -ggdb -gstabs+ -nostdinc -fno-builtin -fno-stack-protector -fpack-struct -mno-ms-bitfields")
set(KERNEL_LINK_FLAGS "-T ${PROJECT_SOURCE_DIR}/Script/link.ld -m elf_i386 -nostdlib")
set(CMAKE_C_LINK_EXECUTABLE "ld ${KERNEL_LINK_FLAGS} -o <TARGET> <OBJECTS>")
set(GRUB_COMPONMENTS ${PROJECT_SOURCE_DIR}/Boot)
set(ELF_TARGET "${EXECUTABLE_OUTPUT_PATH}/Kernel.elf")
set(OUTPUT_IMAGE "${EXECUTABLE_OUTPUT_PATH}/Carbon.iso")
add_executable(Kernel.elf ${KERNEL_SOURCE})
add_custom_target(Generate ALL DEPENDS ${GRUB_COMPONMENTS} ${ELF_TARGET})
add_custom_target(Debug)
add_custom_target(Clean)
add_custom_command(TARGET Generate
        POST_BUILD
        COMMAND echo "Generating the image..."
        COMMAND grub-mkrescue ${GRUB_COMPONMENTS} -o ${OUTPUT_IMAGE} ${ELF_TARGET}
        COMMAND echo "Generating the image finish"
        COMMAND exit)
add_custom_command(TARGET Debug
        POST_BUILD
        COMMAND qemu-system-i386 -s -S -hda ${OUTPUT_IMAGE}
        COMMAND exit)
add_custom_command(TARGET Clean
        POST_BUILD
        COMMAND rm -rf ${EXECUTABLE_OUTPUT_PATH}
        COMMAND exit)