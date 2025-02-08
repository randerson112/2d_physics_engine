//Namespace for all collision detection functions
//Resolve collision method sorts into respective method

#ifndef COLLISION_DETECTION_HPP
#define COLLISION_DETECTION_HPP

#include "RectCollider.hpp"
#include "CircleCollider.hpp"

namespace CollisionDetection
{
    //Sorts into respective function based on body shapes
    bool checkCollision(Collider* colliderA, Collider* colliderB);

    //Calculate collision between two rectangle colliders
    bool checkRectRectCollision(RectCollider* rectA, RectCollider* rectB);

    //Calculate collision between two circle colliders
    bool checkCircleCircleCollision(CircleCollider* circleA, CircleCollider* circleB);

    //Calculate collision between a rectangle and a circle collider
    bool checkRectCircleCollision(RectCollider* rect, CircleCollider* circle);
}

#endif