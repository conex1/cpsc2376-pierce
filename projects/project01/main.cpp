#include <iostream>
#include <vector>
#include <limits>

enum class GameState { ONGOING, PLAYER_1_WINS, PLAYER_2_WINS, DRAW };
enum class PlayerToken { EMPTY, P1, P2 };

class ConnectFour {
private:
    const int ROWS = 6;
    const int COLS = 7;
    std::vector<std::vector<PlayerToken>> board;
    bool playerOneTurn;

    void makeBoard() {
        board = std::vector<std::vector<PlayerToken>>(ROWS, 
            std::vector<PlayerToken>(COLS, PlayerToken::EMPTY));
        playerOneTurn = true;
    }

    bool isValidMove(int column) const {
        return column >= 0 && column < COLS && board[0][column] == PlayerToken::EMPTY;
    }

    void dropPiece(int column) {
        for (int row = ROWS-1; row >= 0; row--) {
            if (board[row][column] == PlayerToken::EMPTY) {
                board[row][column] = playerOneTurn ? PlayerToken::P1 : PlayerToken::P2;
                break;
            }
        }
    }

    GameState checkWin(PlayerToken player) const {
        // Check horizontal
        for (int row = 0; row < ROWS; row++) {
            for (int col = 0; col < COLS-3; col++) {
                if (board[row][col] == player &&
                    board[row][col+1] == player &&
                    board[row][col+2] == player &&
                    board[row][col+3] == player) {
                    return player == PlayerToken::P1 ? GameState::PLAYER_1_WINS 
                                                    : GameState::PLAYER_2_WINS;
                }
            }
        }

        // Check vertical
        for (int col = 0; col < COLS; col++) {
            for (int row = 0; row < ROWS-3; row++) {
                if (board[row][col] == player &&
                    board[row+1][col] == player &&
                    board[row+2][col] == player &&
                    board[row+3][col] == player) {
                    return player == PlayerToken::P1 ? GameState::PLAYER_1_WINS 
                                                    : GameState::PLAYER_2_WINS;
                }
            }
        }

        // Check diagonal (top-left to bottom-right)
        for (int row = 0; row < ROWS-3; row++) {
            for (int col = 0; col < COLS-3; col++) {
                if (board[row][col] == player &&
                    board[row+1][col+1] == player &&
                    board[row+2][col+2] == player &&
                    board[row+3][col+3] == player) {
                    return player == PlayerToken::P1 ? GameState::PLAYER_1_WINS 
                                                    : GameState::PLAYER_2_WINS;
                }
            }
        }

        // Check diagonal (bottom-left to top-right)
        for (int row = 3; row < ROWS; row++) {
            for (int col = 0; col < COLS-3; col++) {
                if (board[row][col] == player &&
                    board[row-1][col+1] == player &&
                    board[row-2][col+2] == player &&
                    board[row-3][col+3] == player) {
                    return player == PlayerToken::P1 ? GameState::PLAYER_1_WINS 
                                                    : GameState::PLAYER_2_WINS;
                }
            }
        }

        return GameState::ONGOING;
    }

public:
    ConnectFour() { resetGame(); }

    void resetGame() { 
        makeBoard();
        playerOneTurn = true;
    }

    void play() {
        printRules();
        GameState status = GameState::ONGOING;
        
        while (status == GameState::ONGOING) {
            printBoard();
            status = processTurn();
        }
        
        printBoard();
        displayResult(status);
        handleGameEnd();
    }

    int getPlayerInput() const {
        int col;
        while (true) {
            std::cout << "Player " << (playerOneTurn ? 1 : 2)
                      << ", enter column (1-7): ";
            if (std::cin >> col) {
                col--;
                if (col >= 0 && col < COLS && isValidMove(col)) {
                    break;
                }
            }
            handleInvalidInput();
        }
        return col;
    }

    GameState processTurn() {
        int col = getPlayerInput();
        dropPiece(col);
        
        // Immediately check win for current player
        PlayerToken current = playerOneTurn ? PlayerToken::P1 : PlayerToken::P2;
        GameState status = checkWin(current);
        
        if (status != GameState::ONGOING) return status;
        
        // Check for draw
        bool boardFull = true;
        for (const auto& cell : board[0]) {
            if (cell == PlayerToken::EMPTY) {
                boardFull = false;
                break;
            }
        }
        if (boardFull) return GameState::DRAW;

        // Only switch turns if game continues
        playerOneTurn = !playerOneTurn;
        return GameState::ONGOING;
    }

    void printRules() const {
        std::cout << "=== Connect Four ===\n"
                  << "Rules:\n"
                  << "1. Players alternate turns\n"
                  << "2. First to get 4 in a row wins\n"
                  << "3. Enter column numbers 1-7 to play\n"
                  << "4. Game ends immediately when a player wins\n\n";
    }

    void printBoard() const {
        std::cout << "\n 1 2 3 4 5 6 7\n";
        for (const auto& row : board) {
            std::cout << "|";
            for (const auto& cell : row) {
                char c = ' ';
                if (cell == PlayerToken::P1) c = 'X';
                else if (cell == PlayerToken::P2) c = 'O';
                std::cout << c << "|";
            }
            std::cout << "\n";
        }
        std::cout << "-------------------\n\n";
    }

    void displayResult(GameState status) const {
        switch (status) {
            case GameState::PLAYER_1_WINS:
                std::cout << "Player 1 (X) wins!\n";
                break;
            case GameState::PLAYER_2_WINS:
                std::cout << "Player 2 (O) wins!\n";
                break;
            case GameState::DRAW:
                std::cout << "Game ended in a draw!\n";
                break;
            default: break;
        }
    }

    void handleGameEnd() const {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    void handleInvalidInput() const {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please try again.\n";
    }
};

int main() {
    while (true) {
        ConnectFour game;
        game.play();
        
        char choice;
        do {
            std::cout << "Play again? (y/n): ";
            std::cin >> choice;
            choice = tolower(choice);
        } while (choice != 'y' && choice != 'n');
        
        if (choice == 'n') break;
    }
    std::cout << "Thanks for playing!\n";
    return 0;
}