//Class defenition for world boundary to keep physics bodies within constraints

#include "physics/StaticBody.hpp"
#include "physics/DynamicBody.hpp"

enum class BoundaryType
{
    Collidable,
    Delete
};

class WorldBoundary
{
private:
    //Minimum boundaries for world, cannot be smaller
    const float MIN_WORLD_WIDTH = 5.0f;
    const float MIN_WORLD_HEIGHT = 5.0f;

    //Dimensions of the world boundaries
    float worldWidth;
    float worldHeight;

    //Type of boundary
    //Objects collide with it, or get deleted when beyond boundary
    BoundaryType type;

public:
    //Constructor to set world width and height and the type of boundary
    WorldBoundary(float width, float height, BoundaryType type);

    //Keeps a body within boundaries when placed or moved
    bool placementEnforce(PhysicsBody* body) const;

    //Keeps a dynamic body within boundaries every frame
    bool dynamicEnforce(DynamicBody* body) const;

    //Getters for member variables
    float getWidth() const;
    float getHeight() const;

    //Set new world boundary dimensions
    void setDimensions(float newWidth, float newHeight);

    //Set a new boundary type
    void setType(BoundaryType newType);
};