#pragma once
#include "view.h"

class TrackOutlinerView : public View {
   public:
    void update() override;
    void draw(WINDOW* win) const override;
};