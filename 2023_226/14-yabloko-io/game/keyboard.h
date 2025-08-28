#pragma once

void init_keyboard();
void kb_reset();

extern char up_pressed;
extern char down_pressed;
extern char left_pressed;
extern char right_pressed;

extern unsigned kbd_buf_size;
extern char *kbd_buf;
