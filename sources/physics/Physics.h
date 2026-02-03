#pragma once
#include "math/Vector2.h"

enum class ForceMode{
    Off = 0,  // simulation simple sans force
    Attraction,  // simulation avec force d'attraction vers le centre
    Repulsion,   // simulation avec force de repulsion vers le centre
    Vortex      // simulation avec force magnetique type Lorentz

};

struct PhysicsParams{

    float forceStrength = 100.0f;
    ForceMode mode = ForceMode::Off;
};

namespace physics {
    Vector2 VortexForce(const Vector2& velocity, float strength);
    Vector2 Centralforce(const Vector2& position, const Vector2& centre, const PhysicsParams& params);
    void Integrate(Vector2& position, Vector2& velocity, const Vector2& acceleration, float deltaTime);
}