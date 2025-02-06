//Class implementation for rectangle shape colliders

#include "RectCollider.hpp"

//Constructor to set width and height of collider
RectCollider::RectCollider(float width, float height)
    : Collider(ColliderShape::Rectangle), width(width), height(height) {}

//Checks for collision with another collider
PhysicsBody* RectCollider::checkCollision(Collider& otherCollider)
{
    //Implement later
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