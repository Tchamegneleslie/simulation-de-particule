#include "Application.h"
#include <iostream> 

bool Application::init(){
    int init = SDL_Init(SDL_INIT_VIDEO);
    if (init < 0){
        SDL_Log("SDL_Init error : %s", SDL_GetError());
        //std::cerr << "Error SDL_Init\n";
        return false;
    }

    std::cout << "SDL3 initialise avec succes " << std::endl;

    mWindow = SDL_CreateWindow("Simulation magnetique", 800, 600, SDL_WINDOW_RESIZABLE);

    if( !mWindow ){
        std::cerr << "Error create windows" << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow, NULL);

    if( !mRenderer ){
        //std::cerr << "Error create renderer" << SDL_GetError() << std::endl;
        SDL_Log("Imgui renderer null ");

        SDL_DestroyWindow(mWindow);
        SDL_Quit();

        return false;
    }

    imgui.Init(mWindow, mRenderer);
    return true;

}

float Application::ComputerDeltaTime(){
    Uint64 currentTicks = SDL_GetTicks();
    float deltaTime = ( currentTicks - mLastTicks ) / 1000.0f;
    mLastTicks = currentTicks;

    return deltaTime;

}

void Application::run(){

    //SDL_ShowWindow(mWindow);

    SDL_Event event;
    imgui.SetSimulation(&mSimulation);

    while(running){
        while(SDL_PollEvent(&event)){
            
            imgui.ProcessEvent(event);

            if (event.type == SDL_EVENT_QUIT){
                running = false;
            }
        }
        
        float deltaTime = ComputerDeltaTime();

        mSimulation.Update(deltaTime);

        // dessiner un fond bleu

        SDL_SetRenderDrawColor(mRenderer, 20, 20, 20, 255);
        SDL_RenderClear(mRenderer);

        imgui.Begin();
        
        imgui.Draw();
        imgui.End();
            

        SDL_RenderPresent(mRenderer);
        
    }

}

void Application::shutdown(){

    imgui.Shutdown();

    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();

}

