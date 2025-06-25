//Class implementation for static physics bodies

#include "physics/StaticBody.hpp"

namespace phys
{
    //Sets position and collider
    StaticBody::StaticBody(const Vector2& position, Collider* collider) :
        PhysicsBody(position, collider, BodyType::StaticBody)
    {
    }

    void StaticBody::update(float deltaTime)
    {
        //Not updated by physics
    }
}