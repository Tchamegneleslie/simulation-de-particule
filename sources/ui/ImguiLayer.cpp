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

    if (!mSimulation) return;

    SimulationParams & mParams = mSimulation->GetParams();
    PhysicsParams& mPhysicsParams = mSimulation->GetPhysicsParams();
    static int lastCount = mParams.particleCount;
    
    ImGui::Begin("Simulation ");

    if (ImGui::SliderInt("Particles", &mParams.particleCount, 10, 1000)){
        if (mParams.particleCount != lastCount){
            mSimulation->RequestReset();
            lastCount = mParams.particleCount;
        }
    }
    
    ImGui::SliderFloat("Speed", & mParams.speed, 1.0f, 100.0f );
    ImGui::SliderFloat("Force", & mPhysicsParams.forceStrength, 0.0f, 200.0f);
    
    const char* modes[]  = { "Off", "Attraction", "Repulsion", "Vortex" };
    int current = static_cast<int>(mPhysicsParams.mode);

    if( ImGui::Combo("Force Mode", &current, modes, 4)){
        mPhysicsParams.mode = static_cast<ForceMode>(current);
    }

    ImGui::Separator();
    ImGui::Text("Simulation active");

    if ( ImGui::Button("Reset")){
        mSimulation->RequestReset(); 
    }
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