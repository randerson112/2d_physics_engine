#include "collisions/AABB.hpp"

//Constructor to set mins and maxes
AABB::AABB(Vector2 min, Vector2 max)
    : m_min(min), m_max(max) {}

//Getters for member variables
Vector2 AABB::getMin() const
{
    return m_min;
}

Vector2 AABB::getMax() const
{
    return m_max;
}

//Setters for member variables
void AABB::setMin(const Vector2& newMin)
{
    m_min = newMin;
}

void AABB::setMax(const Vector2& newMax)
{
    m_max = newMax;
}