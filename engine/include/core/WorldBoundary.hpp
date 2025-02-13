//Class defenition for world boundary to keep physics bodies within constraints

#include "physics/StaticBody.hpp"
#include "physics/DynamicBody.hpp"

class WorldBoundary
{
private:
    //Minimum boundaries for world, cannot be smaller
    const float MIN_WORLD_WIDTH = 5.0f;
    const float MIN_WORLD_HEIGHT = 5.0f;

    //Dimensions of the world boundaries
    float worldWidth;
    float worldHeight;

public:
    //Constructor to set world width and height
    WorldBoundary(float width, float height);

    //Keeps a body within boundaries when placed or moved
    void placementEnforce(PhysicsBody* body) const;

    //Keeps a dynamic body within boundaries every frame
    void dynamicEnforce(DynamicBody* body) const;

    //Getters for member variables
    float getWidth() const;
    float getHeight() const;

    //Set new world boundary dimensions
    void setDimensions(float newWidth, float newHeight);
};