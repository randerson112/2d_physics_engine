//Class implementation for circle shape colliders

#include "collisions/CircleCollider.hpp"

//Constructor to set radius and collider type
CircleCollider::CircleCollider(float initialRadius, ColliderType type)
    : Collider(ColliderShape::Circle, type), radius(initialRadius)
    {
        //Create AABB to enclose circle shape
        boundingBox = AABB({position.x - radius, position.y - radius}, {position.x + radius, position.y + radius});
    }

//Getters for member variables
float CircleCollider::getRadius() const
{
    return radius;
}

//Setters for member variables
void CircleCollider::setRadius(float newRadius)
{
    if (radius >= 0)
    {
        radius = newRadius; //Ensure non-negative radius

        updateAABB();
    }
}

void CircleCollider::updateAABB()
{
    boundingBox.min = {position.x - radius, position.y - radius};
    boundingBox.max = {position.x + radius, position.y + radius};
}