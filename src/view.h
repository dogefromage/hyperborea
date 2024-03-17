#pragma once
#include <ncurses.h>

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
    virtual void input(WINDOW* win) = 0;
    virtual void draw(WINDOW* win) = 0;
};