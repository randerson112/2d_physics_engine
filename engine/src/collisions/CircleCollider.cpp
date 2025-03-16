//Class implementation for circle shape colliders

#include "collisions/CircleCollider.hpp"

//Constructor to set radius and collider type
CircleCollider::CircleCollider(float initialRadius, ColliderType type)
    : Collider(ColliderShape::Circle, type), radius(initialRadius) {}

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
    }
}