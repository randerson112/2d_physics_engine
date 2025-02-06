//Class implementation for circle shape colliders

#include "CircleCollider.hpp"

//Constructor to set radius
CircleCollider::CircleCollider(float initialRadius)
    : Collider(ColliderShape::Circle), radius(initialRadius) {}

//Checks for collision with another collider
PhysicsBody* CircleCollider::checkCollision(Collider& otherCollider)
{
    //Implement later
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