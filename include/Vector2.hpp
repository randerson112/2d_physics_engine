//Class defentions for 2D vectors
//Stores an x and y value

#ifndef Vector2_HPP
#define Vector2_HPP

#include <cmath>

class Vector2
{
public:
    float x;
    float y;

    Vector2(float x, float y) : x(x), y(y) {}

    Vector2 operator+(Vector2 other)
    {
        return {x + other.x, y + other.y};
    }

    void operator+=(Vector2 other)
    {
        x += other.x;
        y += other.y;
    }

    Vector2 operator-(Vector2 other)
    {
        return {x - other.x, y - other.y};
    }

    void operator-=(Vector2 other)
    {
        x -= other.x;
        y -= other.y;
    }

    Vector2 operator*(float scalar)
    {
        return {x * scalar, y * scalar};
    }

    void operator*=(float scalar)
    {
        x *= scalar;
        y *= scalar;
    }

    Vector2 operator/(float divisor)
    {
        return {x / divisor, y / divisor};
    }

    void operator/=(float divisor)
    {
        x /= divisor;
        y /= divisor;
    }

    Vector2 normalized()
    {
        float length = sqrt(x * x + y * y);
        return {x / length, y / length};
    }
};

#endif