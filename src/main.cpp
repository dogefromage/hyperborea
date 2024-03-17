#include <ncurses.h>

#include <algorithm>
#include <cstring>
#include <string>

#include "app.h"
#include "color.h"
#include "project.h"

int main(int argc, char* argv[]) {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);

    color_init();
    init_project();
    app_init();

    int w, h;
    getmaxyx(stdscr, h, w);
    WINDOW* win_toolbar = newwin(1, w, 0, 0);
    WINDOW* win_views = newwin(h - 2, w, 1, 0);
    WINDOW* win_input = newwin(1, w - 2, h - 1, 1);
    refresh();

    wsetcolor(win_toolbar, COLOR_WHITE, COLOR_MAGENTA);
    wprintw(win_toolbar, " -- Hyperborea -- ");
    wclrtoeol(win_toolbar);
    wrefresh(win_toolbar);

    wsetcolor(win_input, COLOR_MAGENTA | COLOR_INTENSITY, COLOR_BLACK);

    while (isRunning) {
        app_draw_current_view(win_views);
        app_draw_and_get_input(win_input);
    }

    getch();

    delwin(win_toolbar);
    delwin(win_views);
    delwin(win_input);

    endwin();
    return 0;
}