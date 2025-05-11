//Namespace for all collision detection functions
//Check collision method sorts into respective method

#ifndef COLLISION_DETECTION_HPP
#define COLLISION_DETECTION_HPP

#include "collisions/AABB.hpp"
#include "collisions/RectCollider.hpp"
#include "collisions/CircleCollider.hpp"
#include "collisions/Collision.hpp"
#include <vector>

namespace phys
{
namespace CollisionDetection
{
    //Checks if two AABBs are overlapping
    bool checkAABBvsAABB(const AABB& boxA, const AABB& boxB);

    //Checks if two polygons are intersecting using SAT
    bool checkPolygonCollision(const std::vector<Vector2>& verticiesA, const std::vector<Vector2>& verticiesB);

    //Returns the min and max of verticies projected onto an axis in a Vector2 struct
    const Vector2 projectVerticiesOntoAxis(const std::vector<Vector2>& vertcies, const Vector2& axis);

    //Sorts into respective function based on body shapes
    Collision* checkCollision(PhysicsBody* bodyA, PhysicsBody* bodyB);

    //Calculate collision between two rectangle colliders
    Collision* checkRectRectCollision(RectCollider* rectA, RectCollider* rectB);

    //Calculate collision between two circle colliders
    Collision* checkCircleCircleCollision(CircleCollider* circleA, CircleCollider* circleB);

    //Calculate collision between a rectangle and a circle collider
    Collision* checkRectCircleCollision(RectCollider* rect, CircleCollider* circle);
}
}

#endif