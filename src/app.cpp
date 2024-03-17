#include "app.h"

#include <memory>

#include "viewtrackoutliner.h"
#include "viewtrackproperties.h"

static std::unordered_map<Views, std::shared_ptr<View>> views;

static Views currentViewType;
static std::vector<Action> globalActions;

bool isRunning = true;

static void action_close_app() {
    isRunning = false;
}

void app_init() {
    currentViewType = Views::TrackOutliner;

    views.insert({Views::TrackOutliner, std::make_shared<TrackOutlinerView>()});
    views.insert({Views::TrackProperties, std::make_shared<TrackPropertiesView>()});

    globalActions.push_back({27, "Test", action_close_app});
}

View& get_view(Views viewType) {
    assert(views.contains(viewType) && "View not found.");
    return *views[currentViewType];
}

void app_draw_current_view(WINDOW* win) {
    View& view = get_view(currentViewType);
    view.draw(win);
}

void change_view(Views viewType) {
    currentViewType = viewType;
}

bool dispatch_global_actions(int input) {
    for (const Action& action : globalActions) {
        if (input == action.character) {
            action.dispatch();
            return true;
        }
    }
    return false;
}

void app_draw_and_get_input(WINDOW* win) {
    View& view = get_view(currentViewType);
    view.input(win);
}

std::unordered_map<Views, std::shared_ptr<View>>& get_views() {
    return views;
}
