//Base class defention for physics bodies
//All other physics bodies will inherit from this
//Handles basic physics properties such as position, velocity, and forces

#ifndef PHYSICS_BODY_HPP
#define PHYSICS_BODY_HPP

#include "Vector2.hpp"

class PhysicsBody
{
private:
    //Position of body in the world
    Vector2 position;

    //Current velocity of body (how fast it is moving)
    Vector2 velocity;

    //Acceleration factor of the body
    Vector2 acceleration;

    //Mass of the body (weight)
    float mass;

public:
    //Constructors and deconstructors
    PhysicsBody(Vector2 initialPosition = {0, 0},
    Vector2 initialVelocity = {0, 0},
    Vector2 initialAcceleration = {0, 0},
    float mass = 1.0f);

    virtual ~PhysicsBody() = default;

    //Applies a force to the body
    virtual void applyForce(Vector2 force) = 0;

    //Updates the physics of the body in the world
    virtual void update(float deltaTime) = 0;

    //Getters for member variables
    Vector2 getPosition();
    Vector2 getVelocity();
    Vector2 getAcceleration();
    float getMass();

    //Setters for member variables
    void setPosition(Vector2 newPosition);
    void setVelocity(Vector2 newVelocity);
    void setAcceleration(Vector2 newAcceleration);
    void setMass(float newMass);
};

#endif