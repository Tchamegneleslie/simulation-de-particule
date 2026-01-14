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

    window = SDL_CreateWindow("Simulation magnetique", 800, 600, SDL_WINDOW_RESIZABLE);

    if( !window ){
        std::cerr << "Error create windows" << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window, NULL);

    if( !renderer ){
        std::cerr << "Error create renderer" << SDL_GetError() << std::endl;

        SDL_DestroyWindow(window);
        SDL_Quit();

        return false;
    }

    imgui.init(window, renderer);
    return true;

}

void Application::run(){

    //SDL_ShowWindow(window);

    SDL_Event event;

    while(running){
        while(SDL_PollEvent(&event)){
            
            imgui.processEvent(event);

            if (event.type == SDL_EVENT_QUIT){
                running = false;
            }
        }
            
            // dessiner un fond bleu

            SDL_SetRenderDrawColor(renderer, 30, 144, 255, 255);
            SDL_RenderClear(renderer);

            imgui.begin();
            imgui.draw();
            imgui.end();
            

            SDL_RenderPresent(renderer);
        
    }

}

void Application::shutdown(){

    imgui.shutdown();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}

