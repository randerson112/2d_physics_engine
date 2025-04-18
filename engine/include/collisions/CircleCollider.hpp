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

    //Update AABB mins and maxes
    virtual void updateAABB() override;

public:
    //Constructor to set radius and collider type
    CircleCollider(float initialRadius, ColliderType type);

    //Getters for member variables
    float getRadius() const;

    //Setters for member variables
    void setRadius(float newRadius);
};

#endif