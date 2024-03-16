#include "viewtrackoutliner.h"

#include <string.h>

#include "project.h"
#include "app.h"
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

void TrackOutlinerView::update() {
    int selectedTrackLabel = -1;
    while (true) {
        int input = getch();
        
        if (input >= '0' && input <= '9') {
            int digit = input - '0';
            if (selectedTrackLabel < 0) {
                selectedTrackLabel = digit;
            } else {
                selectedTrackLabel = 10 * selectedTrackLabel + digit;
            }
            continue;
        }

        if (input == 'i') {
            if (selectedTrackLabel > 0) {
                View* uncast_tp = &get_view(Views::TrackProperties);
                TrackPropertiesView* tp = dynamic_cast<TrackPropertiesView*>(uncast_tp);
                tp->activeTrack = selectedTrackLabel - 1;
                return;
            }
        }

        if (dispatch_global_actions(input)) {
            return;
        }
    }
}

void TrackOutlinerView::draw(WINDOW* win) const {
    wclear(win);
    
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

            // if (activeTrack == track_index) {
            //     wattron(win, A_REVERSE);
            // }
            wprintw(win, "%2d ", track_index + 1);
            // wattroff(win, A_REVERSE);


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