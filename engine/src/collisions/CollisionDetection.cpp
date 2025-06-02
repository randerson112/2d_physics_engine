//Implementaion of collision detection functions

#include "collisions/CollisionDetection.hpp"
#include "core/Vector2.hpp"
#include <algorithm>

struct Collision;

namespace phys
{
    //Checks if two AABBs are overlapping
    bool CollisionDetection::checkAABBvsAABB(const AABB& boxA, const AABB& boxB)
    {
        //Get mins and maxes
        Vector2 minA = boxA.min;
        Vector2 maxA = boxA.max;

        Vector2 minB = boxB.min;
        Vector2 maxB = boxB.max;

        //Check for overlap
        if (maxA.x > minB.x && minA.x < maxB.x && maxA.y > minB.y && minA.y < maxB.y)
            return true;

        //No overlap
        return false;
    }

    //Sorts into respective function based on body shapes
    Collision* CollisionDetection::checkCollision(PhysicsBody* bodyA, PhysicsBody* bodyB)
    {
        //Get colliders
        Collider* colliderA = bodyA->getCollider();
        Collider* colliderB = bodyB->getCollider();

        //Get collider shapes
        ColliderShape shapeA = colliderA->getShape();
        ColliderShape shapeB = colliderB->getShape();

        //First collider is a rectangle
        if (shapeA == ColliderShape::Rectangle)
        {
            RectCollider* rectA = static_cast<RectCollider*>(colliderA);

            //Second collider is also a rectangle
            if (shapeB == ColliderShape::Rectangle)
            {
                RectCollider* rectB = static_cast<RectCollider*>(colliderB);

                //Check for rect-rect collision
                return checkRectRectCollision(rectA, rectB);
            }

            //Second collider is a circle
            else if (shapeB == ColliderShape::Circle)
            {
                CircleCollider* circleB = static_cast<CircleCollider*>(colliderB);

                //Check for rect-circle collision
                return checkRectCircleCollision(rectA, circleB);
            }
        }

        //First collider is a circle
        else if (shapeA == ColliderShape::Circle)
        {
            CircleCollider* circleA = static_cast<CircleCollider*>(colliderA);

            //Second collider is also a circle
            if (shapeB == ColliderShape::Circle)
            {
                CircleCollider* circleB = static_cast<CircleCollider*>(colliderB);

                //Check for circle-circle collision
                return checkCircleCircleCollision(circleA, circleB);
            }

            //Second collider is a rectangle
            else if (shapeB == ColliderShape::Rectangle)
            {
                RectCollider* rectB = static_cast<RectCollider*>(colliderB);

                //Check for rect-circle collision
                return checkRectCircleCollision(rectB, circleA);
            }
        }

        return nullptr;
    }

    //Calculate collision between two rectangle colliders
    Collision* CollisionDetection::checkRectRectCollision(RectCollider* rectA, RectCollider* rectB)
    {
        //Get positions of centers
        Vector2 rectAPos = rectA->getPosition();
        Vector2 rectBPos = rectB->getPosition();

        //Get widths and heights
        float rectAWidth = rectA->getWidth();
        float rectAHeight = rectA->getHeight();

        float rectBWidth = rectB->getWidth();
        float rectBHeight = rectB->getHeight();

        //Calculate side bounds
        float rectALeft = rectAPos.x - rectAWidth / 2;
        float rectATop = rectAPos.y - rectAHeight / 2;
        float rectARight = rectAPos.x + rectAWidth / 2;
        float rectABottom = rectAPos.y + rectAHeight / 2;

        float rectBLeft = rectBPos.x - rectBWidth / 2;
        float rectBTop = rectBPos.y - rectBHeight / 2;
        float rectBRight = rectBPos.x + rectBWidth / 2;
        float rectBBottom = rectBPos.y + rectBHeight / 2;

        //Check for overlap
        if (rectARight > rectBLeft && rectALeft < rectBRight && rectABottom > rectBTop && rectATop < rectBBottom)
        {
            // Compute penetration depth on both axes
            float xOverlap = std::min(rectARight - rectBLeft, rectBRight - rectALeft);
            float yOverlap = std::min(rectABottom - rectBTop, rectBBottom - rectATop);

            //Declare variables for normal and penetration depth
            Vector2 normal;
            float penDepth;

            //Horizontal collision
            if (xOverlap <= yOverlap)
            {
                normal = (rectAPos.x < rectBPos.x) ? Vector2(1, 0) : Vector2(-1, 0);
                penDepth = xOverlap;
            }

            //Vertical collision
            else
            {
                normal = (rectAPos.y < rectBPos.y) ? Vector2(0, 1) : Vector2(0, -1);
                penDepth = yOverlap;
            }

            //Return a collision object
            return new Collision(rectA->getParent(), rectB->getParent(), normal, penDepth);
        }

        //If no collision is detected
        return nullptr;
    }

    //Calculate collision between two circle colliders
    Collision* CollisionDetection::checkCircleCircleCollision(CircleCollider* circleA, CircleCollider* circleB)
    {
        //Get positions of centers
        Vector2 circleAPos = circleA->getPosition();
        Vector2 circleBPos = circleB->getPosition();

        //Get radii
        float circleARadius = circleA->getRadius();
        float circleBRadius = circleB->getRadius();

        float sumRadii = circleARadius + circleBRadius;

        //Calculate distance squared between circles
        Vector2 vectorBetweenCenters = circleAPos.getVectorTo(circleBPos);
        float distanceSquared = vectorBetweenCenters.getSquare();

        //Check if distance squared is less than sum of radii squared
        if (distanceSquared <= (sumRadii * sumRadii))
        {
            //Get the normal and penetration depth of the collision
            Vector2 normal = circleAPos.getDirectionTo(circleBPos);
            float penDepth = sumRadii - (circleAPos.getVectorTo(circleBPos)).getLength();

            //Return a collision object
            return new Collision(circleA->getParent(), circleB->getParent(), normal, penDepth);
        }

        //If no collision is detected
        return nullptr;
    }

    //Calculate collision between a rectangle and a circle collider
    Collision* CollisionDetection::checkRectCircleCollision(RectCollider* rect, CircleCollider* circle)
    {
        //Get the rectangle center position
        Vector2 rectPos = rect->getPosition();

        //Get the circle center position and radius
        Vector2 circlePos = circle->getPosition();
        float circleRadius = circle->getRadius();

        //Get rectangle width and height
        float rectWidth = rect->getWidth();
        float rectHeight = rect->getHeight();

        //Find point on the rectangle closest to the circle center
        float closestX = std::clamp(circlePos.x, rectPos.x - rectWidth / 2, rectPos.x + rectWidth / 2);
        float closestY = std::clamp(circlePos.y, rectPos.y - rectHeight / 2, rectPos.y + rectHeight / 2);
        Vector2 closestPoint = {closestX, closestY};

        //Calculate the distance between the closest point and the circle center
        Vector2 vectorBetween = closestPoint.getVectorTo(circlePos);
        float distanceSquared = vectorBetween.getSquare();

        //Check if circle center is inside the rectangle
        if (closestX == circlePos.x && closestY == circlePos.y)
        {
            // Circle is inside the rectangle, push it outward
            Vector2 rectCenterToCircle = rectPos.getDirectionTo(circlePos);

            // Avoid zero-length normal
            if (rectCenterToCircle.x == 0 && rectCenterToCircle.y == 0)
            {
                rectCenterToCircle = Vector2(1, 0); // Arbitrary normal
            }

            //Return a collision object
            return new Collision(rect->getParent(), circle->getParent(), rectCenterToCircle, circleRadius);
        }

        //Get radius squared
        float circleRadiusSquared = circleRadius * circleRadius;

        //Compare distance squared with the squared radius
        if (distanceSquared < circleRadiusSquared)
        {
            //Get the normal and penetration depth of the collision
            Vector2 normal = closestPoint.getDirectionTo(circlePos);
            float penDepth = circleRadius - sqrt(distanceSquared);

            //Return a collision object
            return new Collision(rect->getParent(), circle->getParent(), normal, penDepth);
        }

        //If no collision is detected
        return nullptr;
    }
}