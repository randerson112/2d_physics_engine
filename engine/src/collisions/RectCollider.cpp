//Class implementation for rectangle shape colliders

#include "collisions/RectCollider.hpp"
#include <cmath>

namespace phys
{
    //Constructor to set width and height of collider
    RectCollider::RectCollider(const Vector2& dimensions, ColliderType colliderType) :
        Collider(ColliderShape::Rectangle, colliderType), m_dimensions(dimensions)
    {
        //Create AABB to enclose rectangle shape
        m_boundingBox = AABB({m_position.x - m_dimensions.x / 2, m_position.y - m_dimensions.y / 2},
            {m_position.x + m_dimensions.x / 2, m_position.y + m_dimensions.y / 2});
    }

    //Returns the verticies of the collider in its current state
    const std::vector<Vector2> RectCollider::calculateVertcies()
    {
        float cos = std::cos(m_rotation);
        float sin = std::sin(m_rotation);

        float halfWidth = getWidth() / 2.0f;
        float halfHeight = getHeight() / 2.0f;

        //Standard vertecies without rotation
        const std::vector<Vector2> localVerticies = {
            {-halfWidth, halfHeight}, {halfWidth, halfHeight}, {halfWidth, -halfHeight}, {-halfWidth, -halfHeight}};

        //Calculate vertcies with rotation applied
        std::vector<Vector2> WorldVerticies;
        for (const Vector2& vertex : localVerticies)
        {
            float rotatedX = vertex.x * cos - vertex.y * sin;
            float rotatedY = vertex.x * sin + vertex.y * cos;
            WorldVerticies.emplace_back(rotatedX + m_position.x, rotatedY + m_position.y);
        }

        return WorldVerticies;
    }

    //Getters for member variables
    float RectCollider::getWidth() const
    {
        return m_dimensions.x;
    }

    float RectCollider::getHeight() const
    {
        return m_dimensions.y;
    }

    //Setters for member variables
    void RectCollider::setDimensions(const Vector2& newDimensions)
    {
        m_dimensions = newDimensions;
    }

    //Update AABB mins and maxes
    void RectCollider::updateAABB()
    {
        m_boundingBox.min = {m_position.x - m_dimensions.x / 2, m_position.y - m_dimensions.y / 2};
        m_boundingBox.max = {m_position.x + m_dimensions.x / 2, m_position.y + m_dimensions.y / 2};
    }
}