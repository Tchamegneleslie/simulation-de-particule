#pragma once

// parametres controlables depuis ImGui

struct SimulationParams {
    int particleCount = 100;
    float timeScale = 1.0f;
    bool magneticOn = false;
    bool paused = false;
};

class Simulation {
    public:
        Simulation();
        void Update(float deltaTime);
        SimulationParams & GetParams();

    private:
        SimulationParams mParams;
        float mTime;
};