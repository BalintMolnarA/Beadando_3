#ifndef GAME_BOARD_WIDGET_HPP_INCLUDED
#define GAME_BOARD_WIDGET_HPP_INCLUDED

#include "widgets.hpp"
#include "JatekMester.hpp"

class GameBoardWidget : public Widget {
    JatekMester& game;
    bool computer_opponent;

public:
    GameBoardWidget(int x, int y, int sx, int sy, JatekMester& game, bool computer_opponent);
    void draw() override;
    void handle(genv::event ev) override;
    std::string get_value() const override;
};

#endif // GAME_BOARD_WIDGET_HPP_INCLUDED
