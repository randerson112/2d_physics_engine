//Implementation of WorldBoundary class

#include "core/WorldBoundary.hpp"
#include "collisions/RectCollider.hpp"
#include "collisions/CircleCollider.hpp"

namespace phys
{
    //Constructor to set dimensions and boundary type
    WorldBoundary::WorldBoundary(const Vector2& dimensions, BoundaryType boundaryType) :
        m_dimensions(dimensions), m_type(boundaryType)
    {
        //Check if dimensions are not less than minimums
        if (m_dimensions.x < MIN_WORLD_WIDTH)
            m_dimensions.x = MIN_WORLD_WIDTH;

        if (m_dimensions.y < MIN_WORLD_HEIGHT)
            m_dimensions.y = MIN_WORLD_HEIGHT;

        //Check if dimensions are not greater than maximums
        if (m_dimensions.x > MAX_WORLD_WIDTH)
            m_dimensions.x = MAX_WORLD_WIDTH;

        if (m_dimensions.y > MAX_WORLD_HEIGHT)
            m_dimensions.y = MAX_WORLD_HEIGHT;
    }

    //Enforce boundaries on a body when it is first placed or moved
    //Returns true if body has gone beyond the boundary so the engine knows to delete it
    bool WorldBoundary::placementEnforce(PhysicsBody* body) const
    {
        //Get world half dimensions
        float halfWorldWidth = m_dimensions.x / 2;
        float halfWorldHeight = m_dimensions.y / 2;

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
            if (m_type == BoundaryType::Collidable)
            {
                //Left boundary
                if (bodyPos.x - halfBodyWidth < -halfWorldWidth)
                    newBodyPos.x = -halfWorldWidth + halfBodyWidth;

                //Right boundary
                if (bodyPos.x + halfBodyWidth > halfWorldWidth)
                    newBodyPos.x = halfWorldWidth - halfBodyWidth;

                //Bottom boundary
                if (bodyPos.y - halfBodyHeight < -halfWorldHeight)
                    newBodyPos.y = -halfWorldHeight + halfBodyHeight;

                //Top boundary
                if (bodyPos.y + halfBodyHeight > halfWorldHeight)
                    newBodyPos.y = halfWorldHeight - halfBodyHeight;
            }

            //If we want to delete the body if it is beyond the boundary
            if (m_type == BoundaryType::Delete)
            {
                //Left boundary
                if (bodyPos.x + halfBodyWidth < -halfWorldWidth)
                    return true;

                //Right boundary
                if (bodyPos.x - halfBodyWidth > halfWorldWidth)
                    return true;

                //Bottom boundary
                if (bodyPos.y + halfBodyHeight < -halfWorldHeight)
                    return true;

                //Top boundary
                if (bodyPos.y - halfBodyHeight > halfWorldHeight)
                    return true;

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
            if (m_type == BoundaryType::Collidable)
            {
                //Left boundary
                if (bodyPos.x - bodyRadius < -halfWorldWidth)
                    newBodyPos.x = -halfWorldWidth + bodyRadius;

                //Right boundary
                if (bodyPos.x + bodyRadius > halfWorldWidth)
                    newBodyPos.x = halfWorldWidth - bodyRadius;

                //Bottom boundary
                if (bodyPos.y - bodyRadius < -halfWorldHeight)
                    newBodyPos.y = -halfWorldHeight + bodyRadius;

                //Top boundary
                if (bodyPos.y + bodyRadius > halfWorldHeight)
                    newBodyPos.y = halfWorldHeight - bodyRadius;
            }

            //If we want to delete the body if it is beyond the boundary
            if (m_type == BoundaryType::Delete)
            {
                //Left boundary
                if (bodyPos.x + bodyRadius < -halfWorldWidth)
                    return true;

                //Right boundary
                if (bodyPos.x - bodyRadius > halfWorldWidth)
                    return true;

                //Bottom boundary
                if (bodyPos.y + bodyRadius < -halfWorldHeight)
                    return true;

                //Top boundary
                if (bodyPos.y - bodyRadius > halfWorldHeight)
                    return true;

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
        float halfWorldWidth = m_dimensions.x / 2;
        float halfWorldHeight = m_dimensions.y / 2;

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
            if (m_type == BoundaryType::Collidable)
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
            if (m_type == BoundaryType::Delete)
            {
                //Left boundary
                if (bodyPos.x + halfBodyWidth < -halfWorldWidth)
                    return true;

                //Right boundary
                if (bodyPos.x - halfBodyWidth > halfWorldWidth)
                    return true;

                //Bottom boundary
                if (bodyPos.y + halfBodyHeight < -halfWorldHeight)
                    return true;

                //Top boundary
                if (bodyPos.y - halfBodyHeight > halfWorldHeight)
                    return true;

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
            if (m_type == BoundaryType::Collidable)
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
            if (m_type == BoundaryType::Delete)
            {
                //Left boundary
                if (bodyPos.x + bodyRadius < -halfWorldWidth)
                    return true;

                //Right boundary
                if (bodyPos.x - bodyRadius > halfWorldWidth)
                    return true;

                //Bottom boundary
                if (bodyPos.y + bodyRadius < -halfWorldHeight)
                    return true;

                //Top boundary
                if (bodyPos.y - bodyRadius > halfWorldHeight)
                    return true;

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
        return m_dimensions.x;
    }

    float WorldBoundary::getHeight() const
    {
        return m_dimensions.y;
    }

    //Sets new dimensions for world boundaries, cannot be less than minimums
    void WorldBoundary::setDimensions(Vector2& newDimensions)
    {
        //Check if dimensions are not less than minimums
        if (newDimensions.x < MIN_WORLD_WIDTH)
            newDimensions.x = MIN_WORLD_WIDTH;

        if (newDimensions.y < MIN_WORLD_HEIGHT)
            newDimensions.y = MIN_WORLD_HEIGHT;

        //Check if dimensions are not greater than maximums
        if (newDimensions.x > MAX_WORLD_WIDTH)
            newDimensions.x = MAX_WORLD_WIDTH;

        if (newDimensions.y > MAX_WORLD_HEIGHT)
            newDimensions.y = MAX_WORLD_HEIGHT;

        //Set new dimensions
        m_dimensions = newDimensions;
    }

    //Set a new boundary type
    void WorldBoundary::setType(BoundaryType newType)
    {
        m_type = newType;
    }
}