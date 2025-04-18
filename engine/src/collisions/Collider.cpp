//Base class implementation for colliders

#include "collisions/Collider.hpp"

//Constructor to set shape and collider type
Collider::Collider(ColliderShape shapeType, ColliderType type)
: parent(nullptr), position({0, 0}), offset({0, 0}), shape(shapeType), type(type), boundingBox(nullptr) {}

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

ColliderType Collider::getType() const
{
    return type;
}

AABB* Collider::getAABB() const
{
    return boundingBox;
}

//Setters for member variables
void Collider::setPosition(const Vector2& newPosition)
{
    position = newPosition;

    updateAABB();
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

void Collider::setType(ColliderType newType)
{
    type = newType;
}