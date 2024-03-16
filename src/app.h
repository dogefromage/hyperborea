#pragma once
#include "view.h"

extern bool isRunning;

enum class Views {
    TrackOutliner,
    TrackProperties,
};

void app_draw_current_view(WINDOW* win);
void app_init();
void app_update();
void change_view(Views view);
bool dispatch_global_actions(int input);
View& get_view(Views viewType);

void draw_input_line(WINDOW* win);