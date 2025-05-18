#include "JatekMester.hpp"
#include <random>
#include <algorithm>

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
    if (state != RUNNING || current_player != O) return false;
    auto [row, col] = find_best_move();
    return make_move(row, col);
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
    std::vector<std::pair<int, int>> empty_cells;
    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            if (board[r][c] == EMPTY) empty_cells.emplace_back(r, c);
        }
    }

    auto check_potential_win = [&](Cell player) {
        for (auto [r, c] : empty_cells) {
            JatekMester temp = *this;
            temp.board[r][c] = player;
            if (temp.check_win(player,r,c)) return std::make_pair(r, c);
        }
        return std::make_pair(-1,-1);
    };
    auto win = check_potential_win(O);
    if (win.first != -1) return win;

    auto block = check_potential_win(X);
    if (block.first != -1) return block;

    auto check_three_in_a_row = [&](Cell player) {
        for (int r = 0; r < size; r++) {
            for (int c = 0; c < size; c++) {
                if (board[r][c] != player) continue;
                for (auto [dr, dc] : std::vector<std::pair<int, int>>{{0, 1}, {1, 0}, {1, 1}, {1, -1}}) {
                    int count_forward = 1;
                    int r_forward = r + dr, c_forward = c + dc;
                    while (r_forward >= 0 && r_forward < size && c_forward >= 0 && c_forward < size &&
                           board[r_forward][c_forward] == player) {
                        count_forward++;
                        r_forward += dr;
                        c_forward += dc;
                    }
                    int count_backward = 0;
                    int r_backward = r - dr, c_backward = c - dc;
                    while (r_backward >= 0 && r_backward < size && c_backward >= 0 && c_backward < size &&
                            board[r_backward][c_backward] == player) {
                        count_backward++;
                        r_backward -= dr;
                        c_backward -= dc;
                    }
                    if (count_forward + count_backward == 3) {
                        if (r_forward >= 0 && r_forward < size && c_forward >= 0 && c_forward < size &&
                            board[r_forward][c_forward] == EMPTY) {
                            return std::make_pair(r_forward, c_forward);
                        }
                        if (r_backward >= 0 && r_backward < size && c_backward >= 0 && c_backward < size &&
                            board[r_backward][c_backward] == EMPTY) {
                            return std::make_pair(r_backward, c_backward);
                        }
                    }
                }
            }
        }
        return std::make_pair(-1, -1);
    };

    auto block_three_x = check_three_in_a_row(X);
    if (block_three_x.first !=-1) return block_three_x;

    auto continue_three_o = check_three_in_a_row(O);
    if (continue_three_o.first !=-1) return continue_three_o;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0,empty_cells.size() - 1);
    return empty_cells[dis(gen)];
}
