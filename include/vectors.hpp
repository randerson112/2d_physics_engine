#ifndef VECTORS_HPP
#define VECTORS_HPP

#include <cmath>

class Vector
{
public:
    float x;
    float y;

    Vector(float x, float y) : x(x), y(y) {}

    Vector operator+(Vector other)
    {
        return {x + other.x, y + other.y};
    }

    void operator+=(Vector other)
    {
        x += other.x;
        y += other.y;
    }

    Vector operator-(Vector other)
    {
        return {x - other.x, y - other.y};
    }

    void operator-=(Vector other)
    {
        x -= other.x;
        y -= other.y;
    }

    Vector operator*(float scalar)
    {
        return {x * scalar, y * scalar};
    }

    void operator*=(float scalar)
    {
        x *= scalar;
        y *= scalar;
    }

    Vector operator/(float divisor)
    {
        return {x / divisor, y / divisor};
    }

    void operator/=(float divisor)
    {
        x /= divisor;
        y /= divisor;
    }

    Vector normalized()
    {
        float length = sqrt(x * x + y * y);
        return {x / length, y / length};
    }
};

#endif