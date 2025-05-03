#include "Game.h"
#include <SDL.h>
#include <SDL_image.h>
#include <algorithm>

Game::Game() :
    currentPlayer(Player::PLAYER1),
    state(GameState::PLAYING),
    cursorCol(0),
    fontTexture(nullptr),
    isAnimating(false),
    animationColumn(0),
    currentAnimationRow(0),
    targetRow(0),
    animationStartTime(0)
{
    reset();
}

Game::~Game() {
    if (fontTexture) SDL_DestroyTexture(fontTexture);
}

void Game::reset() {
    for (auto& row : board)
        row.fill(Player::NONE);
    currentPlayer = Player::PLAYER1;
    state = GameState::PLAYING;
    cursorCol = 0;
    isAnimating = false;
}

void Game::loadFontTexture(SDL_Renderer* renderer) const {
    if (!fontTexture) {
        SDL_Surface* fontSurface = SDL_LoadBMP("fonts/font.bmp");
        if (fontSurface) {
            SDL_SetColorKey(fontSurface, SDL_TRUE, SDL_MapRGB(fontSurface->format, 255, 0, 255));
            fontTexture = SDL_CreateTextureFromSurface(renderer, fontSurface);
            SDL_FreeSurface(fontSurface);
        }
    }
}

void Game::drawText(SDL_Renderer* renderer, const std::string& text, int x, int y) const {
    loadFontTexture(renderer);
    if (!fontTexture) return;

    SDL_Rect src, dest;
    for (size_t i = 0; i < text.size(); ++i) {
        char c = text[i];
        if (c < ' ' || c > '~') continue;

        int charIndex = c - ' ';
        src.x = (charIndex % 16) * CHAR_WIDTH;
        src.y = (charIndex / 16) * CHAR_HEIGHT;
        src.w = CHAR_WIDTH;
        src.h = CHAR_HEIGHT;

        dest.x = x + static_cast<int>(i * CHAR_WIDTH);
        dest.y = y;
        dest.w = CHAR_WIDTH;
        dest.h = CHAR_HEIGHT;

        SDL_RenderCopy(renderer, fontTexture, &src, &dest);
    }
}

void Game::moveCursor(int dx) {
    if (!isAnimating) {
        cursorCol = (cursorCol + dx + COLS) % COLS;
    }
}

int Game::findLowestRow(int col) const {
    for (int row = ROWS - 1; row >= 0; --row)
        if (board[row][col] == Player::NONE)
            return row;
    return -1;
}

void Game::placePiece() {
    if (isAnimating || state != GameState::PLAYING) return;

    int row = findLowestRow(cursorCol);
    if (row == -1) return;

    isAnimating = true;
    animationColumn = cursorCol;
    currentAnimationRow = -2;
    targetRow = row;
    animationStartTime = SDL_GetTicks();
}

void Game::updateAnimation() {
    if (!isAnimating) return;

    Uint32 currentTime = SDL_GetTicks();
    float progress = static_cast<float>(currentTime - animationStartTime) / DROP_SPEED;
    currentAnimationRow = std::min(targetRow, static_cast<int>(progress));

    if (currentAnimationRow >= targetRow) {
        isAnimating = false;
        board[targetRow][animationColumn] = currentPlayer;

        if (checkWin(targetRow, animationColumn)) {
            state = (currentPlayer == Player::PLAYER1) ? GameState::WON : GameState::LOST;
        }
        else if (checkDraw()) {
            state = GameState::DRAW;
        }
        else {
            currentPlayer = (currentPlayer == Player::PLAYER1) ?
                Player::PLAYER2 : Player::PLAYER1;
        }
    }
}

bool Game::checkWin(int row, int col) const {
    Player player = board[row][col];

    // Vertical check
    int count = 1;
    for (int i = row + 1; i < ROWS && board[i][col] == player; ++i) count++;
    if (count >= 4) return true;

    // Horizontal check
    count = 1;
    for (int i = col - 1; i >= 0 && board[row][i] == player; --i) count++;
    for (int i = col + 1; i < COLS && board[row][i] == player; ++i) count++;
    if (count >= 4) return true;

    // Diagonal checks
    count = 1;
    for (int i = 1; row - i >= 0 && col - i >= 0 && board[row - i][col - i] == player; ++i) count++;
    for (int i = 1; row + i < ROWS && col + i < COLS && board[row + i][col + i] == player; ++i) count++;
    if (count >= 4) return true;

    count = 1;
    for (int i = 1; row - i >= 0 && col + i < COLS && board[row - i][col + i] == player; ++i) count++;
    for (int i = 1; row + i < ROWS && col - i >= 0 && board[row + i][col - i] == player; ++i) count++;
    return count >= 4;
}

bool Game::checkDraw() const {
    for (const auto& col : board[0])
        if (col == Player::NONE)
            return false;
    return true;
}

GameState Game::getState() const {
    return state;
}

Player Game::getCurrentPlayer() const {
    return currentPlayer;
}

bool Game::isAnimatingNow() const {
    return isAnimating;
}

void Game::draw(SDL_Renderer* renderer) const {
    // Draw background
    SDL_SetRenderDrawColor(renderer, 30, 30, 150, 255);
    SDL_RenderClear(renderer);

    // Draw grid
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int c = 0; c <= COLS; c++)
        SDL_RenderDrawLine(renderer, c * 100, 0, c * 100, 600);
    for (int r = 0; r <= ROWS; r++)
        SDL_RenderDrawLine(renderer, 0, r * 100, 700, r * 100);

    // Draw colored arrow cursor
    const SDL_Color arrowColor = currentPlayer == Player::PLAYER1 ?
        SDL_Color{ 255, 50, 50, 255 } : SDL_Color{ 255, 255, 50, 255 };

    const int arrowX = cursorCol * 100 + 50;
    const int arrowY = 20;
    SDL_SetRenderDrawColor(renderer, arrowColor.r, arrowColor.g, arrowColor.b, 255);

    // Arrow triangle
    SDL_RenderDrawLine(renderer, arrowX - ARROW_SIZE, arrowY, arrowX, arrowY + ARROW_SIZE);
    SDL_RenderDrawLine(renderer, arrowX, arrowY + ARROW_SIZE, arrowX + ARROW_SIZE, arrowY);
    SDL_RenderDrawLine(renderer, arrowX - ARROW_SIZE / 2, arrowY, arrowX + ARROW_SIZE / 2, arrowY);

    // Draw pieces
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            if (board[r][c] != Player::NONE) {
                SDL_Rect piece{ c * 100 + 10, r * 100 + 10, 80, 80 };
                SDL_SetRenderDrawColor(renderer,
                    board[r][c] == Player::PLAYER1 ? 200 : 220,
                    board[r][c] == Player::PLAYER1 ? 0 : 220,
                    0, 255);
                SDL_RenderFillRect(renderer, &piece);
            }
        }
    }

    // Draw animated piece
    if (isAnimating) {
        SDL_Rect animPiece{
            animationColumn * 100 + 10,
            currentAnimationRow * 100 + 10,
            80, 80
        };
        SDL_SetRenderDrawColor(renderer,
            currentPlayer == Player::PLAYER1 ? 255 : 255,
            currentPlayer == Player::PLAYER1 ? 50 : 255,
            50, 255);
        SDL_RenderFillRect(renderer, &animPiece);
    }

    // Draw game state messages
    if (state != GameState::PLAYING) {
        std::string message;
        if (state == GameState::WON) {
            message = "RED PLAYER WINS!";
        }
        else if (state == GameState::LOST) {
            message = "YELLOW PLAYER WINS!";
        }
        else {
            message = "GAME IS A DRAW!";
        }

        // Center text horizontally
        int textWidth = static_cast<int>(message.length()) * CHAR_WIDTH;
        int textX = (700 - textWidth) / 2;
        drawText(renderer, message, textX, 280);

        drawText(renderer, "PRESS R TO RESTART", 220, 320);
    }
    else {
        // Draw current turn indicator
        std::string turn = std::string(currentPlayer == Player::PLAYER1 ? "RED" : "YELLOW") + "'S TURN";
        int textWidth = static_cast<int>(turn.length()) * CHAR_WIDTH;
        drawText(renderer, turn, (700 - textWidth) / 2, 620);

        drawText(renderer, "USE ARROW KEYS & ENTER", 150, 660);
    }
}