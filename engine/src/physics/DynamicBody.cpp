//Class implementation for dynamic physics bodies

#include "physics/DynamicBody.hpp"

//Constructor to set members
DynamicBody::DynamicBody(const Vector2& initialPosition, Collider* colliderInstance)
: PhysicsBody(initialPosition, colliderInstance, BodyType::DynamicBody),
mass(1.0f),
restitution(0.6f),
velocity({0, 0}),
acceleration({0, 0}) {}

//Applies an external force to the body
void DynamicBody::applyForce(const Vector2& forceToAdd)
{
    force += forceToAdd;
}

//Update the physics of the body in the world
void DynamicBody::update(float deltaTime)
{
    acceleration = force / mass;
    velocity += acceleration * deltaTime; //Update velocity based on current acceleration

    position += velocity * deltaTime; //Update position based on current velocity
    collider->setPosition(position);

    force = {0, 0};
}

//Getters for member variables
const Vector2& DynamicBody::getVelocity() const
{
    return velocity;
}

const Vector2& DynamicBody::getForce() const
{
    return force;
}

const Vector2& DynamicBody::getAcceleration() const
{
    return acceleration;
}

float DynamicBody::getRestitution() const
{
    return restitution;
}

float DynamicBody::getMass() const
{
    return mass;
}

//Setters for member variables
void DynamicBody::setVelocity(const Vector2& newVelocity)
{
    velocity = newVelocity;
}

void DynamicBody::setForce(const Vector2& newForce)
{
    force = newForce;
}

void DynamicBody::setAcceleration(const Vector2& newAcceleration)
{
    acceleration = newAcceleration;
}

void DynamicBody::setRestitution(float newRestitution)
{
    if (newRestitution >= 0 && newRestitution <= 1)
        restitution = newRestitution;
}

void DynamicBody::setMass(float newMass)
{
    if (newMass >= 0)
        mass = newMass;
}