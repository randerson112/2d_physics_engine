//Implementation of CollisionSolver class to resolve collisions

#include "physics/CollisionSolver.hpp"
#include "core/Vector2.hpp"
#include "collisions/RectCollider.hpp"
#include "collisions/CircleCollider.hpp"
#include "physics/StaticBody.hpp"
#include "physics/DynamicBody.hpp"

//Constructor needs no paramters
CollisionSolver::CollisionSolver() {}

//Destructor to delete lingering collision objects
CollisionSolver::~CollisionSolver()
{
    for (Collision* collision : collisions)
    {
        delete collision;
    }

    collisions.clear();
}

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
                resolveRectRectCollision(collision->bodyA, collision->bodyB, collision->normal, collision->penDepth);

            //If second body is a circle
            if (shapeB == ColliderShape::Circle)
                resolveRectCircleCollision(collision->bodyA, collision->bodyB, collision->normal, collision->penDepth);
        }

        //If first body is a circle
        if (shapeA == ColliderShape::Circle)
        {
            //If second body is also a circle
            if (shapeB == ColliderShape::Circle)
                resolveCircleCircleCollision(collision->bodyA, collision->bodyB, collision->normal, collision->penDepth);

            //If second body is a rectangle
            if (shapeB == ColliderShape::Rectangle)
                resolveRectCircleCollision(collision->bodyB, collision->bodyA, collision->normal, collision->penDepth);
        }

        //Delete the collision object from memory after resolution
        delete collision;
    }

    //Clears the collisions vector after all are resolved
    collisions.clear();
}

//Resolve a collision with two rectangles
void CollisionSolver::resolveRectRectCollision(PhysicsBody* rectA, PhysicsBody* rectB, Vector2 normal, float penDepth)
{
    //Rect-Rect collision resolution logic
}

//Resolve a collision with two circles
void CollisionSolver::resolveCircleCircleCollision(PhysicsBody* circleA, PhysicsBody* circleB, Vector2 normal, float penDepth)
{
    //Get body types
    BodyType typeA = circleA->getType();
    BodyType typeB = circleB->getType();

    // Ensure circleA is always the dynamic body
    if (circleA->getType() == BodyType::StaticBody && circleB->getType() == BodyType::DynamicBody)
    {
        std::swap(circleA, circleB);
    }

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

    DynamicBody* dynamicCircleA = static_cast<DynamicBody*>(circleA);

    //Get velocity, restitution, and mass
    Vector2 velocityA = dynamicCircleA->getVelocity();
    float restitutionA = dynamicCircleA->getRestitution();
    float massA = dynamicCircleA->getMass();
    
    //If second circle is also a dynamic physics body
    if (typeB == BodyType::DynamicBody)
    {
        DynamicBody* dynamicCircleB = static_cast<DynamicBody*>(circleB);

        //Get velocity, restitution, and mass
        Vector2 velocityB = dynamicCircleB->getVelocity();
        float restitutionB = dynamicCircleB->getRestitution();
        float massB = dynamicCircleB->getMass();

        //Move circles along the normal by half the penetration depth
        dynamicCircleA->move(-normal * penDepth / 2);
        dynamicCircleB->move(normal * penDepth / 2);

        //Get relative velocity
        Vector2 relVelocity = velocityB - velocityA;

        //Get minimum restitution
        float e = std::min(restitutionA, restitutionB);

        //Get the impulse magnitude
        float j = -(1 + e) * relVelocity.projectOntoAxis(normal);
        j /= (1 / massA) + (1 / massB);

        //Calculate and set new velocities
        dynamicCircleA->setVelocity(dynamicCircleA->getVelocity() - normal * j / massA);
        dynamicCircleB->setVelocity(dynamicCircleB->getVelocity() + normal * j / massB);
    }

    //If second circle is a static physics body
    if (typeB == BodyType::StaticBody)
    {
        StaticBody* staticCircleB = static_cast<StaticBody*>(circleB);

        //Move dynamic circle along normal by the full penetration depth
        dynamicCircleA->move(-normal * penDepth);

        //Reflect the dynamic circle velocity along the normal
        Vector2 reflectedVelocity = velocityA - normal * (1 + restitutionA) * velocityA.projectOntoAxis(normal);
        dynamicCircleA->setVelocity(reflectedVelocity);
    }
}

//Resolve a collision with a rectangle and a circle
void CollisionSolver::resolveRectCircleCollision(PhysicsBody* rect, PhysicsBody* circle, Vector2 normal, float penDepth)
{
    //Get body types
    BodyType rectType = rect->getType();
    BodyType circleType = circle->getType();

    //Get positions of centers
    Vector2 rectPos = rect->getPosition();
    Vector2 circlePos = circle->getPosition();

    //Get colliders
    RectCollider* rectCollider = static_cast<RectCollider*>(rect->getCollider());
    CircleCollider* circleCollider = static_cast<CircleCollider*>(rect->getCollider());

    //Get circle radius
    float circleRadius = circleCollider->getRadius();

    //If the rectangle is a static body
    if (rectType == BodyType::StaticBody)
    {
        //If the circle is a dynamic body
        if (circleType == BodyType::DynamicBody)
        {
            DynamicBody* dynamicCircle = static_cast<DynamicBody*>(circle);

            //Get circle velocity, restitution, and mass
            Vector2 circleVelocity = dynamicCircle->getVelocity();
            float circleRestitution = dynamicCircle->getRestitution();
            float circleMass = dynamicCircle->getMass();

            //Move dynamic circle along normal by the full penetration depth
            dynamicCircle->move(normal * penDepth);

            //Reflect the dynamic circle velocity along the normal
            Vector2 reflectedVelocity = circleVelocity - normal * (1 + circleRestitution) * circleVelocity.projectOntoAxis(normal);
            dynamicCircle->setVelocity(reflectedVelocity);
        }
    }
}