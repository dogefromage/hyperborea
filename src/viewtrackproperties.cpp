#include "viewtrackproperties.h"

void TrackPropertiesView::update() {
}

void TrackPropertiesView::draw(WINDOW* win) const {
    wclear(win);
    wmove(win, 1, 1);
    wprintw(win, "Inspecting track: %d", activeTrack);
    wrefresh(win);
}