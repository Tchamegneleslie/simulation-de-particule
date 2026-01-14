#include "ImguiLayer.h"

#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_sdlrenderer3.h"

void ImguiLayer::init(SDL_Window* window, SDL_Renderer* renderer){

    // setup dear imgui context

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);


}

void ImguiLayer::processEvent(const SDL_Event& event){
    ImGui_ImplSDL3_ProcessEvent(&event);
}

void ImguiLayer::begin(){

    // Start the Dear ImGui frame

    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
}

void ImguiLayer::draw(){
    ImGui::Begin("Hello");
    ImGui::Text("SDL3 + ImGui OK -/");
    ImGui::Text("la boucle fonctionne");
    ImGui::End();

}

void ImguiLayer::end(){

    // rendering

    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
}

void ImguiLayer::shutdown(){

    // cleanup

    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

}