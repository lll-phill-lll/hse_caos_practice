#include "console.h"
#include "drivers/vga.h"
#include "drivers/uart.h"
#include "drivers/misc.h"

void show_vga_symbol_table(void);


void wait(unsigned ms) {
    for (int i = 0; i < 10000 * ms; i++) {
        asm("pause");
    }
}

void _start() {
    uartinit();

    while (1) {
        show_vga_symbol_table();
        wait(300);
    }
    qemu_shutdown();
}
