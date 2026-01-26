#include "ImguiLayer.h"

#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_sdlrenderer3.h"

void ImguiLayer::Init(SDL_Window* window, SDL_Renderer* renderer){

    mWindow = window;
    mRenderer = renderer;

    // setup dear imgui context


    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForSDLRenderer(mWindow, mRenderer);
    ImGui_ImplSDLRenderer3_Init(mRenderer);


}

void ImguiLayer::SetSimulation( Simulation* simulation ){

    mSimulation = simulation;

}

void ImguiLayer::ProcessEvent(const SDL_Event& event){
    ImGui_ImplSDL3_ProcessEvent(&event);
}

void ImguiLayer::Begin(){

    // Start the Dear ImGui frame

    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
}

void ImguiLayer::Draw(){

    //ImGui::ShowDemoWindow();

    if (!mSimulation) return;

    SimulationParams & mParams = mSimulation->GetParams();
    
    ImGui::Begin("Simulation ");
    ImGui::SliderInt("Particles", & mParams.particleCount, 1, 1000 );
    ImGui::SliderFloat("Time scale", & mParams.timeScale, 0.1f, 5.0f );
    ImGui::Checkbox("Magnetic force", & mParams.magneticOn );
    ImGui::Checkbox("Pause", &mParams.paused );
    ImGui::Separator();
    ImGui::Text("Simulation active");
    ImGui::End();

}

void ImguiLayer::End(){

    // rendering

    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), mRenderer);
}

void ImguiLayer::Shutdown(){

    // cleanup

    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

}