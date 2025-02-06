//Base class defention for physics bodies
//All other physics bodies will inherit from this
//Handles basic physics properties such as position, velocity, and forces

#ifndef PHYSICS_BODY_HPP
#define PHYSICS_BODY_HPP

#include "Vector2.hpp"
#include "Collider.hpp"
#include <memory>

class Collider;

class PhysicsBody
{
protected:
    //Position of body in the world
    Vector2 position;

    //Collider for detecting collisions
    Collider* collider;

public:
    //Constructor
    PhysicsBody(Vector2 initialPosition, Collider* colliderInstance);

    //Destructor
    virtual ~PhysicsBody();

    //Updates the physics of the body in the world (implemented in derived classes)
    virtual void update(float deltaTime) = 0;

    //Getters for member variables
    Vector2 getPosition() const;
    Collider* getCollider() const;

    //Setters for member variables
    void setPosition(Vector2 newPosition);
    void setCollider(Collider* newCollider);
};

#endif