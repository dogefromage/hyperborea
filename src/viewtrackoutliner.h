#pragma once
#include "view.h"

class TrackOutlinerView : public View {
   public:
    void input(WINDOW* win) override;
    void draw(WINDOW* win) override;
    int activeTrack = -1;
};