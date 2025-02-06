//Base class implementation for physics bodies

#include "PhysicsBody.hpp"

//Constructor and deconstructor
PhysicsBody::PhysicsBody(Vector2 initialPosition, Collider* colliderInstance)
    : position(initialPosition), collider(colliderInstance)
    {
        collider->setPosition(position); //Set the position of the collider to body position
    }

PhysicsBody::~PhysicsBody()
{
    delete collider;
}

//Getters for member variables
Vector2 PhysicsBody::getPosition() const
{
    return position;
}

Collider* PhysicsBody::getCollider() const
{
    return collider;
}

//Setters for member variables
void PhysicsBody::setPosition(Vector2 newPosition)
{
    position = newPosition;
    collider->setPosition(position); //Also move collider to new position
}

void PhysicsBody::setCollider(Collider* newCollider)
{
    if (collider != nullptr) //If there is an active collider already
    {
        delete collider; //Delete current collider
    }

    collider = newCollider;
}