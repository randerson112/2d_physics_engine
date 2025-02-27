//Implementation of WorldBoundary class

#include "core/WorldBoundary.hpp"
#include "collisions/RectCollider.hpp"
#include "collisions/CircleCollider.hpp"

//Constructor to set dimensions and boundary type
WorldBoundary::WorldBoundary(float width, float height, BoundaryType type)
    : worldWidth(width), worldHeight(height), type(type)
    {
        //Check if dimensions are not less than minimums
        if (worldWidth < MIN_WORLD_WIDTH)
            worldWidth = MIN_WORLD_WIDTH;

        if (worldHeight < MIN_WORLD_HEIGHT)
            worldHeight = MIN_WORLD_HEIGHT;
    }

//Enforce boundaries on a body when it is first placed or moved
//Returns true if body has gone beyond the boundary so the engine knows to delete it
bool WorldBoundary::placementEnforce(PhysicsBody* body) const
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

        //if we want the body to stay inside the boundary
        if (type == BoundaryType::Collidable)
        {
            //Left boundary
            if (bodyPos.x - halfBodyWidth < -halfWorldWidth) newBodyPos.x = -halfWorldWidth + halfBodyWidth;

            //Right boundary
            if (bodyPos.x + halfBodyWidth > halfWorldWidth) newBodyPos.x = halfWorldWidth - halfBodyWidth;

            //Bottom boundary
            if (bodyPos.y - halfBodyHeight < -halfWorldHeight) newBodyPos.y = -halfWorldHeight + halfBodyHeight;

            //Top boundary
            if (bodyPos.y + halfBodyHeight > halfWorldHeight) newBodyPos.y = halfWorldHeight - halfBodyHeight;
        }

        //If we want to delete the body if it is beyond the boundary
        if (type == BoundaryType::Delete)
        {
            //Left boundary
            if (bodyPos.x + halfBodyWidth < -halfWorldWidth) return true;

            //Right boundary
            if (bodyPos.x - halfBodyWidth > halfWorldWidth) return true;

            //Bottom boundary
            if (bodyPos.y + halfBodyHeight < -halfWorldHeight) return true;

            //Top boundary
            if (bodyPos.y - halfBodyHeight > halfWorldHeight) return true;

            //Body is still within boundaries, do not delete
            return false;
        }
    }

    //If body is a circle
    if (bodyShape == ColliderShape::Circle)
    {
        CircleCollider* bodyCollider = static_cast<CircleCollider*>(body->getCollider());

        //Get the radius
        float bodyRadius = bodyCollider->getRadius();

        //if we want the body to stay inside the boundary
        if (type == BoundaryType::Collidable)
        {
            //Left boundary
            if (bodyPos.x - bodyRadius < -halfWorldWidth) newBodyPos.x = -halfWorldWidth + bodyRadius;

            //Right boundary
            if (bodyPos.x + bodyRadius > halfWorldWidth) newBodyPos.x = halfWorldWidth - bodyRadius;

            //Bottom boundary
            if (bodyPos.y - bodyRadius < -halfWorldHeight) newBodyPos.y = -halfWorldHeight + bodyRadius;

            //Top boundary
            if (bodyPos.y + bodyRadius > halfWorldHeight) newBodyPos.y = halfWorldHeight - bodyRadius;
        }

        //If we want to delete the body if it is beyond the boundary
        if (type == BoundaryType::Delete)
        {
            //Left boundary
            if (bodyPos.x + bodyRadius < -halfWorldWidth) return true;

            //Right boundary
            if (bodyPos.x - bodyRadius > halfWorldWidth) return true;

            //Bottom boundary
            if (bodyPos.y + bodyRadius < -halfWorldHeight) return true;

            //Top boundary
            if (bodyPos.y - bodyRadius > halfWorldHeight) return true;

            //Body is still within boundaries, do not delete
            return false;
        }
    }

    //Update the body position to stay within bounds
    body->setPosition(newBodyPos);

    //Return false because body type is not delete and calculations already made
    return false;
}

//Enforce boundaries on a dynamic body every frame
bool WorldBoundary::dynamicEnforce(DynamicBody* body) const
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

        //If we want the dynamic body to collide with the boundary
        if (type == BoundaryType::Collidable)
        {
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

        //If we want the dynamic body to be deleted if it goes beyond the boundary
        if (type == BoundaryType::Delete)
        {
            //Left boundary
            if (bodyPos.x + halfBodyWidth < -halfWorldWidth) return true;

            //Right boundary
            if (bodyPos.x - halfBodyWidth > halfWorldWidth) return true;

            //Bottom boundary
            if (bodyPos.y + halfBodyHeight < -halfWorldHeight) return true;

            //Top boundary
            if (bodyPos.y - halfBodyHeight > halfWorldHeight) return true;

            //Body is still within boundaries, do not delete
            return false;
        }
    }

    //If body is a circle
    if (bodyShape == ColliderShape::Circle)
    {
        CircleCollider* bodyCollider = static_cast<CircleCollider*>(body->getCollider());

        //Get circle radius
        float bodyRadius = bodyCollider->getRadius();

        //If we want the dynamic body to collide with the boundary
        if (type == BoundaryType::Collidable)
        {
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

        //If we want the dynamic body to be deleted if it goes beyond the boundary
        if (type == BoundaryType::Delete)
        {
            //Left boundary
            if (bodyPos.x + bodyRadius < -halfWorldWidth) return true;

            //Right boundary
            if (bodyPos.x - bodyRadius > halfWorldWidth) return true;

            //Bottom boundary
            if (bodyPos.y + bodyRadius < -halfWorldHeight) return true;

            //Top boundary
            if (bodyPos.y - bodyRadius > halfWorldHeight) return true;

            //Body is still within boundaries, do not delete
            return false;
        }
    }

    //Update the body position to stay within bounds
    body->setPosition(newBodyPos);

    //Update the body velocity when boundaries are hit
    body->setVelocity(newVelocity);

    //Return false because body type is not delete and calculations already made
    return false;
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

//Set a new boundary type
void WorldBoundary::setType(BoundaryType newType)
{
    type = newType;
}