#pragma once
#include "view.h"

enum class TrackProperty {
    None,
    Channel,
    Name,
};

class TrackPropertiesView : public View {
   public:
    void input(WINDOW* win) override;
    void draw(WINDOW* win) override;

    int activeTrack = -1;
    TrackProperty targetProperty = TrackProperty::None;
};