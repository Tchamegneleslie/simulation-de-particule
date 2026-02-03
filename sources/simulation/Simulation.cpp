#include "Simulation.h"
#include "physics/Physics.h"
#include <cstdlib>



Simulation::Simulation(){
    Reset();
}

void Simulation::Reset(){
    mParticles.clear();
    mParticles.resize(mParams.particleCount);

    for( auto& p : mParticles ){
        p.position.x = rand() % 800;
        p.position.y = rand() % 600;
        p.velocity.x = ((rand() % 200) - 100) / 2.0f;
        p.velocity.y = ((rand() % 200) - 100) / 2.0f;
        
        

        
    }
}

void Simulation::RequestReset(){
    mNeedsReset = true;
}

void Simulation::Update(float deltaTime){

    if (mNeedsReset){
        Reset();
        mNeedsReset = false;
    }

    Vector2 centre(400.0f, 300.0f);
    

    for (auto& p : mParticles){
        Vector2 force{0.0f, 0.0f};

        switch (mPhysicsParams.mode){
            case ForceMode::Off :
                p.position  += p.velocity * mParams.speed * deltaTime;
                break;
            case ForceMode::Vortex:
                force = physics::VortexForce(p.velocity,mPhysicsParams.forceStrength);
                break;
            case ForceMode::Attraction:
            case ForceMode::Repulsion:
                force = physics::Centralforce(p.position, centre, mPhysicsParams);
                break;
        }
        

        physics::Integrate(p.position, p.velocity, force, deltaTime);

        // limites d'ecran

        if (p.position.x < 0.0f) {
            p.position.x = 0.0f;
            p.velocity.x *= -0.8f;
        }
        else if(p.position.x > 800.0f){
            p.position.x =  800.0f;
            p.velocity.x *= -0.8f;
        }
        if (p.position.y < 0.0f){
            p.position.y = 0.0f;
            p.velocity.y *= -0.8f;
        } 
        else if(p.position.y > 600.0f){
            p.position.y = 600.0f;
            p.velocity.y *= -0.8f;
        }

        

        

        
    }

}

 

const std::vector<Particles>& Simulation::GetParticles() const {
    return mParticles;
}

SimulationParams & Simulation::GetParams(){

    return mParams;
}

PhysicsParams& Simulation::GetPhysicsParams(){

    return mPhysicsParams;
}