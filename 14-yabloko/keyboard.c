#include "keyboard.h"
#include "cpu/isr.h"
#include "cpu/memlayout.h"
#include "console.h"
#include "port.h"
#include "kernel/mem.h"

static const char sc_ascii[] = {
    '?', '?', '1', '2', '3', '4', '5', '6',
    '7', '8', '9', '0', '-', '=', '?', '?', 'q', 'w', 'e', 'r', 't', 'y',
    'u', 'i', 'o', 'p', '[', ']', '\n', '?', 'a', 's', 'd', 'f', 'g',
    'h', 'j', 'k', 'l', ';', '\'', '`', '?', '\\', 'z', 'x', 'c', 'v',
    'b', 'n', 'm', ',', '.', '/', '?', '?', '?', ' ',
};

enum { kbd_buf_capacity = PGSIZE };

int left_pressed = 0;
int right_pressed = 0;
int up_pressed = 0;
int down_pressed = 0;

void reset_kb() {
    left_pressed = 0;
    right_pressed = 0;
    up_pressed = 0;
    down_pressed = 0;
}

static void interrupt_handler(registers_t *r) {
    uint8_t scancode = port_byte_in(0x60);
    if (scancode < sizeof(sc_ascii)) {
        char c = sc_ascii[scancode];
        if (c == 'j') down_pressed = 1;
        else if (c == 'k') up_pressed = 1;
        else if (c == 'h') left_pressed = 1;
        else if (c == 'l') right_pressed = 1;
    }
}

char* kbd_buf;
unsigned kbd_buf_size;

void init_keyboard() {
    kbd_buf = kalloc();

    register_interrupt_handler(IRQ1, interrupt_handler);
}
