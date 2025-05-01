//Class implementation for circle shape colliders

#include "collisions/CircleCollider.hpp"

namespace phys
{
//Constructor to set radius and collider type
CircleCollider::CircleCollider(float radius, ColliderType colliderType)
    : Collider(ColliderShape::Circle, colliderType), m_radius(radius)
    {
        //Create AABB to enclose circle shape
        m_boundingBox = AABB({m_position.x - m_radius, m_position.y - m_radius}, {m_position.x + m_radius, m_position.y + m_radius});
    }

//Getters for member variables
float CircleCollider::getRadius() const
{
    return m_radius;
}

//Setters for member variables
void CircleCollider::setRadius(float newRadius)
{
    if (m_radius >= 0)
    {
        m_radius = newRadius; //Ensure non-negative radius

        updateAABB();
    }
}

void CircleCollider::updateAABB()
{
    m_boundingBox.min = {m_position.x - m_radius, m_position.y - m_radius};
    m_boundingBox.max = {m_position.x + m_radius, m_position.y + m_radius};
}
}