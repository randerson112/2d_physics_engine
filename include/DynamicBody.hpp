//Class defenition for physics bodies that are affected by gravity and forces
//Affected by gravity
//Affected by collisions with other bodies
//Has a collider to collide with other bodies
//Responds to basic physics but cannot be controlled

#ifndef DYNAMIC_BODY_HPP
#define DYNAMIC_BODY_HPP

#include "PhysicsBody.hpp"
#include "Vector2.hpp"

class DynamicBody : public PhysicsBody
{
private:
    //Current velocity of the body
    Vector2 velocity;

    //Current acceleration of the body
    Vector2 acceleration;

    //Mass of the body
    float mass;

public:
    //Constructor to set postion, velocity, acceleration, mass, and collider
    DynamicBody(Vector2 initialPosition,
    Collider* colliderInstance,
    Vector2 initialVelocity = {0, 0},
    Vector2 initialAcceleration = {0, 0},
    float initialMass = 1.0f);

    //Applies an external force to the body
    void applyForce(Vector2 force);

    //Update the physics of the body in the world
    void update(float deltaTime) override;
};

#endif