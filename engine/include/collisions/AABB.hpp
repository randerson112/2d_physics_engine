//Class defenition for Axis Aligined Bounding Boxes (AABB)

#ifndef AABB_HPP
#define AABB_HPP

#include "core/Vector2.hpp"

class AABB
{
public:
    //Constructor to set mins and maxes
    AABB(Vector2 min, Vector2 max);

    //Getters for member variables
    Vector2 getMin();
    Vector2 getMax();

private:
    //Min x and y
    Vector2 m_min;

    //Max x and y
    Vector2 m_max;
};

#endif