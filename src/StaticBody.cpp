//Class implementation for static physics bodies

#include "StaticBody.hpp"

StaticBody::StaticBody(Vector2 initialPosition) : PhysicsBody(initialPosition) {}

void StaticBody::applyForce(Vector2 force)
{
    //No forces applied to static body, it cannot be moved
}

void StaticBody::update(float deltaTime)
{
    //Static body does not get updated by physics
}