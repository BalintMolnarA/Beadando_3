#ifndef JATEK_MESTER_HPP_INCLUDED
#define JATEK_MESTER_HPP_INCLUDED

#include <vector>
#include <string>

class JatekMester {
public:
    enum Cell { EMPTY, X, O };
    enum GameState { RUNNING, X_WON, O_WON, DRAW };

    JatekMester(int size = 15);
    bool make_move(int row, int col);
    bool make_computer_move();
    GameState get_state() const;
    Cell get_cell(int row, int col) const;
    Cell get_current_player() const;
    std::string get_status_message() const;

private:
    int size;
    std::vector<std::vector<Cell>> board;
    Cell current_player;
    GameState state;

    void switch_player();
    bool is_valid_move(int row, int col) const;
    bool check_win(Cell player, int row, int col) const;
    bool is_board_full() const;
    std::pair<int, int> find_best_move() const;
};

#endif // JATEK_MESTER_HPP_INCLUDED
