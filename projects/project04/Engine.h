#pragma once
#include <SDL.h>
#include <functional>  // For std::function

class Engine {
public:
    Engine();
    ~Engine();

    // Event handling with callback
    void handleEvents(const std::function<void(const SDL_Event&)>& callback);

    // Rendering with callback
    void render(const std::function<void(SDL_Renderer*)>& callback);

    // Getter for renderer (optional)
    SDL_Renderer* getRenderer() const { return renderer; }

private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
};