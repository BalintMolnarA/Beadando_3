#ifndef APPLICATION_HPP_INCLUDED
#define APPLICATION_HPP_INCLUDED

#include "widgets.hpp"
#include "DropdownSelector.hpp"
#include "ButtonWidget.hpp"
#include <vector>

class Application {
    std::vector<Widget*> widgets;
    int focus;
    bool in_menu;

public:
    Application();
    ~Application();
    void run();
    void draw_instructions();
    void handle_event(genv::event ev);
};

#endif // APPLICATION_HPP_INCLUDED
