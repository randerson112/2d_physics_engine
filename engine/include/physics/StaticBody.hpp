//Class defenition for physics bodies that are static in space
//Not affected by gravity
//Has a collider so other objects can collide with it
//Cannot be moved by other physics bodies
//Uses include grounds, walls, boundaries, etc

#ifndef STATIC_BODY_HPP
#define STATIC_BODY_HPP

#include "physics/PhysicsBody.hpp"
#include "core/Vector2.hpp"

namespace phys
{
class StaticBody : public PhysicsBody
{
public:
    //Constructor to set position in world and attach collider
    StaticBody(const Vector2& initialPosition, Collider* colliderInstance);

    //Nothing will happen here since body is static
    void update(float deltaTime) override;
};
}

#endif