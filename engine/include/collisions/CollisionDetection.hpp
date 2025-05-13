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

//Data structure for storing axis projection data
struct Projection
{
    float min;
    float max;

    Projection(float min, float max)
        : min(min), max(max) {}
};

namespace CollisionDetection
{
    //Checks if two AABBs are overlapping
    bool checkAABBvsAABB(const AABB& boxA, const AABB& boxB);

    //Calculate collision between two polygons using SAT
    Collision* checkPolygonCollision(RectCollider* polygonA, RectCollider* polygonB);

    //Calculate collision between a circle and polygon using SAT
    Collision* checkCirclePolygonCollision(CircleCollider* circle, RectCollider* polygon);

    //Returns the min and max of a polygon projected onto an axis
    const Projection projectPolygonOntoAxis(const std::vector<Vector2>& vertices, const Vector2& axis);

    //Returns the min and max of a circle projected onto an axis
    const Projection projectCircleOntoAxis(const Vector2& center, float radius, const Vector2& axis);

    //Find closest point on polygon to circle center, returns the index
    int findClosestPointToCenter(const Vector2& center, const std::vector<Vector2>& vertices);

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