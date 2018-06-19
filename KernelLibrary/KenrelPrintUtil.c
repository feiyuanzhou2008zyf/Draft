#include "Kernel/CarbonKernelPrintUtil.h"
extern uint8_t cursor_x;
extern uint8_t cursor_y;
extern uint16_t *video_memory;
void ClearScreen() {
    uint8_t attribute_byte = (0 << 4) | (0x5 & 0x0F);
    uint16_t blank = 0x20 | (attribute_byte << 8);
    int i;
    for (i = 0; i < 80 * 25; i++)
        video_memory[i] = blank;
    cursor_x = 0;
    cursor_y = 0;
    move_cursor();
}
void WriteScreen(char *str) {
    while (*str)
        Putchar(*str++);
}
void Putchar(char c) {
    uint8_t back_color = (uint8_t)0;
    uint8_t front_color = (uint8_t)15;
    uint8_t attribute_byte = (back_color << 4) | (front_color & 0x0F);
    uint16_t attribute = attribute_byte << 8;
    if (c == 0x08 && cursor_x) { cursor_x--; }
    else if (c == 0x09) { cursor_x = (cursor_x + 8) & ~(8 - 1); }
    else if (c == '\r') { cursor_x = 0; }
    else if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    }
    else if (c >= ' ') {
        video_memory[cursor_y * 80 + cursor_x] = c | attribute;
        cursor_x++;
    }
    if (cursor_x >= 80) {
        cursor_x = 0;
        cursor_y++;
    }
    scroll();
    move_cursor();
}
void KernelPrint(const char *format, ...) {
    static char buffer[1024];
    va_list args;
    va_start(args, format);
    int i = vsprintf(buffer, format, args);
    va_end(args);
    buffer[i] = '\0';
    WriteScreen(buffer);
}