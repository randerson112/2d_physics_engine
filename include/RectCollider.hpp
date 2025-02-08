//Class defenition for rectangle shape colliders
//Width and height attributes

#ifndef RECT_COLLIDER_HPP
#define RECT_COLLIDER_HPP

#include "Collider.hpp"

class RectCollider : public Collider
{
private:
    //Width and height of rectangle collision area
    float width;
    float height;

public:
    //Constructor to set dimensions
    RectCollider(float width, float height);

    //Getters for member variables
    float getWidth();
    float getHeight();

    //Setters for member variables
    void setWidth(float newWidth);
    void setHeight(float newHeight);
};

#endif