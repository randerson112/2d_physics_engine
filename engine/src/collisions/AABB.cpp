#include "collisions/AABB.hpp"

//Constructor to set mins and maxes
AABB::AABB(Vector2 min, Vector2 max)
    : m_min(min), m_max(max) {}

//Getters for member variables
Vector2 AABB::getMin()
{
    return m_min;
}

Vector2 AABB::getMax()
{
    return m_max;
}