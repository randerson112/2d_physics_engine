//Class implementation for dynamic physics bodies

#include "DynamicBody.hpp"

//Constructor to set members
DynamicBody::DynamicBody(Vector2 initialPosition,
Collider* colliderInstance,
Vector2 initialVelocity,
Vector2 initialAcceleration,
float initialMass)
: PhysicsBody(initialPosition, colliderInstance),
velocity(initialVelocity),
acceleration(initialAcceleration),
mass(initialMass) {}

//Applies an external force to the body
void DynamicBody::applyForce(Vector2 force)
{
    acceleration = force / mass;
}

//Update the physics of the body in the world
void DynamicBody::update(float deltaTime)
{
    velocity += acceleration * deltaTime; //Update velocity based on current acceleration

    position += velocity * deltaTime; //Update position based on current velocity
    collider->setPosition(position);

    acceleration = {0, 0};
}

//Getters for member variables
Vector2 DynamicBody::getVelocity()
{
    return velocity;
}

Vector2 DynamicBody::getAcceleration()
{
    return acceleration;
}

float DynamicBody::getMass()
{
    return mass;
}

//Setters for member variables
void DynamicBody::setVelocity(Vector2 newVelocity)
{
    velocity = newVelocity;
}

void DynamicBody::setAcceleration(Vector2 newAcceleration)
{
    acceleration = newAcceleration;
}

void DynamicBody::setMass(float newMass)
{
    if (newMass >= 0)
    {
        mass = newMass;
    }
}