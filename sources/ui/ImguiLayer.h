#pragma once
#include <SDL3/SDL.h>

class ImguiLayer{
    public:
        SDL_Renderer* renderer;
        void init(SDL_Window* window, SDL_Renderer* renderer);
        void processEvent(const SDL_Event& event);
        void begin();
        void draw();
        void end();
        void shutdown();

   
};