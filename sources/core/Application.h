#pragma once
#include <SDL3/SDL.h>
#include "ui/ImguiLayer.h"

#define SDL_MAIN_HANDLED

class Application {
    public:
        bool init();
        void run();
        void shutdown();
        float ComputerDeltaTime();

    private:
        SDL_Window* mWindow = nullptr;
        SDL_Renderer* mRenderer = nullptr;
        bool running = true;
        Uint64 mLastTicks;

        ImguiLayer imgui;
        Simulation mSimulation;
};