//Base class implementation for colliders

#include "collisions/Collider.hpp"

//Constructor to set position and offset
Collider::Collider(ColliderShape shapeType)
: parent(nullptr), position({0, 0}), offset({0, 0}), shape(shapeType) {}

//Getters for member variables
Vector2 Collider::getPosition()
{
    return position;
}

Vector2 Collider::getOffset()
{
    return offset;
}
PhysicsBody* Collider::getParent()
{
    return parent;
}

ColliderShape Collider::getShape()
{
    return shape;
}

//Setters for member variables
void Collider::setPosition(Vector2 newPosition)
{
    position = newPosition;
}

void Collider::setOffset(Vector2 newOffest)
{
    offset = newOffest;
}

void Collider::setParent(PhysicsBody* newParent)
{
    parent = newParent;
    //Destroy old parent?
}