#pragma once
#include <vector>
#include "math/Vector2.h"
#include "physics/Physics.h"

// 

struct Particles{
    Vector2 position;
    Vector2 velocity;
};

// parametres controlables depuis ImGui

struct SimulationParams {
    int particleCount = 100;
    float speed = 20.0f;
    
};

class Simulation {
    public:
        Simulation();
        void Update(float deltaTime);
        void RequestReset();
        const std::vector<Particles>& GetParticles() const;
        SimulationParams & GetParams();
        //parametres physiques
        PhysicsParams& GetPhysicsParams();

    private:
        void Reset();  // lance la simulation
        std::vector<Particles> mParticles;
        SimulationParams mParams;
        PhysicsParams mPhysicsParams;
        bool mNeedsReset = false;
        
};