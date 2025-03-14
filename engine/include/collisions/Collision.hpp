//Defenition of Collision struct to store pointers to two colliding bodies
//Also stores collision normal and penetration depth

#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "physics/PhysicsBody.hpp"

struct Collision
{
    PhysicsBody* bodyA;
    PhysicsBody* bodyB;
    Vector2 normal;
    float penDepth;

    Collision(PhysicsBody* bodyA, PhysicsBody* bodyB, const Vector2& normal, float penDepth)
        : bodyA(bodyA), bodyB(bodyB), normal(normal), penDepth(penDepth) {}
};

#endif