#include "Physics.h"


Vector2 physics::VortexForce(const Vector2& velocity, float strength){
    float speed = velocity.Lenght();

    if(speed < 0.0001f) return Vector2(0.0f, 0.0f);

    Vector2 perpendicular(-velocity.y, velocity.x);

     //normalisation sure
    perpendicular /= speed;

    return perpendicular * strength;


}

Vector2 physics::Centralforce( const Vector2& position, const Vector2& centre, const PhysicsParams& params ){
    Vector2 dir = centre - position;
    float dist = dir.Lenght() + 0.001f;
    Vector2 force = dir.Normalized() * params.forceStrength;

    if (params.mode == ForceMode::Repulsion) {
        force = force * -1.0f;
        float maxRadius = 300.0f;
        if (dist > maxRadius) return Vector2{0.0f, 0.0f};
    }

    return force;
}

void physics::Integrate( Vector2& position, Vector2& velocity, const Vector2& acceleration, float deltaTime ){
    velocity += acceleration * deltaTime;
    position += velocity * deltaTime;
}