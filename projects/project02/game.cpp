#include "game.h"
#include <vector>

Game::Game() : board(ROWS, std::vector<Cell>(COLS, EMPTY)), 
               gameStatus(ONGOING), 
               currentPlayer_(PLAYER_1),
               lastRow(-1),
               lastCol(-1) {}

void Game::play(int column) {
    if (gameStatus != ONGOING) return;

    if (column < 0 || column >= COLS) return;

    int row = -1;
    for (int r = ROWS - 1; r >= 0; --r) {
        if (board[r][column] == EMPTY) {
            row = r;
            break;
        }
    }

    if (row == -1) return;

    board[row][column] = currentPlayer_;
    lastRow = row;
    lastCol = column;

    if (checkWin(currentPlayer_)) {
        gameStatus = (currentPlayer_ == PLAYER_1) ? PLAYER_1_WINS : PLAYER_2_WINS;
    } else if (checkDraw()) {
        gameStatus = DRAW;
    } else {
        currentPlayer_ = (currentPlayer_ == PLAYER_1) ? PLAYER_2 : PLAYER_1;
    }
}

bool Game::checkWin(Cell player) const {
    int count = 1;

    int c = lastCol - 1;
    while (c >= 0 && board[lastRow][c] == player) {
        count++;
        c--;
    }
    c = lastCol + 1;
    while (c < COLS && board[lastRow][c] == player) {
        count++;
        c++;
    }
    if (count >= 4) return true;

    count = 1;
    int r = lastRow - 1;
    while (r >= 0 && board[r][lastCol] == player) {
        count++;
        r--;
    }
    r = lastRow + 1;
    while (r < ROWS && board[r][lastCol] == player) {
        count++;
        r++;
    }
    if (count >= 4) return true;

    count = 1;
    r = lastRow - 1;
    c = lastCol - 1;
    while (r >= 0 && c >= 0 && board[r][c] == player) {
        count++;
        r--;
        c--;
    }
    r = lastRow + 1;
    c = lastCol + 1;
    while (r < ROWS && c < COLS && board[r][c] == player) {
        count++;
        r++;
        c++;
    }
    if (count >= 4) return true;

    count = 1;
    r = lastRow - 1;
    c = lastCol + 1;
    while (r >= 0 && c < COLS && board[r][c] == player) {
        count++;
        r--;
        c++;
    }
    r = lastRow + 1;
    c = lastCol - 1;
    while (r < ROWS && c >= 0 && board[r][c] == player) {
        count++;
        r++;
        c--;
    }
    if (count >= 4) return true;

    return false;
}

bool Game::checkDraw() const {
    for (int c = 0; c < COLS; ++c) {
        if (board[0][c] == EMPTY) {
            return false;
        }
    }
    return true;
}

std::ostream& operator<<(std::ostream& os, const Game& game) {
    for (int r = 0; r < Game::ROWS; ++r) {
        os << "|";
        for (int c = 0; c < Game::COLS; ++c) {
            switch (game.board[r][c]) {
                case Game::EMPTY: os << " "; break;
                case Game::PLAYER_1: os << "X"; break;
                case Game::PLAYER_2: os << "O"; break;
            }
            os << "|";
        }
        os << std::endl;
    }
    os << " ";
    for (int c = 0; c < Game::COLS; ++c) {
        os << c << " ";
    }
    os << std::endl;
    return os;
}