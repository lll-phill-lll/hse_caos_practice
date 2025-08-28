#pragma once

void init_keyboard();

extern unsigned kbd_buf_size;
extern char *kbd_buf;

extern int left_pressed;
extern int right_pressed;
extern int up_pressed;
extern int down_pressed;

void reset_kb();
