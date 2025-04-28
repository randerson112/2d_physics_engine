#include "collisions/AABB.hpp"

//Default constructor
AABB::AABB() : min(Vector2()), max(Vector2()) {}

//Constructor to set mins and maxes
AABB::AABB(const Vector2& min, const Vector2& max)
    : min(min), max(max) {}