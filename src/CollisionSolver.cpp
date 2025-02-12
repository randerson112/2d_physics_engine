//Implementation of CollisionSolver class to resolve collisions

#include "CollisionSolver.hpp"
#include "Vector2.hpp"
#include "RectCollider.hpp"
#include "CircleCollider.hpp"
#include "StaticBody.hpp"
#include "DynamicBody.hpp"

//Constructor needs no paramters
CollisionSolver::CollisionSolver() {}

//Adds a collision instance to the vector, called from the engine
void CollisionSolver::addCollision(Collision* newCollision)
{
    collisions.push_back(newCollision);
}

//Loops through collisions vector and sort collisions to respective solvers
void CollisionSolver::resolveCollisions()
{
    for (auto& collision : collisions)
    {
        //Get collider shapes
        ColliderShape shapeA = collision->bodyA->getCollider()->getShape();
        ColliderShape shapeB = collision->bodyB->getCollider()->getShape();

        //If first body is a rectangle
        if (shapeA == ColliderShape::Rectangle)
        {
            //If second body is also a rectangle
            if (shapeB == ColliderShape::Rectangle)
                resolveRectRectCollision(collision->bodyA, collision->bodyB);

            //If second body is a circle
            if (shapeB == ColliderShape::Circle)
                resolveRectCircleCollision(collision->bodyA, collision->bodyB);
        }

        //If first body is a circle
        if (shapeA == ColliderShape::Circle)
        {
            //If second body is also a circle
            if (shapeB == ColliderShape::Circle)
                resolveCircleCircleCollision(collision->bodyA, collision->bodyB);

            //If second body is a rectangle
            if (shapeB == ColliderShape::Rectangle)
                resolveRectCircleCollision(collision->bodyB, collision->bodyA);
        }

        //Delete the collision object from memory after resolution
        delete collision;
    }

    //Clears the collisions vector after all are resolved
    collisions.clear();
}

//Resolve a collision with two rectangles
void CollisionSolver::resolveRectRectCollision(PhysicsBody* rectA, PhysicsBody* rectB)
{
    //Rect-Rect collision resolution logic
}

//Resolve a collision with two circles
void CollisionSolver::resolveCircleCircleCollision(PhysicsBody* circleA, PhysicsBody* circleB)
{
    //Get body types
    BodyType typeA = circleA->getType();
    BodyType typeB = circleB->getType();

    //Get colliders
    CircleCollider* colliderA = static_cast<CircleCollider*>(circleA->getCollider());
    CircleCollider* colliderB = static_cast<CircleCollider*>(circleB->getCollider());

    //Get positions of centers
    Vector2 posA = circleA->getPosition();
    Vector2 posB = circleB->getPosition();

    //Get radii
    float radiusA = colliderA->getRadius();
    float radiusB = colliderB->getRadius();

    float sumRadii = radiusA + radiusB;

    //Get collision normal and tangent
    Vector2 normal = posA.getDirectionTo(posB);
    Vector2 tangent = {-normal.y, normal.x};

    //Get penetration depth
    float penDepth = sumRadii - (posA.getVectorTo(posB)).getLength();

    //If first circle is a dynamic physics body
    if (typeA == BodyType::DynamicBody)
    {
        DynamicBody* dynamicCircleA = static_cast<DynamicBody*>(circleA);

        //Get velocity and mass
        Vector2 velocityA = dynamicCircleA->getVelocity();
        float massA = dynamicCircleA->getMass();

        //Move along the inverse normal by half the penetration depth
        dynamicCircleA->move(-normal * penDepth / 2);
        
        //Poject velocity onto normal and tangent axes
        float vNormalA = velocityA.projectOntoAxis(normal);
        float vTangentA = velocityA.projectOntoAxis(tangent);

        //If second circle is also a dynamic physics body
        if (typeB == BodyType::DynamicBody)
        {
            DynamicBody* dynamicCircleB = static_cast<DynamicBody*>(circleB);

            //Get velocity and mass
            Vector2 velocityB = dynamicCircleB->getVelocity();
            float massB = dynamicCircleB->getMass();

            //Move along the normal by half the penetration depth
            dynamicCircleB->move(normal * penDepth / 2);
            
            //Poject velocity onto normal and tangent axes
            float vNormalB = velocityA.projectOntoAxis(normal);
            float vTangentB = velocityA.projectOntoAxis(tangent);
            
            //Compute new normal velocities using conservation of momentum
            float vNormalFinalA = ((massA - massB) * vNormalA + 2 * massB * vNormalB) / (massA + massB);
            float vNormalFinalB = ((massB - massA) * vNormalB + 2 * massA * vNormalA) / (massA + massB);

            //Convert final normal and unchanged tangential components back to vector form
            dynamicCircleA->setVelocity(normal * vNormalFinalA + tangent * vTangentA);
            dynamicCircleB->setVelocity(normal * vNormalFinalB + tangent * vTangentB);
        }
    }
}

//Resolve a collision with a rectangle and a circle
void CollisionSolver::resolveRectCircleCollision(PhysicsBody* rect, PhysicsBody* circle)
{
    //Rect-Circle collision resolution logic
}