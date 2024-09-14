#include "drivers/vga.h"

const char cradle1[] = "                           \n"
                       "                           \n"
                       "                           \n"
                       "                           \n"
                       "             +-----------+ \n"
                       "             |   |||||   | \n"
                       "             |   |||||   | \n"
                       "             |   00000   | \n";

const char cradle2[] = "                           \n"
                       "                           \n"
                       "                           \n"
                       "                           \n"
                       "             +-----------+ \n"
                       "             |   |||||   | \n"
                       "             |   |||| \\  | \n"
                       "             |   0000  0 | \n";

const char cradle3[] = "                           \n"
                       "                           \n"
                       "                           \n"
                       "                           \n"
                       "             +-----------+ \n"
                       "             |   |||||   | \n"
                       "             |  / ||||   | \n"
                       "             | 0  0000   | \n";

static unsigned char my_get_color(unsigned char fg, unsigned char bg) {
    return (bg << 4) + fg;
}

void my_vga_set_char(unsigned offset, char c, unsigned char color) {
    video_memory[2 * offset] = c;
    video_memory[2 * offset + 1] = color;
}

static int iter = 0;

void print_cradle(const char* s) {

    unsigned offset = 0;

    unsigned char colors[] = {red, magenta, green};

    while(*s != 0) {
        if (*s == '\n') {
            offset = COLS * (offset / COLS + 1);
        } else {
            unsigned char color = my_get_color(brown, black);
            if (*s == '0') {
                color = my_get_color(colors[iter % 3], black);
            }
            my_vga_set_char(offset, *s, color);
            ++offset;
        }
        ++s;
    }
}


void show_vga_symbol_table() {
    const char* cradles[] = {cradle1, cradle2, cradle1, cradle3};

    vga_clear_screen();
    print_cradle(cradles[iter++ % 4]);
}
