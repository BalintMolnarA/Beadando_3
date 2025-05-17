#include "JatekMester.hpp"
#include <random>

JatekMester::JatekMester(int size) : size(size), current_player(X), state(RUNNING) {
    if (size < 15 || size > 30) size = 15;
    board.assign(size, std::vector<Cell>(size, EMPTY));
}

bool JatekMester::make_move(int row, int col) {
    if (state != RUNNING || !is_valid_move(row, col)) return false;
    board[row][col] = current_player;
    if (check_win(current_player, row, col)) {
        state = (current_player == X) ? X_WON : O_WON;
    } else if (is_board_full()) {
        state = DRAW;
    } else {
        switch_player();
    }
    return true;
}

bool JatekMester::make_computer_move() {
    return false;
}

JatekMester::GameState JatekMester::get_state() const { return state; }
JatekMester::Cell JatekMester::get_cell(int row, int col) const { return board[row][col]; }
JatekMester::Cell JatekMester::get_current_player() const { return current_player; }

std::string JatekMester::get_status_message() const {
    switch (state) {
        case X_WON: return "X nyert!";
        case O_WON: return "O nyert!";
        case DRAW: return "Dontetlen!";
        default: return std::string(current_player == X ? "X" : "O") + " kovetkezik";
    }
}

void JatekMester::switch_player() {
    current_player = (current_player == X) ? O : X;
}

bool JatekMester::is_valid_move(int row, int col) const {
    return row >= 0 && row < size && col >= 0 && col < size && board[row][col] == EMPTY;
}

bool JatekMester::check_win(Cell player, int row, int col) const {
    auto count = [&](int dr, int dc) {
        int r = row, c = col, count = 0;
        while (r >= 0 && r < size && c >= 0 && c < size && board[r][c] == player) {
            count++; r += dr; c += dc;
        }
        return count;
    };
    for (auto [dr, dc] : std::vector<std::pair<int, int>>{{0, 1}, {1, 0}, {1, 1}, {1, -1}}) {
        if (count(dr, dc) + count(-dr, -dc) - 1 >= 5) return true;
    }
    return false;
}

bool JatekMester::is_board_full() const {
    for (const auto& row : board) {
        for (const auto& cell : row) {
            if (cell == EMPTY) return false;
        }
    }
    return true;
}

std::pair<int, int> JatekMester::find_best_move() const {
    return {-1, -1};
}
