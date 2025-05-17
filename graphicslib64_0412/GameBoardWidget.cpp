#include "GameBoardWidget.hpp"
#include "graphics.hpp"
using namespace genv;

GameBoardWidget::GameBoardWidget(int x, int y , int sx, int sy, JatekMester& game, bool computer_opponent)
    : Widget(x, y, sx, sy), game(game), computer_opponent(computer_opponent) {}

void GameBoardWidget::draw() {
    int cell_size = _size_x / 15;
    gout << move_to(_x, _y) << color(0, 0, 0) << box(_size_x, _size_y);
    for (int r = 0; r < 15; r++) {
        for (int c = 0; c < 15; c++) {
            int px = _x + c * cell_size, py = _y + r * cell_size;
            gout << move_to(px, py) << color(255, 255, 255) << box(cell_size - 1, cell_size - 1);
            if (game.get_cell(r, c) == JatekMester::X) {
                gout << move_to(px + 5, py + cell_size - 5) << color(255, 0, 0) << text("X");
            } else if (game.get_cell(r, c) == JatekMester::O) {
                gout << move_to(px + 5, py + cell_size - 5) << color(0, 0, 255) << text("O");
            }
        }
    }
}

void GameBoardWidget::handle(genv::event ev) {
    if (ev.type == ev_mouse && ev.button == btn_left && game.get_state() == JatekMester::RUNNING) {
        int cell_size = _size_x / 15;
        int row = (ev.pos_y - _y) / cell_size;
        int col = (ev.pos_x - _x) / cell_size;
        if (game.make_move(row, col) && computer_opponent && game.get_state() == JatekMester::RUNNING) {
            game.make_computer_move();
        }
    }
}

std::string GameBoardWidget::get_value() const { return game.get_status_message(); }
