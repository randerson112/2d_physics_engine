//Implementation of collision resolution functions

#include "physics/CollisionSolver.hpp"

//Sort collision to respective solver
void CollisionResolution::resolveCollision(const Collision& collision)
{
    //Get body types
    BodyType typeA = collision.bodyA->getType();
    BodyType typeB = collision.bodyB->getType();

    //If the first body is dynamic
    if (typeA == BodyType::DynamicBody)
    {
        DynamicBody* dynamicBodyA = static_cast<DynamicBody*>(collision.bodyA);

        //If the second body is also dynamic
        if (typeB == BodyType::DynamicBody)
        {
            DynamicBody* dynamicBodyB = static_cast<DynamicBody*>(collision.bodyB);

            //Resolve collision between two dynamic bodies
            resolveDynamicCollision(dynamicBodyA, dynamicBodyB, collision.normal, collision.penDepth);
        }

        //If second body is a static body
        else if (typeB == BodyType::StaticBody)
        {
            StaticBody* staticBodyB = static_cast<StaticBody*>(collision.bodyB);

            //Resolve collision between a dynamic body and a static body
            resolveDynamicStaticCollision(dynamicBodyA, staticBodyB, collision.normal, collision.penDepth);
        }
    }

    //If the first body is a static body
    else if (typeA == BodyType::StaticBody)
    {
        StaticBody* staticBodyA = static_cast<StaticBody*>(collision.bodyA);

        //If the second body is a dynamic body
        if (typeB == BodyType::DynamicBody)
        {
            DynamicBody* dynamicBodyB = static_cast<DynamicBody*>(collision.bodyB);

            //Resolve collision between a dynamic body and a static body
            //Flip the normal since we switched the order of bodies
            resolveDynamicStaticCollision(dynamicBodyB, staticBodyA, -collision.normal, collision.penDepth);
        }
    }
}

//Resolve a collision between a dynamic body and a static body
void CollisionResolution::resolveDynamicStaticCollision(DynamicBody* dynamicBody, StaticBody* staticBody, const Vector2& normal, float penDepth)
{
    //Get velocity, restitution, and mass of dynamic body
    Vector2 velocity = dynamicBody->getVelocity();
    float restitution = dynamicBody->getRestitution();
    float mass = dynamicBody->getMass();

    //Move dynamic body along normal by the full penetration depth
    dynamicBody->move(-normal * penDepth);

    //Reflect the dynamic body velocity along the normal
    Vector2 reflectedVelocity = velocity - normal * (1 + restitution) * velocity.projectOntoAxis(normal);
    dynamicBody->setVelocity(reflectedVelocity);
}

//Resolve a collision between two dynamic bodies
void CollisionResolution::resolveDynamicCollision(DynamicBody* bodyA, DynamicBody* bodyB, const Vector2& normal, float penDepth)
{
    //get velocities, restitutions, and masses of both bodies
    Vector2 velocityA = bodyA->getVelocity();
    Vector2 velocityB = bodyB->getVelocity();

    float restitutionA = bodyA->getRestitution();
    float restitutionB = bodyB->getRestitution();

    float massA = bodyA->getMass();
    float massB = bodyB->getMass();

    //Move bodies along the normal by half the penetration depth
    bodyA->move(-normal * penDepth / 2);
    bodyB->move(normal * penDepth / 2);

    //Get relative velocity
    Vector2 relVelocity = velocityB - velocityA;

    //Get minimum restitution
    float e = std::min(restitutionA, restitutionB);

    //Get the impulse magnitude
    float j = -(1 + e) * relVelocity.projectOntoAxis(normal);
    j /= (1 / massA) + (1 / massB);

    //Calculate and set new velocities
    bodyA->setVelocity(bodyA->getVelocity() - normal * j / massA); 
    bodyB->setVelocity(bodyB->getVelocity() + normal * j / massB);
}