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

        //Calculate distance to other circle
        float distanceX = otherPos.x - thisPos.x;
        float distanceY = otherPos.y - thisPos.y;
        float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

        //Check if distance is less than sum of radii
        float sumRadii = thisRadius + otherRadius;
        if (distanceSquared <= (sumRadii * sumRadii))
        {
            return true;
        }
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

        //Calculate the distance between the closest point and the circle center
        float distanceX = thisPos.x - closestX;
        float distanceY = thisPos.y - closestY;
        float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

        //Compare with the squared radius
        if (distanceSquared <= (thisRadius * thisRadius))
        {
            return true;
        }
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