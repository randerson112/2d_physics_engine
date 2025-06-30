//Implementaion of collision detection functions

#include "collisions/CollisionDetection.hpp"
#include "core/Vector2.hpp"
#include <algorithm>

struct Collision;

namespace phys
{
    //Checks if two AABBs are overlapping
    bool CollisionDetection::checkAABBvsAABB(const AABB& boxA, const AABB& boxB)
    {
        //Get mins and maxes
        Vector2 minA = boxA.min;
        Vector2 maxA = boxA.max;

        Vector2 minB = boxB.min;
        Vector2 maxB = boxB.max;

        //Check for overlap
        if (maxA.x > minB.x && minA.x < maxB.x && maxA.y > minB.y && minA.y < maxB.y)
            return true;

        //No overlap
        return false;
    }

    //Checks if two polygons are intersecting using seperating axis theorem
    Collision* CollisionDetection::checkPolygonCollision(RectCollider* polygonA, RectCollider* polygonB)
    {
        //Define variables for collision data
        float penDepth = std::numeric_limits<float>::infinity();
        Vector2 normal;
        std::vector<Vector2> contactPoints;
        int contactCount = 0;

        //Get vertices of each polygon
        std::vector<Vector2> verticesA = polygonA->calculateVertcies();
        std::vector<Vector2> verticesB = polygonB->calculateVertcies();

        //Check against normals of polygon A
        for (int i = 0; i < verticesA.size(); i++)
        {
            Vector2 vertexA = verticesA[i];
            Vector2 vertexB = verticesA[(i + 1) % verticesA.size()];

            Vector2 edge = vertexB - vertexA;
            Vector2 axis = {-edge.y, edge.x};
            axis = axis.getNormal();

            Projection projectionA = projectPolygonOntoAxis(verticesA, axis);
            Projection projectionB = projectPolygonOntoAxis(verticesB, axis);

            if (projectionA.min > projectionB.max || projectionB.min > projectionA.max)
                return nullptr;

            float axisPenDepth = std::min(projectionB.max - projectionA.min, projectionA.max - projectionB.min);

            if (axisPenDepth < penDepth)
            {
                penDepth = axisPenDepth;
                normal = axis;
            }
        }

        //Check against normals of polygon B
        for (int i = 0; i < verticesB.size(); i++)
        {
            Vector2 vertexA = verticesB[i];
            Vector2 vertexB = verticesB[(i + 1) % verticesB.size()];

            Vector2 edge = vertexB - vertexA;
            Vector2 axis = {-edge.y, edge.x};
            axis = axis.getNormal();

            Projection projectionA = projectPolygonOntoAxis(verticesA, axis);
            Projection projectionB = projectPolygonOntoAxis(verticesB, axis);

            if (projectionA.min > projectionB.max || projectionB.min > projectionA.max)
                return nullptr;

            float axisPenDepth = std::min(projectionB.max - projectionA.min, projectionA.max - projectionB.min);

            if (axisPenDepth < penDepth)
            {
                penDepth = axisPenDepth;
                normal = axis;
            }
        }

        //Ensure normal points from polygonA to polygonB
        Vector2 direction = polygonB->getParent()->getPosition() - polygonA->getParent()->getPosition();
        if (normal.projectOntoAxis(direction) < 0)
            normal = -normal;

        //Find contact points
        contactPoints = findPolygonContactPoints(verticesA, verticesB);
        contactCount = contactPoints.size();

        //Return collision object with data if collision was found
        return new Collision(
            polygonA->getParent(), polygonB->getParent(), normal, penDepth, contactPoints, contactCount);
    }

    //Checks if circle and polygon are intersecting using SAT
    Collision* CollisionDetection::checkCirclePolygonCollision(CircleCollider* circle, RectCollider* polygon)
    {
        //Get circle properties and polygon vertices
        Vector2 center = circle->getPosition();
        float radius = circle->getRadius();
        std::vector<Vector2> vertices = polygon->calculateVertcies();

        //Define variables for collision data
        float penDepth = std::numeric_limits<float>::infinity();
        Vector2 normal;
        std::vector<Vector2> contactPoints;
        int contactCount = 0;

        //Check against normals of polygon
        for (int i = 0; i < vertices.size(); i++)
        {
            Vector2 vertexA = vertices[i];
            Vector2 vertexB = vertices[(i + 1) % vertices.size()];

            Vector2 edge = vertexB - vertexA;
            Vector2 axis = {-edge.y, edge.x};
            axis = axis.getNormal();

            Projection circleProjection = projectCircleOntoAxis(center, radius, axis);
            Projection polygonProjection = projectPolygonOntoAxis(vertices, axis);

            if (circleProjection.min > polygonProjection.max || polygonProjection.min > circleProjection.max)
                return nullptr;

            float axisPenDepth =
                std::min(polygonProjection.max - circleProjection.min, circleProjection.max - polygonProjection.min);

            if (axisPenDepth < penDepth)
            {
                penDepth = axisPenDepth;
                normal = axis;
            }
        }

        //Check against axis between circle center and closest point
        int closestIndex = findClosestPointToCenter(center, vertices);
        Vector2 closestPoint = vertices[closestIndex];

        Vector2 axis = closestPoint - center;
        axis = axis.getNormal();

        Projection circleProjection = projectCircleOntoAxis(center, radius, axis);
        Projection polygonProjection = projectPolygonOntoAxis(vertices, axis);

        if (circleProjection.min > polygonProjection.max || polygonProjection.min > circleProjection.max)
            return nullptr;

        float axisPenDepth =
            std::min(polygonProjection.max - circleProjection.min, circleProjection.max - polygonProjection.min);

        if (axisPenDepth < penDepth)
        {
            penDepth = axisPenDepth;
            normal = axis;
        }

        //Ensure normal points from circle to polygon
        Vector2 direction = polygon->getParent()->getPosition() - circle->getParent()->getPosition();
        if (normal.projectOntoAxis(direction) < 0)
            normal = -normal;

        //Find contact points
        contactPoints = findCirclePolygonContactPoints(center, radius, vertices);
        contactCount = contactPoints.size();

        //Return a collision object with data if collision was found
        return new Collision(circle->getParent(), polygon->getParent(), normal, penDepth, contactPoints, contactCount);
    }

    //Returns the min and max of verticies projected onto an axis in a Vector2 struct
    const Projection CollisionDetection::projectPolygonOntoAxis(
        const std::vector<Vector2>& vertices, const Vector2& axis)
    {
        float min = std::numeric_limits<float>::infinity();
        float max = -std::numeric_limits<float>::infinity();

        for (int i = 0; i < vertices.size(); i++)
        {
            Vector2 vertex = vertices[i];
            float projection = vertex.projectOntoAxis(axis);

            if (projection < min)
                min = projection;

            if (projection > max)
                max = projection;
        }

        return {min, max};
    }

    //Returns the min and max of a circle projected onto an axis
    const Projection CollisionDetection::projectCircleOntoAxis(const Vector2& center, float radius, const Vector2& axis)
    {
        Vector2 axisDirection = axis.getNormal();
        Vector2 directionWithRadius = axisDirection * radius;

        Vector2 point1 = center + directionWithRadius;
        Vector2 point2 = center - directionWithRadius;

        float projection1 = point1.projectOntoAxis(axis);
        float projection2 = point2.projectOntoAxis(axis);

        float min;
        float max;

        if (projection1 > projection2)
        {
            min = projection2;
            max = projection1;
        }
        else
        {
            min = projection1;
            max = projection2;
        }

        return {min, max};
    }

    //Find closest point on polygon to circle center, returns the index
    int CollisionDetection::findClosestPointToCenter(const Vector2& center, const std::vector<Vector2>& vertices)
    {
        int index = 0;
        float minDistanceSquared = center.getVectorTo(vertices[0]).getSquare();

        for (int i = 1; i < vertices.size(); i++)
        {
            float distanceSquared = center.getVectorTo(vertices[i]).getSquare();
            if (distanceSquared < minDistanceSquared)
            {
                minDistanceSquared = distanceSquared;
                index = i;
            }
        }

        return index;
    }

    //Sorts into respective function based on body shapes
    Collision* CollisionDetection::checkCollision(PhysicsBody* bodyA, PhysicsBody* bodyB)
    {
        //Get colliders
        Collider* colliderA = bodyA->getCollider();
        Collider* colliderB = bodyB->getCollider();

        //If on different collision layers, return early
        if (colliderA->getCollisionLayer() != colliderB->getCollisionLayer())
            return nullptr;

        //Get collider shapes
        ColliderShape shapeA = colliderA->getShape();
        ColliderShape shapeB = colliderB->getShape();

        //First collider is a rectangle
        if (shapeA == ColliderShape::Rectangle)
        {
            RectCollider* rectA = static_cast<RectCollider*>(colliderA);

            //Second collider is also a rectangle
            if (shapeB == ColliderShape::Rectangle)
            {
                RectCollider* rectB = static_cast<RectCollider*>(colliderB);

                //Check for polygon collision
                return checkPolygonCollision(rectA, rectB);
            }

            //Second collider is a circle
            else if (shapeB == ColliderShape::Circle)
            {
                CircleCollider* circleB = static_cast<CircleCollider*>(colliderB);

                //Check for circle-polygon collision
                return checkCirclePolygonCollision(circleB, rectA);
            }
        }

        //First collider is a circle
        else if (shapeA == ColliderShape::Circle)
        {
            CircleCollider* circleA = static_cast<CircleCollider*>(colliderA);

            //Second collider is also a circle
            if (shapeB == ColliderShape::Circle)
            {
                CircleCollider* circleB = static_cast<CircleCollider*>(colliderB);

                //Check for circle-circle collision
                return checkCircleCollision(circleA, circleB);
            }

            //Second collider is a rectangle
            else if (shapeB == ColliderShape::Rectangle)
            {
                RectCollider* rectB = static_cast<RectCollider*>(colliderB);

                //Check for rect-circle collision
                return checkCirclePolygonCollision(circleA, rectB);
            }
        }

        return nullptr;
    }

    //Calculate collision between two circle colliders
    Collision* CollisionDetection::checkCircleCollision(CircleCollider* circleA, CircleCollider* circleB)
    {
        //Get positions of centers
        Vector2 circleAPos = circleA->getPosition();
        Vector2 circleBPos = circleB->getPosition();

        //Get radii
        float circleARadius = circleA->getRadius();
        float circleBRadius = circleB->getRadius();

        float sumRadii = circleARadius + circleBRadius;

        //Calculate distance squared between circles
        Vector2 vectorBetweenCenters = circleAPos.getVectorTo(circleBPos);
        float distanceSquared = vectorBetweenCenters.getSquare();

        //Check if distance squared is less than sum of radii squared
        if (distanceSquared <= (sumRadii * sumRadii))
        {
            //Get the normal and penetration depth of the collision
            Vector2 normal = circleAPos.getDirectionTo(circleBPos);
            float penDepth = sumRadii - (circleAPos.getVectorTo(circleBPos)).getLength();

            //Find contact points
            std::vector<Vector2> contactPoints = findCircleContactPoints(circleAPos, circleARadius, circleBPos, normal);
            int contactCount = contactPoints.size();

            //Return a collision object
            return new Collision(
                circleA->getParent(), circleB->getParent(), normal, penDepth, contactPoints, contactCount);
        }

        //If no collision is detected
        return nullptr;
    }

    //Find contact point between two circles
    std::vector<Vector2> CollisionDetection::findCircleContactPoints(
        const Vector2& centerA, float radiusA, const Vector2& centerB, const Vector2& normal)
    {
        std::vector<Vector2> contactPoints;

        Vector2 contact = centerA + normal * radiusA;
        contactPoints.push_back(contact);

        return contactPoints;
    }

    //Find contact point between a circle and polygon
    std::vector<Vector2> CollisionDetection::findCirclePolygonContactPoints(
        const Vector2& circleCenter, float circleRadius, const std::vector<Vector2>& polygonVertices)
    {
        std::vector<Vector2> contactPoints;
        Vector2 contact;

        float minDistanceSquared = std::numeric_limits<float>::infinity();

        //Loop through edges of polygon and find closest point to circle center
        for (int i = 0; i < polygonVertices.size(); i++)
        {
            Vector2 vertexA = polygonVertices[i];
            Vector2 vertexB = polygonVertices[(i + 1) % polygonVertices.size()];

            Vector2 closestPointOnEdge = findClosestPointOnSegment(circleCenter, vertexA, vertexB);
            float distanceSquared = (circleCenter - closestPointOnEdge).getSquare();

            if (distanceSquared < minDistanceSquared)
            {
                minDistanceSquared = distanceSquared;
                contact = closestPointOnEdge;
            }
        }

        contactPoints.push_back(contact);

        return contactPoints;
    }

    //Find contact points between two polygons
    std::vector<Vector2> CollisionDetection::findPolygonContactPoints(
        std::vector<Vector2>& verticesA, std::vector<Vector2>& verticesB)
    {
        std::vector<Vector2> contactPoints;
        Vector2 contact1;
        Vector2 contact2;
        int contactCount = 0;

        float minDistanceSquared = std::numeric_limits<float>::infinity();

        //Loop through points of polygon A
        for (int i = 0; i < verticesA.size(); i++)
        {
            Vector2 point = verticesA[i];

            //Check against edges of polygon B and find closest point on edge
            for (int j = 0; j < verticesB.size(); j++)
            {
                Vector2 vertexA = verticesB[j];
                Vector2 vertexB = verticesB[(i + 1) % verticesB.size()];

                Vector2 edge = vertexB - vertexA;
                Vector2 closestPointOnEdge = findClosestPointOnSegment(point, vertexA, vertexB);
                float distanceSquared = (point - closestPointOnEdge).getSquare();

                if (distanceSquared == minDistanceSquared && closestPointOnEdge != contact1)
                {
                    contact2 = closestPointOnEdge;
                    contactCount = 2;
                }
                else if (distanceSquared < minDistanceSquared)
                {
                    minDistanceSquared = distanceSquared;
                    contact1 = closestPointOnEdge;
                    contactCount = 1;
                }
            }
        }

        //Loop through points of polygon B
        for (int i = 0; i < verticesB.size(); i++)
        {
            Vector2 point = verticesB[i];

            //Check against edges of polygon A and find closest point on edge
            for (int j = 0; j < verticesA.size(); j++)
            {
                Vector2 vertexA = verticesA[j];
                Vector2 vertexB = verticesA[(i + 1) % verticesA.size()];

                Vector2 edge = vertexB - vertexA;
                Vector2 closestPointOnEdge = findClosestPointOnSegment(point, vertexA, vertexB);
                float distanceSquared = (point - closestPointOnEdge).getSquare();

                if (distanceSquared == minDistanceSquared && closestPointOnEdge != contact1)
                {
                    contact2 = closestPointOnEdge;
                    contactCount = 2;
                }
                else if (distanceSquared < minDistanceSquared)
                {
                    minDistanceSquared = distanceSquared;
                    contact1 = closestPointOnEdge;
                    contactCount = 1;
                }
            }
        }

        //Return contact points
        if (contactCount == 1)
        {
            contactPoints.push_back(contact1);

            return contactPoints;
        }

        else if (contactCount == 2)
        {
            contactPoints.push_back(contact1);
            contactPoints.push_back(contact2);

            return contactPoints;
        }
    }

    //Find closest point on a segment to another point
    const Vector2 CollisionDetection::findClosestPointOnSegment(
        const Vector2& point, const Vector2& vertexA, const Vector2& vertexB)
    {
        Vector2 edge = vertexB - vertexA;
        Vector2 aToPoint = point - vertexA;

        float projection = aToPoint.projectOntoAxis(edge);
        float edgeLengthSquared = edge.getSquare();
        float distance = projection / edgeLengthSquared;

        if (distance < 0)
        {
            return vertexA;
        }
        else if (distance > 1)
        {
            return vertexB;
        }
        else
        {
            return vertexA + edge * distance;
        }
    }

}