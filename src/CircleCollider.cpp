//Class implementation for circle shape colliders

#include "CircleCollider.hpp"
#include "RectCollider.hpp"
#include <algorithm>

//Constructor to set radius
CircleCollider::CircleCollider(float initialRadius)
    : Collider(ColliderShape::Circle), radius(initialRadius) {}

//Checks for collision with another collider
bool CircleCollider::checkCollision(Collider* otherCollider)
{
    //Check collision with another circle
    if (otherCollider->getShape() == ColliderShape::Circle)
    {
        CircleCollider* other = static_cast<CircleCollider*>(otherCollider);

        //Get positions
        Vector2 thisPos = getPosition();
        Vector2 otherPos = other->getPosition();

        //Get radii
        float thisRadius = getRadius();
        float otherRadius = other->getRadius();

        //Calculate distance squared to other circle
        Vector2 distanceBetweenCenters = thisPos.getDistanceTo(otherPos);
        float distanceSquared = distanceBetweenCenters.getSquare();

        //Check if distance squared is less than sum of radii squared
        float sumRadii = thisRadius + otherRadius;
        return (distanceSquared <= (sumRadii * sumRadii));
    }

    //Check collision with a rectangle
    else if (otherCollider->getShape() == ColliderShape::Rectangle)
    {
        RectCollider* other = static_cast<RectCollider*>(otherCollider);

        //Get the circle position and radius
        Vector2 thisPos = getPosition();
        float thisRadius = getRadius();

        //Get the rectangle position
        Vector2 otherPos = other->getPosition();

        //Find closest point on the rectangle to the circle
        float closestX = std::max(otherPos.x - other->getWidth() / 2, std::min(thisPos.x, otherPos.x + other->getWidth() / 2));
        float closestY = std::max(otherPos.y - other->getHeight() / 2, std::min(thisPos.y, otherPos.y + other->getHeight() / 2));
        Vector2 closestPoint = {closestX, closestY};

        //Calculate the distance between the closest point and the circle center
        Vector2 distance = closestPoint.getDistanceTo(thisPos);
        float distanceSquared = distance.getSquare();

        //Compare with the squared radius
        return (distanceSquared <= (thisRadius * thisRadius));
    }
}

//Getters for member variables
float CircleCollider::getRadius()
{
    return radius;
}

//Setters for member variables
void CircleCollider::setRadius(float newRadius)
{
    if (radius >= 0)
    {
        radius = newRadius; //Ensure non-negative radius
    }
}