#include <ncurses.h>

#include <algorithm>
#include <cstring>
#include <string>

#include "project.h"

void format_name(char* target, int targetSize, std::string name) {
    memset(target, ' ', targetSize);
    memcpy(target, name.c_str(), std::min(targetSize, (int)name.length()));

    if ((int)name.length() > targetSize) {
        for (int i = targetSize - 1; i >= 0 && i >= targetSize - 3; i--) {
            target[i] = '.';
        }
    }
}

void draw_track_view(WINDOW* win) {
    const int trackViewWidth = 36;
    const int maxNameWidth = trackViewWidth - 15;

    int width, height;
    getmaxyx(win, height, width);

    // draw heading
    wmove(win, 0, 0);
    wattron(win, A_REVERSE | A_BOLD);
    wprintw(win, "%-*s%-*s", trackViewWidth, " Tracks ", width - trackViewWidth, "| Items ");
    wattroff(win, A_REVERSE | A_BOLD);

    char formattedName[maxNameWidth];

    for (int y = 1; y < height - 1; y++) {
        wmove(win, y, 1);

        int track_index = y - 1;
        if (0 <= track_index && track_index < (int)gProject.tracks.size()) {
            Track& track = gProject.tracks[track_index];
            format_name(formattedName, maxNameWidth, track.name);

            wprintw(win, "%2d ", track_index + 1);
            wattron(win, A_BOLD);
            wprintw(win, "[ %.*s ] ", maxNameWidth, formattedName);
            wattroff(win, A_BOLD);

            wattron(win, A_DIM);
            wprintw(win, "CH %2d", track.midiChannel);
            wattroff(win, A_DIM);
        } else {
            wattron(win, A_DIM);
            wprintw(win, " .");
            wattroff(win, A_DIM);
        }
    }

    wrefresh(win);
}

int main(int argc, char* argv[]) {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);

    init_project();

    WINDOW* track_view = newwin(30, 80, 5, 10);
    refresh();

    box(track_view, 0, 0);
    draw_track_view(track_view);

    // refresh();
    getch();
    endwin();

    return 0;
}