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
    Vector2 operator+(Vector2 other);
    Vector2 operator-(Vector2 other);
    Vector2 operator*(float scalar);
    Vector2 operator/(float divisor);

    //Basic assignment operator overloads
    void operator+=(Vector2 other);
    void operator-=(Vector2 other);
    void operator*=(float scalar);
    void operator/=(float divisor);

    //Negative operator overload for getting the inverse
    Vector2 operator-();

    //Gets the normal of the vector, length of 1
    Vector2 getNormal();

    //Returns the magnitude or length of a vector
    float getLength();

    //Gets the vector pointing to another vector
    Vector2 getVectorTo(Vector2 other);

    //Gets the direction with length of 1 to another vector
    Vector2 getDirectionTo(Vector2 other);

    //Return the square of the vector
    float getSquare();

    //How much of the vector lies on the other vector when projected
    float projectOntoAxis(Vector2 axis);
};

#endif