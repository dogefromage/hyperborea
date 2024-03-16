#include <ncurses.h>

#include <algorithm>
#include <cstring>
#include <string>

#include "app.h"
#include "project.h"

int main(int argc, char* argv[]) {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);
    if (!has_colors()) {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }

    init_project();
    app_init();

    while (isRunning) {
        app_draw_current_view(stdscr);
        app_update();
    }

    endwin();
    return 0;
}