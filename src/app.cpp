#include "app.h"

#include <cassert>
#include <memory>
#include <unordered_map>

#include "viewtrackoutliner.h"
#include "viewtrackproperties.h"

static std::unordered_map<Views, std::shared_ptr<View>> views;
static Views currentViewType;
static std::vector<Action> globalActions;

bool isRunning = true;

static void action_close_app() {
    isRunning = false;
}

void app_update() {
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

void app_init() {
    View& view = get_view(currentViewType);
    view.update();
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

void draw_input_line(WINDOW* win) {
    wmove(win, 0, 0);
}