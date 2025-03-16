//Class defenition for rectangle shape colliders
//Width and height attributes

#ifndef RECT_COLLIDER_HPP
#define RECT_COLLIDER_HPP

#include "collisions/Collider.hpp"

class RectCollider : public Collider
{
private:
    //Width and height of rectangle collision area
    float width;
    float height;

public:
    //Constructor to set dimensions and collider type
    RectCollider(Vector2 dimensions, ColliderType type);

    //Getters for member variables
    float getWidth() const;
    float getHeight() const;

    //Setters for member variables
    void setWidth(float newWidth);
    void setHeight(float newHeight);
};

#endif