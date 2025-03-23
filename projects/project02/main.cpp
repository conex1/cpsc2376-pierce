#include <iostream>
#include "game.h"

int main() {
    Game game;

    while (game.status() == Game::ONGOING) {
        std::cout << game << std::endl;

        int currentPlayer = (game.currentPlayer() == Game::PLAYER_1) ? 1 : 2;
        std::cout << "Player " << currentPlayer << ", enter column (0-6): ";
        int column;
        std::cin >> column;

        game.play(column);
    }

    std::cout << game << std::endl;

    switch (game.status()) {
        case Game::PLAYER_1_WINS:
            std::cout << "Player 1 wins!" << std::endl;
            break;
        case Game::PLAYER_2_WINS:
            std::cout << "Player 2 wins!" << std::endl;
            break;
        case Game::DRAW:
            std::cout << "It's a draw!" << std::endl;
            break;
        default:
            break;
    }

    return 0;
}