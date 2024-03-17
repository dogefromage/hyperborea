#pragma once

#define COLOR_INTENSITY 8

void color_init(void);
void wsetcolor(WINDOW* win, int fg, int bg);
void wunsetcolor(WINDOW* win, int fg, int bg);