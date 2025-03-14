//Class defentions for 2D vectors
//Stores an x and y value
//Methods for normalizing, finding distance

#ifndef Vector2_HPP
#define Vector2_HPP

#include <cmath>

class Vector2
{
public:
    //coordinates of the vector
    float x;
    float y;

    //Default constructor
    Vector2();

    //Constructor with x and y parameters
    Vector2(float x, float y);

    //Basic operator overloads
    Vector2 operator+(const Vector2& other) const;
    Vector2 operator-(const Vector2& other) const;
    Vector2 operator*(float scalar) const;
    Vector2 operator/(float divisor) const;

    //Basic assignment operator overloads
    void operator+=(const Vector2& other);
    void operator-=(const Vector2& other);
    void operator*=(float scalar);
    void operator/=(float divisor);

    //Negative operator overload for getting the inverse
    Vector2 operator-() const;

    //Gets the normal of the vector, length of 1
    Vector2 getNormal() const;

    //Returns the magnitude or length of a vector
    float getLength() const;

    //Gets the vector pointing to another vector
    Vector2 getVectorTo(const Vector2& other) const;

    //Gets the direction with length of 1 to another vector
    Vector2 getDirectionTo(const Vector2& other) const;

    //Return the square of the vector
    float getSquare() const;

    //How much of the vector lies on the other vector when projected
    float projectOntoAxis(const Vector2& axis) const;
};

#endif