#include <ncurses.h>
#include <stdlib.h>

short curs_color(int fg) {
    switch (7 & fg) { /* RGB */
        case 0:       /* 000 */
            return (COLOR_BLACK);
        case 1: /* 001 */
            return (COLOR_RED);
        case 2: /* 010 */
            return (COLOR_GREEN);
        case 3: /* 011 */
            return (COLOR_YELLOW);
        case 4: /* 100 */
            return (COLOR_BLUE);
        case 5: /* 101 */
            return (COLOR_MAGENTA);
        case 6: /* 110 */
            return (COLOR_CYAN);
        case 7: /* 111 */
            return (COLOR_WHITE);
    }
    return ERR;
}

int colornum(int fg, int bg) {
    int B, bbb, ffff;

    B = 1 << 7;
    bbb = (7 & bg) << 4;
    ffff = 7 & fg;

    return (B | bbb | ffff);
}

void color_init(void) {
    if (!has_colors()) {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }
    start_color();
    int fg, bg;
    int colorpair;
    for (bg = 0; bg <= 7; bg++) {
        for (fg = 0; fg <= 7; fg++) {
            colorpair = colornum(fg, bg);
            init_pair(colorpair, curs_color(fg), curs_color(bg));
        }
    }
}

int is_bold(int fg) {
    /* return the intensity bit */
    int i;
    i = 1 << 3;
    return (i & fg);
}

void wsetcolor(WINDOW* win, int fg, int bg) {
    /* set the color pair (colornum) and bold/bright (A_BOLD) */
    wattron(win, COLOR_PAIR(colornum(fg, bg)));
    if (is_bold(fg)) {
        wattron(win, A_BOLD);
    }
}

void wunsetcolor(WINDOW* win, int fg, int bg) {
    /* unset the color pair (colornum) and
       bold/bright (A_BOLD) */

    wattroff(win, COLOR_PAIR(colornum(fg, bg)));
    if (is_bold(fg)) {
        wattroff(win, A_BOLD);
    }
}
