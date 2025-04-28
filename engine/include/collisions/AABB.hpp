//Struct defenition for Axis Aligined Bounding Boxes (AABB)

#ifndef AABB_HPP
#define AABB_HPP

#include "core/Vector2.hpp"

struct AABB
{
    //Min x and y
    Vector2 min;

    //Max x and y
    Vector2 max;

    //Default constructor
    AABB() : min(Vector2()), max(Vector2()) {}

    //Constructor to set mins and maxes
    AABB(const Vector2& min, const Vector2& max)
        : min(min), max(max) {}
};

#endif