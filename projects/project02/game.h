#ifndef GAME_H
#define GAME_H

#include <vector>
#include <iostream>

class Game {
public:
    enum Status { ONGOING, PLAYER_1_WINS, PLAYER_2_WINS, DRAW };
    enum Cell { EMPTY, PLAYER_1, PLAYER_2 };

    Game();

    void play(int column);
    Status status() const { return gameStatus; }
    Cell currentPlayer() const { return currentPlayer_; }

    friend std::ostream& operator<<(std::ostream& os, const Game& game);

private:
    static const int ROWS = 6;
    static const int COLS = 7;
    std::vector<std::vector<Cell>> board;
    Status gameStatus;
    Cell currentPlayer_;
    int lastRow;
    int lastCol;

    bool checkWin(Cell player) const;
    bool checkDraw() const;
};

#endif // GAME_H