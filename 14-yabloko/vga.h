#pragma once

void vga_clear_screen();

void vga_print_string(const char* s);
void vga_print_colored(const char* s);
enum {
    ROWS = 25,
    COLS = 80,

    VGA_CTRL_REGISTER = 0x3d4,
    VGA_DATA_REGISTER = 0x3d5,
    VGA_OFFSET_LOW = 0x0f,
    VGA_OFFSET_HIGH = 0x0e,
};

void vga_set_char2(int col, int row, char c);
