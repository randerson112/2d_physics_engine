//Base class implementation for physics bodies

#include "PhysicsBody.hpp"

//Constructor
PhysicsBody::PhysicsBody(Vector2 initialPosition, Vector2 initialVelocity, Vector2 initialAcceleration, float mass)
: position(initialPosition), velocity(initialVelocity), acceleration(initialAcceleration), mass(mass), collider(nullptr){}

//Getters for member variables
Vector2 PhysicsBody::getPosition()
{
    return position;
}

Vector2 PhysicsBody::getVelocity()
{
    return velocity;
}

Vector2 PhysicsBody::getAcceleration()
{
    return acceleration;
}

float PhysicsBody::getMass()
{
    return mass;
}

//Setters for member variables
void PhysicsBody::setPosition(Vector2 newPosition)
{
    position = newPosition;
}

void PhysicsBody::setVelocity(Vector2 newVelocity)
{
    velocity = newVelocity;
}

void PhysicsBody::setAcceleration(Vector2 newAcceleration)
{
    acceleration = newAcceleration;
}

void PhysicsBody::setMass(float newMass)
{
    if (newMass >= 0) //Ensure non-negative mass
    {
        mass = newMass;
    }
}

void PhysicsBody::setCollider(Collider* newCollider)
{
    collider = newCollider;
}