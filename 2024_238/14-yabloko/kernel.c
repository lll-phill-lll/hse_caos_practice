#include "console.h"
#include "cpu/isr.h"
#include "cpu/gdt.h"
#include "cpu/memlayout.h"
#include "drivers/keyboard.h"
#include "drivers/vga.h"
#include "drivers/ata.h"
#include "drivers/misc.h"
#include "drivers/pit.h"
#include "drivers/uart.h"
#include "fs/fs.h"
#include "lib/string.h"
#include "proc.h"
#include "kernel/mem.h"

#include "animation.h"


int player_row = ROWS - 1;
int player_col = COLS / 2;

void update_pos() {
    if (down_pressed) {
        player_row++;
        if (player_row >= ROWS) player_row = 0;
    } else if (up_pressed) {
        player_row--;
        if (player_row < 0) player_row = ROWS - 1;
    } else if (left_pressed) {
        player_col--;
        if (player_col < 0) player_col = COLS - 1;
    } else if (right_pressed) {
        player_col++;
        if (player_col >= COLS) player_col = 0;
    }
    reset_kb();
}

void kmain() {
    freerange(P2V(1u<<20), P2V(2u<<20)); // 1MB - 2MB
    kvmalloc();  // map all of physical memory at KERNBASE
    freerange(P2V(2u<<20), P2V(PHYSTOP));

    load_gdt();
    init_keyboard();
    init_pit();
    uartinit();
    load_idt();
    sti();

    vga_clear_screen();
    printk("YABLOKO\n");

    printk("\n> ");
    while (1) {
        msleep(100);

        update_pos();
        vga_clear_screen();
        vga_set_char2(player_col, player_row, '@');
    }
}
