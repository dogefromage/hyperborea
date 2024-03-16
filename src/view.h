#pragma once
#include <curses.h>

#include <memory>
#include <string>
#include <vector>

struct Action {
    int character;
    std::string name;
    void (*dispatch)();
};

class View {
   public:
    virtual ~View() = default;
    std::vector<Action> actions;
    virtual void update() = 0;
    virtual void draw(WINDOW* win) const = 0;
};