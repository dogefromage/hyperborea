#include "viewtrackoutliner.h"

#include <string.h>

#include "app.h"
#include "project.h"
#include "viewtrackproperties.h"

static void format_name(char* target, int targetSize, std::string name) {
    memset(target, ' ', targetSize);
    memcpy(target, name.c_str(), std::min(targetSize, (int)name.length()));

    if ((int)name.length() > targetSize) {
        for (int i = targetSize - 1; i >= 0 && i >= targetSize - 3; i--) {
            target[i] = '.';
        }
    }
}

int number_input(WINDOW* win) {
    int n = 0;
    while (true) {
        int input = getch();
        wprintw(win, "%c", input);
        wrefresh(win);
        if (input >= '0' && input <= '9') {
            n = 10 * n + input - '0';
        } else {
            break;
        }
    }
    return n;
}

int track_number_input(WINDOW* win) {
    wmove(win, 0, 0);
    wclrtoeol(win);
    mvwprintw(win, 0, 0, "enter track number... ");
    wrefresh(win);
    int track_num = number_input(win);

    int track_count = gProject.tracks.size();
    if (0 <= track_num && track_num < track_count) {
        return track_num;
    } else {
        mvwprintw(win, 0, 0, "invalid track number: %d", track_num);
        wclrtoeol(win);
        wrefresh(win);
        getch();
        return -1;
    }
}

void TrackOutlinerView::input(WINDOW* win) {
    mvwprintw(win, 0, 0, "[s] select track [i] inspect ");
    wrefresh(win);

    int input = getch();

    switch (input) {
        case 's': {
            int track = track_number_input(win);
            if (track >= 0) {
                activeTrack = track;
            }
            return;
        }
        case KEY_UP:
            activeTrack--;
            while (activeTrack < 0) {
                activeTrack += gProject.track_count();
            }
            return;
        case KEY_DOWN:
            ++activeTrack %= gProject.track_count();
            return;
        case 'i': {
            std::shared_ptr<TrackPropertiesView> tp = get_extended_view<TrackPropertiesView>(Views::TrackProperties);
            tp->activeTrack = activeTrack; // set inspector track
            change_view(Views::TrackProperties);
            return;
        }
    }
}

void TrackOutlinerView::draw(WINDOW* win) {
    wclear(win);

    const int trackViewWidth = 36;
    const int maxNameWidth = trackViewWidth - 15;

    int width, height;
    getmaxyx(win, height, width);

    // draw heading
    wmove(win, 0, 0);
    wattron(win, /* A_REVERSE | */ A_BOLD);
    wprintw(win, "%-*s%-*s", trackViewWidth, " Tracks ", width - trackViewWidth, "| Items ");
    wattroff(win, /* A_REVERSE | */ A_BOLD);

    char formattedName[maxNameWidth];

    for (int y = 1; y < height - 1; y++) {
        wmove(win, y, 1);

        int track_index = y - 1;
        if (0 <= track_index && track_index < (int)gProject.tracks.size()) {
            Track& track = gProject.tracks[track_index];
            format_name(formattedName, maxNameWidth, track.name);

            if (activeTrack == track_index) {
                wattron(win, A_REVERSE);
            }
            wprintw(win, "%2d ", track_index);
            wattroff(win, A_REVERSE);

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