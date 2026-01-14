#pragma once
#include <SDL3/SDL.h>
#include "ui/ImguiLayer.h"

#define SDL_MAIN_HANDLED

class Application {
    public:
        bool init();
        void run();
        void shutdown();

    private:
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        bool running = true;

        ImguiLayer imgui;
};