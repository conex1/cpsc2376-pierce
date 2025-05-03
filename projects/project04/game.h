#pragma once
#include <SDL.h>
#include <array>
#include <string>

enum class GameState { PLAYING, WON, LOST, DRAW };
enum class Player { NONE, PLAYER1, PLAYER2 };

class Game {
private:
    static const int ROWS = 6;
    static const int COLS = 7;
    static const int DROP_SPEED = 50;
    static const int CHAR_WIDTH = 32;
    static const int CHAR_HEIGHT = 32;
    static const int ARROW_SIZE = 30;

    std::array<std::array<Player, COLS>, ROWS> board;
    Player currentPlayer;
    GameState state;
    int cursorCol;

    mutable SDL_Texture* fontTexture;
    bool isAnimating;
    int animationColumn;
    int currentAnimationRow;
    int targetRow;
    Uint32 animationStartTime;

    bool checkWin(int row, int col) const;
    bool checkDraw() const;
    int findLowestRow(int col) const;
    void drawText(SDL_Renderer* renderer, const std::string& text, int x, int y) const;
    void loadFontTexture(SDL_Renderer* renderer) const;

public:
    Game();
    ~Game();
    void reset();
    void moveCursor(int dx);
    void placePiece();
    void updateAnimation();
    GameState getState() const;
    Player getCurrentPlayer() const;
    bool isAnimatingNow() const;
    void draw(SDL_Renderer* renderer) const;
};