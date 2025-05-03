#include "Engine.h"
#include <SDL.h>

Engine::Engine() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL initialization failed: %s", SDL_GetError());
        return;
    }

    // Create window
    window = SDL_CreateWindow(
        "Connect 4 Game",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        700, 600,  // Width/height matching Connect 4 grid
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        SDL_Log("Window creation failed: %s", SDL_GetError());
        return;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!renderer) {
        SDL_Log("Renderer creation failed: %s", SDL_GetError());
        return;
    }
}

Engine::~Engine() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}

void Engine::handleEvents(const std::function<void(const SDL_Event&)>& callback) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        callback(e);
    }
}

void Engine::render(const std::function<void(SDL_Renderer*)>& callback) {
    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Execute draw callback
    if (callback) {
        callback(renderer);
    }

    // Update screen
    SDL_RenderPresent(renderer);
}