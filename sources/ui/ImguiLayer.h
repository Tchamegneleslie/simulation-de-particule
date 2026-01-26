#pragma once
#include <SDL3/SDL.h>
#include "Simulation/Simulation.h"

class ImguiLayer{
    public:
        //SDL_Renderer* renderer;
        void Init(SDL_Window* mWindow, SDL_Renderer* mRenderer);
        void ProcessEvent(const SDL_Event& event);
        void Begin();
        void Draw();
        void End();
        void Shutdown();
        void SetSimulation( Simulation* simulation);

    private:
        SDL_Window* mWindow;
        SDL_Renderer* mRenderer;
        Simulation* mSimulation;

   
};