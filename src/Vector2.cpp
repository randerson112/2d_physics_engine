//Class implementation for 2D vectors

#include "Vector2.hpp"

//Default constructor
Vector2::Vector2() : x(0), y(0) {}

//Constructor with given x and y values
Vector2::Vector2(float x, float y) : x(x), y(y) {}

//Adding vectors
Vector2 Vector2::operator+(Vector2 other)
{
    return {x + other.x, y + other.y};
}

//Subtracting vectors
Vector2 Vector2::operator-(Vector2 other)
{
    return {x - other.x, y - other.y};
}

//Multiplying a vector by a scalar value
Vector2 Vector2::operator*(float scalar)
{
    return {x * scalar, y * scalar};
}

//Dividing a vector by a divisor value
Vector2 Vector2::operator/(float divisor)
{
    return {x / divisor, y / divisor};
}

//Addition assignment
void Vector2::operator+=(Vector2 other)
{
    x += other.x;
    y += other.y;
}

//Subtraction assignment
void Vector2::operator-=(Vector2 other)
{
    x -= other.x;
    y -= other.y;
}

//Multiplication assignment
void Vector2::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;
}

//Division assignment
void Vector2::operator/=(float divisor)
{
    x /= divisor;
    y /= divisor;
}

//Gets the normal of a vector, length 1
Vector2 Vector2::getNormal()
{
    float length = sqrt(x * x + y * y);
    return {x / length, y / length};
}

//Gets the distance to another vector
Vector2 Vector2::getDistanceTo(Vector2 other)
{
    return {other.x - x, other.y - y};
}

//Gets the direction to another vector, length of 1
Vector2 Vector2::getDirectionTo(Vector2 other)
{
    return getDistanceTo(other).getNormal();
}

float Vector2::getSquare()
{
    return (x * x) + (y * y);
}

