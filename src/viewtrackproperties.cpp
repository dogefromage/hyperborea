#include "viewtrackproperties.h"

#include "app.h"
#include "project.h"

void TrackPropertiesView::input(WINDOW* win) {
    mvwprintw(win, 0, 0, "[backspace] back ");
    wclrtoeol(win);
    wrefresh(win);
    int input = getch();

    switch (input) {
        case KEY_BACKSPACE:  // esc
            change_view(Views::TrackOutliner);
            break;
        case 'n':
            targetProperty = TrackProperty::Name;
            break;
        case 'c':
            targetProperty = TrackProperty::Channel;
            break;
    }
}

void TrackPropertiesView::draw(WINDOW* win) {
    if (targetProperty == TrackProperty::None) {
        wclear(win);
    }
    
    box(win, 0, 0);
    if (activeTrack < 0 || gProject.track_count() <= activeTrack) {
        mvwprintw(win, 1, 1, "Unknown track index: %d", activeTrack);
        wrefresh(win);
        return;
    }

    Track& track = gProject.tracks[activeTrack];

    mvwprintw(win, 1, 2, "Track properties of track #%d", activeTrack);

    // properties
    const int column_width = 20;
    int line = 3;

    mvwprintw(win, line, 2, "[n] Name");
    if (targetProperty == TrackProperty::Name) {
        mvwprintw(win, line, column_width, "[ EDIT NAME ]");
        wrefresh(win);
        getch();
        targetProperty = TrackProperty::None;
    } else {
        mvwprintw(win, line, column_width, "[ %s ]", track.name.c_str());
    }

    line += 2;
    mvwprintw(win, line, 2, "[c] Channel");
    if (targetProperty == TrackProperty::Channel) {
        mvwprintw(win, line, column_width, "[ EDIT CHANNEL ]");
        wrefresh(win);
        getch();
        targetProperty = TrackProperty::None;
    } else {
        mvwprintw(win, line, column_width, "[ %2d ]", track.midiChannel);
    }

    wrefresh(win);
}