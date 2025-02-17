//Namespace for all collision detection functions
//Check collision method sorts into respective method

#ifndef COLLISION_DETECTION_HPP
#define COLLISION_DETECTION_HPP

#include "collisions/RectCollider.hpp"
#include "collisions/CircleCollider.hpp"
#include "collisions/Collision.hpp"

namespace CollisionDetection
{
    //Sorts into respective function based on body shapes
    Collision* checkCollision(PhysicsBody* bodyA, PhysicsBody* bodyB);

    //Calculate collision between two rectangle colliders
    Collision* checkRectRectCollision(RectCollider* rectA, RectCollider* rectB);

    //Calculate collision between two circle colliders
    Collision* checkCircleCircleCollision(CircleCollider* circleA, CircleCollider* circleB);

    //Calculate collision between a rectangle and a circle collider
    Collision* checkRectCircleCollision(RectCollider* rect, CircleCollider* circle);
}

#endif