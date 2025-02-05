//Base class implementation for colliders

#include "Collider.hpp"

//Constructor to set position and offset
Collider::Collider(Vector2 initialPosition, Vector2 offset, ColliderShape shapeType)
: position(initialPosition), offset(offset), parent(nullptr), shape(shapeType) {}

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
}