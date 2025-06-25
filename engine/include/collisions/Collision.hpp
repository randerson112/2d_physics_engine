//Defenition of Collision struct to store pointers to two colliding bodies
//Also stores collision normal and penetration depth

#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "physics/PhysicsBody.hpp"
#include "core/Vector2.hpp"
#include <vector>

namespace phys
{
    struct Collision
    {
        PhysicsBody* bodyA;
        PhysicsBody* bodyB;
        Vector2 normal;
        float penDepth;
        std::vector<Vector2> contactPoints;
        int contactCount;

        Collision(PhysicsBody* bodyA,
            PhysicsBody* bodyB,
            const Vector2& normal,
            float penDepth,
            std::vector<Vector2>& collisionPoints,
            int collisionCount) :
            bodyA(bodyA),
            bodyB(bodyB),
            normal(normal),
            penDepth(penDepth),
            contactPoints(collisionPoints),
            contactCount(collisionCount)
        {
        }
    };
}

#endif