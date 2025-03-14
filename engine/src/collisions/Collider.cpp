//Base class implementation for colliders

#include "collisions/Collider.hpp"

//Constructor to set position and offset
Collider::Collider(ColliderShape shapeType)
: parent(nullptr), position({0, 0}), offset({0, 0}), shape(shapeType) {}

//Getters for member variables
const Vector2& Collider::getPosition() const
{
    return position;
}

const Vector2& Collider::getOffset() const
{
    return offset;
}
PhysicsBody* Collider::getParent() const
{
    return parent;
}

ColliderShape Collider::getShape() const
{
    return shape;
}

//Setters for member variables
void Collider::setPosition(const Vector2& newPosition)
{
    position = newPosition;
}

void Collider::setOffset(const Vector2& newOffest)
{
    offset = newOffest;
}

void Collider::setParent(PhysicsBody* newParent)
{
    parent = newParent;
    //Destroy old parent?
}