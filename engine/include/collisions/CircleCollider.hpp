//Class defenition for circle shape colliders
//Radius attribute

#ifndef CIRCLE_COLLIDER_HPP
#define CIRCLE_COLLIDER_HPP

#include "collisions/Collider.hpp"

class CircleCollider : public Collider
{
private:
    //Radius of the circle
    float radius;

public:
    //Constructor to set radius
    CircleCollider(float initialRadius);

    //Getters for member variables
    float getRadius();

    //Setters for member variables
    void setRadius(float newRadius);
};

#endif