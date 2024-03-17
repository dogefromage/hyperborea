#pragma once
#include <cassert>
#include <unordered_map>

#include "view.h"

extern bool isRunning;

enum class Views {
    TrackOutliner,
    TrackProperties,
};

void app_draw_current_view(WINDOW* win);
void app_init();
void change_view(Views view);
bool dispatch_global_actions(int input);
View& get_view(Views viewType);

void app_draw_and_get_input(WINDOW* win);

std::unordered_map<Views, std::shared_ptr<View>>& get_views();

template <typename T>
inline std::shared_ptr<T> get_extended_view(Views viewType) {
    auto& views = get_views();
    assert(views.contains(viewType) && "View not found.");
    return std::static_pointer_cast<T>(views[viewType]);
}
