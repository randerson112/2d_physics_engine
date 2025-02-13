//Class implementation for static physics bodies

#include "physics/StaticBody.hpp"

//Sets position and collider
StaticBody::StaticBody(Vector2 initialPosition, Collider* colliderInstance)
    : PhysicsBody(initialPosition, colliderInstance, BodyType::StaticBody) {}

void StaticBody::update(float deltaTime)
{
    //Not updated by physics
}