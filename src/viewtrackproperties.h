#pragma once
#include "view.h"

class TrackPropertiesView : public View {
   public:
    void update() override;
    void draw(WINDOW* win) const override;

    int activeTrack = -1;
};