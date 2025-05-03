#include "Engine.h"
#include "Game.h"

int main(int argc, char* argv[]) {
    Engine engine;
    Game game;

    bool running = true;
    while (running) {
        engine.handleEvents([&](const SDL_Event& e) {
            if (e.type == SDL_QUIT) {
                running = false;
            }

            if (!game.isAnimatingNow()) {
                if (e.type == SDL_KEYDOWN) {
                    switch (e.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        running = false;
                        break;

                    case SDLK_r:
                        game.reset();
                        break;

                    case SDLK_LEFT:
                        game.moveCursor(-1);
                        break;

                    case SDLK_RIGHT:
                        game.moveCursor(1);
                        break;

                    case SDLK_RETURN:
                        game.placePiece();
                        break;

                    default:
                        break;
                    }
                }
            }
            });

        game.updateAnimation();

        engine.render([&](SDL_Renderer* renderer) {
            game.draw(renderer);
            });
    }
    return 0;
}