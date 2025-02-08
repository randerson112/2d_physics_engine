//Class implementation for rectangle shape colliders

#include "RectCollider.hpp"
#include "CircleCollider.hpp"
#include <algorithm>

//Constructor to set width and height of collider
RectCollider::RectCollider(float width, float height)
    : Collider(ColliderShape::Rectangle), width(width), height(height) {}

//Checks for collision with another collider
bool RectCollider::checkCollision(Collider* otherCollider)
{
    //Check collision with another rectangle
    if (otherCollider->getShape() == ColliderShape::Rectangle)
    {
        RectCollider* other = static_cast<RectCollider*>(otherCollider);

        //Get positions
        Vector2 thisPos = getPosition();
        Vector2 otherPos = other->getPosition();

        //Calculate bounds
        float thisLeft = thisPos.x - width / 2;
        float thisTop = thisPos.y - height / 2;
        float thisRight = thisPos.x + width / 2;
        float thisBottom = thisPos.y + height / 2;

        float otherLeft = otherPos.x - width / 2;
        float otherTop = otherPos.y - height / 2;
        float otherRight = otherPos.x + width / 2;
        float otherBottom = otherPos.y + height / 2;

        //Check for overlap
        return (thisRight > otherLeft && thisLeft < otherRight && thisBottom > otherTop && thisTop < otherBottom);
    }

    //Check collision with a circle
    else if (otherCollider->getShape() == ColliderShape::Circle)
    {
        CircleCollider* other = static_cast<CircleCollider*>(otherCollider);

        //Get the rectangle position
        Vector2 thisPos = getPosition();

        //Get the circle position and radius
        Vector2 otherPos = other->getPosition();
        float otherRadius = other->getRadius();

        //Find closest point on the rectangle to the circle
        float closestX = std::max(thisPos.x - width / 2, std::min(otherPos.x, thisPos.x + width / 2));
        float closestY = std::max(thisPos.y - height / 2, std::min(otherPos.y, thisPos.y + height / 2));
        Vector2 closestPoint = {closestX, closestY};

        //Calculate the distance between the closest point and the circle center
        Vector2 distance = closestPoint.getDistanceTo(otherPos);
        float distanceSquared = distance.getSquare();

        //Compare with the squared radius
        return (distanceSquared < (otherRadius * otherRadius));
    }
}

//Getters for member variables
float RectCollider::getWidth()
{
    return width;
}

float RectCollider::getHeight()
{
    return height;
}

//Setters for member variables
void RectCollider::setWidth(float newWidth)
{
    if (newWidth >= 0)
    {
        width = newWidth;
    }
}

void RectCollider::setHeight(float newHeight)
{
    if (newHeight >= 0)
    {
        height = newHeight;
    }
}