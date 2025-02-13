//Implementaion of collision detection functions

#include "collisions/CollisionDetection.hpp"
#include "core/Vector2.hpp"
#include <algorithm>

//Sorts into respective function based on body shapes
bool CollisionDetection::checkCollision(Collider* colliderA, Collider* colliderB)
{
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
}

//Calculate collision between two rectangle colliders
bool CollisionDetection::checkRectRectCollision(RectCollider* rectA, RectCollider* rectB)
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
    return (rectARight > rectBLeft &&
            rectALeft < rectBRight &&
            rectABottom > rectBTop &&
            rectATop < rectBBottom);
}

//Calculate collision between two circle colliders
bool CollisionDetection::checkCircleCircleCollision(CircleCollider* circleA, CircleCollider* circleB)
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
    return (distanceSquared <= (sumRadii * sumRadii));
}

//Calculate collision between a rectangle and a circle collider
bool CollisionDetection::checkRectCircleCollision(RectCollider* rect, CircleCollider* circle)
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

    //Compare with the squared radius
    return (distanceSquared < (circleRadius * circleRadius));
}