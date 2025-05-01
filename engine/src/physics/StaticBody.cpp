//Class implementation for static physics bodies

#include "physics/StaticBody.hpp"

namespace phys
{
//Sets position and collider
StaticBody::StaticBody(const Vector2& initialPosition, Collider* colliderInstance)
    : PhysicsBody(initialPosition, colliderInstance, BodyType::StaticBody) {}

void StaticBody::update(float deltaTime)
{
    //Not updated by physics
}
}