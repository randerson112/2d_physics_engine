//Class defenition for world boundary to keep physics bodies within constraints

#ifndef WORLD_BOUNDARY_HPP
#define WORLD_BOUNDARY_HPP

#include "physics/StaticBody.hpp"
#include "physics/DynamicBody.hpp"

namespace phys
{
enum class BoundaryType
{
    Collidable,
    Delete
};

class WorldBoundary
{
private:
    //Minimum boundaries for world
    const float MIN_WORLD_WIDTH = 5.0f;
    const float MIN_WORLD_HEIGHT = 5.0f;

    //Maximum boundaries for world
    const float MAX_WORLD_WIDTH = 10000.0f;
    const float MAX_WORLD_HEIGHT = 10000.0f;

    //Dimensions of the world boundaries
    Vector2 m_dimensions;

    //Type of boundary
    //Objects collide with it, or get deleted when beyond boundary
    BoundaryType m_type;

public:
    //Constructor to set world width and height and the type of boundary
    WorldBoundary(const Vector2& dimensions, BoundaryType type);

    //Keeps a body within boundaries when placed or moved
    bool placementEnforce(PhysicsBody* body) const;

    //Keeps a dynamic body within boundaries every frame
    bool dynamicEnforce(DynamicBody* body) const;

    //Getters for member variables
    float getWidth() const;
    float getHeight() const;

    //Set new world boundary dimensions
    void setDimensions(Vector2& newDimensions);

    //Set a new boundary type
    void setType(BoundaryType newType);
};
}

#endif