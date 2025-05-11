//Class defenition for rectangle shape colliders
//Width and height attributes

#ifndef RECT_COLLIDER_HPP
#define RECT_COLLIDER_HPP

#include "collisions/Collider.hpp"
#include <vector>

namespace phys
{
class RectCollider : public Collider
{
private:
    //Dimensions of rectangle collision area
    Vector2 m_dimensions;

    //Update AABB mins and maxes
    virtual void updateAABB() override;

public:
    //Constructor to set dimensions and collider type
    RectCollider(const Vector2& dimensions, ColliderType type);

    //Returns the verticies of the collider in its current state
    const std::vector<Vector2> calculateVertcies();

    //Getters for member variables
    float getWidth() const;
    float getHeight() const;

    //Setters for member variables
    void setDimensions(const Vector2& newDimensions);
};
}

#endif