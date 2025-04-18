//Class implementation for rectangle shape colliders

#include "collisions/RectCollider.hpp"

//Constructor to set width and height of collider
RectCollider::RectCollider(Vector2 dimensions, ColliderType type)
    : Collider(ColliderShape::Rectangle, type), width(dimensions.x), height(dimensions.y)
    {
        //Create AABB to enclose rectangle shape
        boundingBox = new AABB({position.x - width / 2, position.y + height / 2}, {position.x + width / 2, position.y - height / 2});
    }

//Getters for member variables
float RectCollider::getWidth() const
{
    return width;
}

float RectCollider::getHeight() const
{
    return height;
}

//Setters for member variables
void RectCollider::setWidth(float newWidth)
{
    if (newWidth >= 0)
    {
        width = newWidth;
        updateAABB();
    }
}

void RectCollider::setHeight(float newHeight)
{
    if (newHeight >= 0)
    {
        height = newHeight;
        updateAABB();
    }
}

//Update AABB mins and maxes
void RectCollider::updateAABB()
{
    boundingBox->setMin({position.x - width / 2, position.y + height / 2});
    boundingBox->setMax({position.x + width / 2, position.y - height / 2});
}