asm(".asciz \"kernel start\\n\"");

#include "console.h"
#include "cpu/isr.h"
#include "cpu/gdt.h"
#include "drivers/keyboard.h"
#include "drivers/vga.h"
#include "drivers/ata.h"
#include "drivers/misc.h"
#include "drivers/uart.h"
#include "fs/fs.h"
#include "lib/string.h"
#include "lib/mem.h"
#include "proc.h"

void wait(unsigned ms) {
    for (int i = 0; i < 10000 * ms; i++) {
        asm("pause");
    }
}

int max_obstacles = 1024;
int obstacles_count = 0;
int* obstacles_rows;
int* obstacles_cols;

int player_row = ROWS - 1;
int player_col = COLS / 2;


unsigned my_get_offset(unsigned col, unsigned row) {
    return row * COLS + col;
}

void process_input() {
    if (right_pressed) {
        player_col += 1;
        if (player_col == COLS) player_col = 0;
    } else if (left_pressed) {
        player_col -= 1;
        if (player_col == -1) player_col = COLS - 1;
    } else if (up_pressed) {
        player_row -= 1;
        if (player_row == -1) player_row = ROWS - 1;
    } else if (down_pressed) {
        player_row += 1;
        if (player_row == ROWS) player_row = 0;
    }
    kb_reset();
}

void render_player() {
    vga_set_char(my_get_offset(player_col, player_row), '0');
}

int seed = 123;

void create_obstacle() {
    obstacles_rows[obstacles_count] = 0;
    seed = (seed * 19937 + 1009) % COLS;
    obstacles_cols[obstacles_count] = seed;
    ++obstacles_count;
}

void process_obstacle() {
    for (int i = 0; i < obstacles_count; ++i) {
        obstacles_rows[i]++;
        if (obstacles_rows[i] == ROWS) {
            obstacles_rows[i] = 0;
        }
    }
}

void render_obstacles() {
    for (int i = 0; i < obstacles_count; ++i) {
        vga_set_char(my_get_offset(obstacles_cols[i], obstacles_rows[i]), 'x');
    }
}

int tick = 0;

void _start() {
    load_gdt();
    init_keyboard();
    uartinit();
    load_idt();
    sti();

    obstacles_rows = kmalloc(max_obstacles * sizeof(int));
    obstacles_cols = kmalloc(max_obstacles * sizeof(int));

    while (1) {
        wait(100);
        vga_clear_screen();

        if (tick % 150) create_obstacle();
        if (tick % 100) process_obstacle();

        process_input();
        render_player();
        render_obstacles();

        // if (check_collisions()) {
        //     printk("\n\n\n\n\nFAIL\n\n\n");
        //     asm("hlt");

        // }
        ++tick;
    }
}
