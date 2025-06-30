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
        m_boundingBox(AABB()),
        m_collisionLayers({0}),
        m_collisionMasks({0})
    {
    }

    //Destructor
    Collider::~Collider() = default;

    //Rotate collider by amount of radians
    void Collider::rotate(float radians)
    {
        m_rotation += radians;
    }

    //Getters for member variables
    const Vector2& Collider::getPosition() const
    {
        return m_position;
    }

    float Collider::getRotation() const
    {
        return m_rotation;
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

    void Collider::setRotation(float newRotation)
    {
        m_rotation = newRotation;
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

    //Collision layers and masks
    const std::vector<unsigned int>& Collider::getCollisionLayers() const
    {
        return m_collisionLayers;
    }

    const std::vector<unsigned int>& Collider::getCollisionMasks() const
    {
        return m_collisionMasks;
    }

    void Collider::setCollisionLayers(const std::vector<unsigned int>& newLayers)
    {
        m_collisionLayers = newLayers;
    }

    void Collider::setCollisionMasks(const std::vector<unsigned int>& newMasks)
    {
        m_collisionMasks = newMasks;
    }

    void Collider::addCollisionLayer(unsigned int newLayer)
    {
        if (std::find(m_collisionLayers.begin(), m_collisionLayers.end(), newLayer) == m_collisionLayers.end())
            m_collisionLayers.push_back(newLayer);
    }

    void Collider::addCollisionMask(unsigned int newMask)
    {
        if (std::find(m_collisionMasks.begin(), m_collisionMasks.end(), newMask) == m_collisionMasks.end())
            m_collisionMasks.push_back(newMask);
    }

    void Collider::removeCollisionLayer(unsigned int layer)
    {
        auto it = std::find(m_collisionLayers.begin(), m_collisionLayers.end(), layer);
        if (it != m_collisionLayers.end())
            m_collisionLayers.erase(it);
    }

    void Collider::removeCollisionMask(unsigned int mask)
    {
        auto it = std::find(m_collisionMasks.begin(), m_collisionMasks.end(), mask);
        if (it != m_collisionMasks.end())
            m_collisionMasks.erase(it);
    }

    bool Collider::isOnLayer(unsigned int layer)
    {
        return std::find(m_collisionLayers.begin(), m_collisionLayers.end(), layer) != m_collisionLayers.end();
    }

    bool Collider::collidesWithLayer(unsigned int layer)
    {
        return std::find(m_collisionMasks.begin(), m_collisionMasks.end(), layer) != m_collisionMasks.end();
    }
}