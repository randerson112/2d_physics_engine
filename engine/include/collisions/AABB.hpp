//Struct defenition for Axis Aligined Bounding Boxes (AABB)

#ifndef AABB_HPP
#define AABB_HPP

#include "core/Vector2.hpp"

namespace phys
{
    struct AABB
    {
        //Min x and y
        Vector2 min;

        //Max x and y
        Vector2 max;

        //Default constructor
        AABB() : min(Vector2()), max(Vector2()) {}

        //Constructor to set mins and maxes
        AABB(const Vector2& min, const Vector2& max) : min(min), max(max) {}

        // Checks if AABB is intersecting another
        bool intersects(const AABB& other) const
        {
            return (max.x >= other.min.x && min.x <= other.max.x && max.y >= other.min.y && min.y <= other.max.y);
        }

        // Checks if another AABB is fully inside this AABB
        bool contains(const AABB& other) const
        {
            return (min.x <= other.min.x && max.x >= other.max.x && min.y <= other.min.y && max.y >= other.max.y);
        }
    };
}

#endif