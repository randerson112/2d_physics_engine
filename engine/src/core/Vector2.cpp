//Class implementation for 2D vectors

#include "core/Vector2.hpp"

//Default constructor
Vector2::Vector2() : x(0), y(0) {}

//Constructor with given x and y values
Vector2::Vector2(float x, float y) : x(x), y(y) {}

//Adding vectors
Vector2 Vector2::operator+(const Vector2& other) const
{
    return {x + other.x, y + other.y};
}

//Subtracting vectors
Vector2 Vector2::operator-(const Vector2& other) const
{
    return {x - other.x, y - other.y};
}

//Multiplying a vector by a scalar value
Vector2 Vector2::operator*(float scalar) const
{
    return {x * scalar, y * scalar};
}

//Dividing a vector by a divisor value
Vector2 Vector2::operator/(float divisor) const
{
    return {x / divisor, y / divisor};
}

//Addition assignment
void Vector2::operator+=(const Vector2& other)
{
    x += other.x;
    y += other.y;
}

//Subtraction assignment
void Vector2::operator-=(const Vector2& other)
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

//Negative operator for getting the inverse
Vector2 Vector2::operator-() const
{
    return {-x, -y};
}

//Gets the normal of a vector, length 1
Vector2 Vector2::getNormal() const
{
    float length = getLength();
    return {x / length, y / length};
}

//Returns the magnitude or length of a vector
float Vector2::getLength() const
{
    return sqrt((x * x) + (y * y));
}

//Gets the vector pointing to another vector
Vector2 Vector2::getVectorTo(const Vector2& other) const
{
    return {other.x - x, other.y - y};
}

//Gets the direction to another vector, length of 1
Vector2 Vector2::getDirectionTo(const Vector2& other) const
{
    return getVectorTo(other).getNormal();
}

//Squares each position in the vector
float Vector2::getSquare() const
{
    return (x * x) + (y * y);
}

//How much of the vector lies on the other vector when projected
float Vector2::projectOntoAxis(const Vector2& axis) const
{
    return (x * axis.x) + (y * axis.y);
}