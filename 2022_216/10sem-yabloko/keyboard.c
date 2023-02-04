// документация: https://wiki.osdev.org/PS2_Keyboard


#include "keyboard.h"
#include "../cpu/isr.h"
#include "../console.h"
#include "port.h"
#include "../lib/mem.h"
#include "vga.h"

static const char sc_ascii[] = {
    '?', '?', '1', '2', '3', '4', '5', '6',
    '7', '8', '9', '0', '-', '=', '?', '?', 'q', 'w', 'e', 'r', 't', 'y',
    'u', 'i', 'o', 'p', '[', ']', '\n', '?', 'a', 's', 'd', 'f', 'g',
    'h', 'j', 'k', 'l', ';', '\'', '`', '?', '\\', 'z', 'x', 'c', 'v',
    'b', 'n', 'm', ',', '.', '/', '?', '?', '?', ' ',
};

static const char sc_ascii_shift[] = {
  '?',   '?',  '!',  '@',  '#',  '$',  '%',  '^',  // 0x00
  '&',  '*',  '(',  ')',  '_',  '+',  '\b', '\t',
  'Q',  'W',  'E',  'R',  'T',  'Y',  'U',  'I',  // 0x10
  'O',  'P',  '{',  '}',  '\n', '?',   'A',  'S',
  'D',  'F',  'G',  'H',  'J',  'K',  'L',  ':',  // 0x20
  '"',  '~',  '?',   '|',  'Z',  'X',  'C',  'V',
  'B',  'N',  'M',  '<',  '>',  '?',  '?',   '*',  // 0x30
  '?',   ' ',  '?',   '?',   '?',   '?',   '?',   '?',
  '?',   '?',   '?',   '?',   '?',   '?',   '?',   '7',  // 0x40
  '8',  '9',  '-',  '4',  '5',  '6',  '+',  '1',
  '2',  '3',  '0',  '.',  '?',   '?',   '?',   '?',   // 0x50
};

enum { kbd_buf_capacity = 1024 };


static unsigned shift_pressed;

static void interrupt_handler(registers_t *r) {
    uint8_t scancode = port_byte_in(0x60);
    // зажали левый или праваый шифт
    if (scancode == 0x2A || scancode == 0x36) {
        shift_pressed = 1;
        return;
    }

    // отпустили левый или правый шифт
    if (scancode == 0xAA || scancode == 0xB6) {
        shift_pressed = 0;
        return;
    }

    // нажали backspace -> очистим экран (не очень красиво, но что есть)
    if (scancode == 0x0E) {
        vga_clear_screen();
        return;
    }

    if (scancode < sizeof(sc_ascii)) {
        char c;
        // Если шифт был нажат, но не был отпущен, то печатаем символы из тамблички
        // с зажатым шифтом, иначе из обычной таблички
        if (shift_pressed) {
            c = sc_ascii_shift[scancode];
        } else {
            c = sc_ascii[scancode];
        }
        if (kbd_buf_size < kbd_buf_capacity) {
            kbd_buf[kbd_buf_size++] = c;
        }
        char string[] = {c, '\0'};
        printk(string);
    }
}

char* kbd_buf;
unsigned kbd_buf_size;

// Не забудьте вызвать эту функцию в kernel.c
void init_keyboard() {
    kbd_buf = kmalloc(kbd_buf_capacity);

    register_interrupt_handler(IRQ1, interrupt_handler);
}
