//Implementation of WorldBoundary class

#include "WorldBoundary.hpp"
#include "RectCollider.hpp"
#include "CircleCollider.hpp"

WorldBoundary::WorldBoundary(float width, float height)
    : worldWidth(width), worldHeight(height)
    {
        if (worldWidth < MIN_WORLD_WIDTH)
            worldWidth = MIN_WORLD_WIDTH;

        if (worldHeight < MIN_WORLD_HEIGHT)
            worldHeight = MIN_WORLD_HEIGHT;
    }

//Keeps a body within world bounds when it is first placed or moved
void WorldBoundary::placementEnforce(PhysicsBody* body) const
{
    //Get world half dimensions
    float halfWorldWidth = worldWidth / 2;
    float halfWorldHeight = worldHeight / 2;

    //Get collider shape
    ColliderShape bodyShape = body->getCollider()->getShape();

    //Get body center position
    Vector2 bodyPos = body->getPosition();

    //For storing new position after calculations
    Vector2 newBodyPos = bodyPos;

    //If body is a rectangle
    if (bodyShape == ColliderShape::Rectangle)
    {
        RectCollider* bodyCollider = static_cast<RectCollider*>(body->getCollider());

        //Get rectangle half width and height
        float halfBodyWidth = bodyCollider->getWidth() / 2;
        float halfBodyHeight = bodyCollider->getHeight() / 2;

        //Left boundary
        if (bodyPos.x - halfBodyWidth < -halfWorldWidth) newBodyPos.x = -halfWorldWidth + halfBodyWidth;

        //Right boundary
        if (bodyPos.x + halfBodyWidth > halfWorldWidth) newBodyPos.x = halfWorldWidth - halfBodyWidth;

        //Bottom boundary
        if (bodyPos.y - halfBodyHeight < -halfWorldHeight) newBodyPos.y = -halfWorldHeight + halfBodyHeight;

        //Top boundary
        if (bodyPos.y + halfBodyHeight > halfWorldHeight) newBodyPos.y = halfWorldHeight - halfBodyHeight;
    }

    //If body is a circle
    if (bodyShape == ColliderShape::Circle)
    {
        CircleCollider* bodyCollider = static_cast<CircleCollider*>(body->getCollider());

        //Get the radius
        float bodyRadius = bodyCollider->getRadius();

        //Left boundary
        if (bodyPos.x - bodyRadius < -halfWorldWidth) newBodyPos.x = -halfWorldWidth + bodyRadius;

        //Right boundary
        if (bodyPos.x + bodyRadius > halfWorldWidth) newBodyPos.x = halfWorldWidth - bodyRadius;

        //Bottom boundary
        if (bodyPos.y - bodyRadius < -halfWorldHeight) newBodyPos.y = -halfWorldHeight + bodyRadius;

        //Top boundary
        if (bodyPos.y + bodyRadius > halfWorldHeight) newBodyPos.y = halfWorldHeight - bodyRadius;
    }

    //Update the body position to stay within bounds
    body->setPosition(newBodyPos);
}

//Keeps a dynamic body within world boundaries every frame
void WorldBoundary::dynamicEnforce(DynamicBody* body) const
{
    //Get world half dimensions
    float halfWorldWidth = worldWidth / 2;
    float halfWorldHeight = worldHeight / 2;

    //Get collider shape
    ColliderShape bodyShape = body->getCollider()->getShape();

    //Get body center position
    Vector2 bodyPos = body->getPosition();

    //Get the body restitution
    float bodyRestitution = body->getRestitution();

    //For storing new position after calculations
    Vector2 newBodyPos = bodyPos;

    //For storing new velocity after calculations
    Vector2 newVelocity = body->getVelocity();

    //If body is a rectangle
    if (bodyShape == ColliderShape::Rectangle)
    {
        RectCollider* bodyCollider = static_cast<RectCollider*>(body->getCollider());

        //Get rectangle half width and height
        float halfBodyWidth = bodyCollider->getWidth() / 2;
        float halfBodyHeight = bodyCollider->getHeight() / 2;

        //Left boundary
        if (bodyPos.x - halfBodyWidth < -halfWorldWidth)
        {
            newBodyPos.x = -halfWorldWidth + halfBodyWidth;
            newVelocity.x = -newVelocity.x * bodyRestitution;
        }

        //Right boundary
        if (bodyPos.x + halfBodyWidth > halfWorldWidth)
        {
            newBodyPos.x = halfWorldWidth - halfBodyWidth;
            newVelocity.x = -newVelocity.x * bodyRestitution;
        }

        //Bottom boundary
        if (bodyPos.y - halfBodyHeight < -halfWorldHeight)
        {
            newBodyPos.y = -halfWorldHeight + halfBodyHeight;
            newVelocity.y = -newVelocity.y * bodyRestitution;
        }

        //Top boundary
        if (bodyPos.y + halfBodyHeight > halfWorldHeight)
        {
            newBodyPos.y = halfWorldHeight - halfBodyHeight;
            newVelocity.y = -newVelocity.y * bodyRestitution;
        }
    }

    //If body is a circle
    if (bodyShape == ColliderShape::Circle)
    {
        CircleCollider* bodyCollider = static_cast<CircleCollider*>(body->getCollider());

        //Get circle radius
        float bodyRadius = bodyCollider->getRadius();

        //Left boundary
        if (bodyPos.x - bodyRadius < -halfWorldWidth)
        {
            newBodyPos.x = -halfWorldWidth + bodyRadius;
            newVelocity.x = -newVelocity.x * bodyRestitution;
        }

        //Right boundary
        if (bodyPos.x + bodyRadius > halfWorldWidth)
        {
            newBodyPos.x = halfWorldWidth - bodyRadius;
            newVelocity.x = -newVelocity.x * bodyRestitution;
        }

        //Bottom boundary
        if (bodyPos.y - bodyRadius < -halfWorldHeight)
        {
            newBodyPos.y = -halfWorldHeight + bodyRadius;
            newVelocity.y = -newVelocity.y * bodyRestitution;
        }

        //Top boundary
        if (bodyPos.y + bodyRadius > halfWorldHeight)
        {
            newBodyPos.y = halfWorldHeight - bodyRadius;
            newVelocity.y = -newVelocity.y * bodyRestitution;
        }
    }

    //Update the body position to stay within bounds
    body->setPosition(newBodyPos);

    //Update the body velocity when boundaries are hit
    body->setVelocity(newVelocity);
}

//Getters for member variables
float WorldBoundary::getWidth() const
{
    return worldWidth;
}

float WorldBoundary::getHeight() const
{
    return worldHeight;
}

//Sets new dimensions for world boundaries, cannot be less than minimums
void WorldBoundary::setDimensions(float newWidth, float newHeight)
{
    if (newWidth >= MIN_WORLD_WIDTH)
        worldWidth = newWidth;

    if (newHeight >= MIN_WORLD_HEIGHT)
        worldHeight = newHeight;
}