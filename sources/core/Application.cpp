// boucle principale


#include "Application.h"
#include <iostream> 

bool Application::init(){
    int init = SDL_Init(SDL_INIT_VIDEO);
    if (init < 0){
        SDL_Log("SDL_Init error : %s", SDL_GetError());
        
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
        std::cerr << "Error create renderer" << SDL_GetError() << std::endl;
        

        SDL_DestroyWindow(mWindow);
        SDL_Quit();

        return false;
    }

    imgui.Init(mWindow, mRenderer);
    return true;

}

float Application::ComputerDeltaTime(){
    Uint64 currentCounter = SDL_GetPerformanceCounter();
    Uint64 mLastCounter = SDL_GetPerformanceCounter();
    const double freq = (double)SDL_GetPerformanceFrequency();
    float deltaTime = ( currentCounter - mLastCounter ) / freq;
    mLastCounter = currentCounter;

    // limitation du pas de temps ( 60 FPS )

    if ( deltaTime > 0.066f) deltaTime = 0.066f;

    return deltaTime;

} 

void Application::run(){

    SDL_Event event;
    imgui.SetSimulation(&mSimulation);

    while(running){

        float deltaTime = ComputerDeltaTime();

        while(SDL_PollEvent(&event)){
            
            imgui.ProcessEvent(event);

            if (event.type == SDL_EVENT_QUIT){
                running = false;
            }
        }

        // Mise a jour de deltaTime

        mSimulation.Update(deltaTime);


        // rendu SDL

        SDL_SetRenderDrawColor(mRenderer, 20, 20, 20, 255);
        SDL_RenderClear(mRenderer);

        // dessiner les particules

        SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

        SDL_FRect rect;
        rect.w = 3;
        rect.h = 3;

        for ( auto& p: mSimulation.GetParticles()){
            rect.x = p.position.x;
            rect.y = p.position.y;
            
            SDL_RenderFillRect(mRenderer, &rect);

        }  

        // Rendu imgui

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

