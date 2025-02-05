//Class defenition for physics bodies that are static in space
//Not affected by gravity
//Has a collider so other objects can collide with it
//Cannot be moved by other physics bodies
//Uses include grounds, walls, boundaries, etc

#ifndef STATIC_BODY_HPP
#define STATIC_BODY_HPP

#include "PhysicsBody.hpp"
#include "Vector2.hpp"

class StaticBody : public PhysicsBody
{
public:
    //Constructor to set position in world
    StaticBody(Vector2 initialPosition);

    //Static body not affected by force and physics
    void applyForce(Vector2 force) override;
    void update(float deltaTime) override;
};

#endif