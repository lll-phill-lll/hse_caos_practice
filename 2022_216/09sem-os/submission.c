#include "drivers/vga.h"

void my_vga_clear_screen() {
    for (unsigned i = 0; i < ROWS * COLS; ++i) {
        video_memory[2 * i] = ' ';
        video_memory[2 * i + 1] = 0x07;
    }
}

const char tree1[] ="               z                     \n"
                    "              zrr                    \n"
                    "           zzzzrrrrr                 \n"
                    "             zz#rr                   \n"
                    "              z###r                   \n"
                    "            ##########                \n"
                    "           ##()########               \n"
                    "           ################             \n"
                    "          ####################           \n"
                    "             #########()#####             \n"
                    "           #####()################         \n"
                    "         ###########################       \n"
                    "            #######()######()#####         \n"
                    "        ##############################     \n"
                    "           ######################          \n"
                    "       ######()##############()########    \n"
                    "         ###########################       \n"
                    "                 |  /   |                  \n"
                    "                 |   \\\\ |                  \n"
                    "                 |   \\  |                  \n"
                    "_________________|______|__________________\n";

const char tree2[] ="                     z                     \n"
                    "                    zrr                    \n"
                    "                 zzzzrrrrr                 \n"
                    "                   zz#rr                   \n"
                    "                   z###r                   \n"
                    "                 ##########                \n"
                    "                ##()########               \n"
                    "              ################             \n"
                    "            ####################           \n"
                    "              #########()#####             \n"
                    "           #####()################         \n"
                    "         ###########################       \n"
                    "            #######()######()#####         \n"
                    "        ##############################     \n"
                    "           ######################          \n"
                    "       ######()##############()########    \n"
                    "         ###########################       \n"
                    "                 |  /   |                  \n"
                    "                 |   \\\\ |                  \n"
                    "                 |   \\  |                  \n"
                    "_________________|______|__________________\n";

const char tree3[] ="                           z     \n"
                    "                          zrr    \n"
                    "                       zzzzrrrrr \n"
                    "                         zz#rr   \n"
                    "                         z###r   \n"
                    "                      ##########  \n"
                    "                    ##()########  \n"
                    "                 ################             \n"
                    "              ####################           \n"
                    "               #########()#####             \n"
                    "           #####()################         \n"
                    "         ###########################       \n"
                    "            #######()######()#####         \n"
                    "        ##############################     \n"
                    "           ######################          \n"
                    "       ######()##############()########    \n"
                    "         ###########################       \n"
                    "                 |  /   |                  \n"
                    "                 |   \\\\ |                  \n"
                    "                 |   \\  |                  \n"
                    "_________________|______|__________________\n";

unsigned char my_get_color(unsigned char fg, unsigned char bg) {
    return (bg << 4) + fg;
}

void vga_set_char_colored(unsigned offset, char c, unsigned char color) {
    video_memory[2 * offset] = c;
    video_memory[2 * offset + 1] = my_get_color(color, black);
}

static unsigned iter;

void print_tree(const char* s) {

    unsigned offset = 0;

    unsigned char balls_colors[] = {magenta, yellow, blue};

    while(*s != 0) {
        if (*s == '\n') {
            offset = COLS * ((offset / COLS) + 1);
        } else {
            unsigned char color = brown;
            if (*s == '(' || *s == ')') {
                color = balls_colors[iter % sizeof(balls_colors)];
            } else if (*s == '#') {
                color = green;
            } else if (*s == 'z' || *s == 'r') {
                color = red;
            }

            vga_set_char_colored(offset, *s, color);
            ++offset;
        }

        ++s;
    }
    ++iter;

}

void show_vga_symbol_table(void) {
    const char* trees_order[] = {tree1, tree2, tree3, tree2};
    my_vga_clear_screen();

    print_tree(trees_order[iter % 4]);

}
