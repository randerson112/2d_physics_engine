//Base class implementation for colliders

#include "collisions/Collider.hpp"

namespace phys
{
    //Constructor to set shape and collider type
    Collider::Collider(ColliderShape colliderShape, ColliderType colliderType) :
        m_parent(nullptr),
        m_position({0, 0}),
        m_offset({0, 0}),
        m_shape(colliderShape),
        m_type(colliderType),
        m_boundingBox(AABB())
    {
    }

    //Destructor
    Collider::~Collider() = default;

    //Getters for member variables
    const Vector2& Collider::getPosition() const
    {
        return m_position;
    }

    const Vector2& Collider::getOffset() const
    {
        return m_offset;
    }
    PhysicsBody* Collider::getParent() const
    {
        return m_parent;
    }

    ColliderShape Collider::getShape() const
    {
        return m_shape;
    }

    ColliderType Collider::getType() const
    {
        return m_type;
    }

    const AABB& Collider::getAABB() const
    {
        return m_boundingBox;
    }

    //Setters for member variables
    void Collider::setPosition(const Vector2& newPosition)
    {
        m_position = newPosition;

        updateAABB();
    }

    void Collider::setOffset(const Vector2& newOffest)
    {
        m_offset = newOffest;
    }

    void Collider::setParent(PhysicsBody* newParent)
    {
        m_parent = newParent;
        //Destroy old parent?
    }

    void Collider::setType(ColliderType newType)
    {
        m_type = newType;
    }
}