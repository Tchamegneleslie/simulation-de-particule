#include "Simulation.h"

Simulation::Simulation(): mParams(), mTime(0.0f){}

void Simulation::Update(float deltaTime){

    if (mParams.paused) return ;

    mTime += deltaTime * mParams.timeScale;
}

SimulationParams & Simulation::GetParams(){

    return mParams;
}