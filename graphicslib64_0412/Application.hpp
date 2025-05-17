#ifndef APPLICATION_HPP_INCLUDED
#define APPLICATION_HPP_INCLUDED

#include "widgets.hpp"
#include "GameBoardWidget.hpp"
#include "DropdownSelector.hpp"
#include "ButtonWidget.hpp"
#include "JatekMester.hpp"
#include <vector>

class Application {
    std::vector<Widget*> widgets;
    JatekMester* game;
    int focus;
    bool in_menu;
    bool computer_opponent;


    void start_game(bool computer);
    void reset_game();
    void return_to_menu();

public:
    Application();
    ~Application();
    void run();
    void draw_instructions();
    void handle_event(genv::event ev);
};

#endif // APPLICATION_HPP_INCLUDED
