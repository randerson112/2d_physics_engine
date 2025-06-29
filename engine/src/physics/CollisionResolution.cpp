//Implementation of collision resolution functions

#include "physics/CollisionResolution.hpp"

namespace phys
{
    //Sort collision to respective solver for collisions without rotation
    void CollisionResolution::resolveBasicCollision(const Collision& collision)
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
                resolveBasicDynamicCollision(dynamicBodyA,
                    dynamicBodyB,
                    collision.normal,
                    collision.penDepth);
            }

            //If second body is a static body
            else if (typeB == BodyType::StaticBody)
            {
                StaticBody* staticBodyB = static_cast<StaticBody*>(collision.bodyB);

                //Resolve collision between a dynamic body and a static body
                resolveBasicDynamicStaticCollision(dynamicBodyA,
                    staticBodyB,
                    collision.normal,
                    collision.penDepth);
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
                resolveBasicDynamicStaticCollision(dynamicBodyB,
                    staticBodyA,
                    -collision.normal,
                    collision.penDepth);
            }
        }
    }

    //Sort collision to respective solver for collisions with rotation
    void CollisionResolution::resolveAdvancedCollision(const Collision& collision)
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
                resolveAdvancedDynamicCollision(dynamicBodyA,
                    dynamicBodyB,
                    collision.normal,
                    collision.penDepth,
                    collision.contactPoints,
                    collision.contactCount);
            }

            //If second body is a static body
            else if (typeB == BodyType::StaticBody)
            {
                StaticBody* staticBodyB = static_cast<StaticBody*>(collision.bodyB);

                //Resolve collision between a dynamic body and a static body
                resolveAdvancedDynamicStaticCollision(dynamicBodyA,
                    staticBodyB,
                    collision.normal,
                    collision.penDepth,
                    collision.contactPoints,
                    collision.contactCount);
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
                resolveAdvancedDynamicStaticCollision(dynamicBodyB,
                    staticBodyA,
                    -collision.normal,
                    collision.penDepth,
                    collision.contactPoints,
                    collision.contactCount);
            }
        }
    }

    //Resolve a collision between a dynamic body and a static body
    void CollisionResolution::resolveBasicDynamicStaticCollision(
        DynamicBody* dynamicBody, StaticBody* staticBody, const Vector2& normal, float penDepth)
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
    void CollisionResolution::resolveBasicDynamicCollision(
        DynamicBody* bodyA, DynamicBody* bodyB, const Vector2& normal, float penDepth)
    {
        //get velocities, restitutions, and inverse masses of both bodies
        Vector2 velocityA = bodyA->getVelocity();
        Vector2 velocityB = bodyB->getVelocity();

        float restitutionA = bodyA->getRestitution();
        float restitutionB = bodyB->getRestitution();

        float invMassA = bodyA->getInvMass();
        float invMassB = bodyB->getInvMass();

        //Move bodies along the normal by half the penetration depth
        bodyA->move(-normal * penDepth / 2);
        bodyB->move(normal * penDepth / 2);

        //Get relative velocity
        Vector2 relVelocity = velocityB - velocityA;

        //Get minimum restitution
        float e = std::min(restitutionA, restitutionB);

        //Get the impulse magnitude
        float j = -(1 + e) * relVelocity.projectOntoAxis(normal);
        j /= invMassA + invMassB;

        //Calculate and set new velocities
        bodyA->setVelocity(bodyA->getVelocity() - normal * j * invMassA);
        bodyB->setVelocity(bodyB->getVelocity() + normal * j * invMassB);
    }

    //Resolve a collision between a dynamic body and a static body, with rotations
    void CollisionResolution::resolveAdvancedDynamicStaticCollision(DynamicBody* dynamicBody,
        StaticBody* staticBody,
        const Vector2& normal,
        float penDepth,
        const std::vector<Vector2>& contactPoints,
        int contactCount)
    {
        //Move dynamic body out of penetration
        const float percent = 0.50f; //50% correction
        dynamicBody->move(-normal * penDepth * percent);

        //Get properties
        Vector2 position = dynamicBody->getPosition();
        Vector2 linearVelocity = dynamicBody->getVelocity();
        float angularVelocity = dynamicBody->getAngularVelocity();
        float restitution = dynamicBody->getRestitution();
        float invMass = dynamicBody->getInvMass();
        float invInertia = dynamicBody->getInvRotationalInertia();

        //Vectors for storing values
        std::vector<Vector2> impulses;
        std::vector<Vector2> raValues;

        //Calculate impulses for each contact point
        for (int i = 0; i < contactCount; i++)
        {
            Vector2 contactPoint = contactPoints[i];
            Vector2 ra = contactPoint - position;
            raValues.push_back(ra);

            // Velocity at contact point
            Vector2 rotComponent = Vector2(-ra.y, ra.x) * angularVelocity;
            Vector2 velAtContact = linearVelocity + rotComponent;
            float contactVelocityMagnitude = velAtContact.projectOntoAxis(normal);

            if (contactVelocityMagnitude < 0)
            {
                impulses.push_back(Vector2());
                continue;
            }

            float raCrossN = ra.crossProduct(normal);
            float denom = invMass + (raCrossN * raCrossN) * invInertia;

            float j = -(1.0f + restitution) * contactVelocityMagnitude / denom;
            j /= static_cast<float>(contactCount);

            Vector2 impulse = -normal * j;
            impulses.push_back(impulse);
        }

        //Apply impulses
        Vector2 newVelocity = linearVelocity;
        float newAngularVelocity = angularVelocity;

        for (int i = 0; i < contactCount; i++)
        {
            Vector2 impulse = impulses[i];
            Vector2 ra = raValues[i];

            if (impulse.getLength() == 0.0f)
                continue;

            newVelocity += -impulse * invMass;
            newAngularVelocity += -ra.crossProduct(impulse) * invInertia;
        }

        dynamicBody->setVelocity(newVelocity);
        dynamicBody->setAngularVelocity(newAngularVelocity);
    }

    //Resolve a collision between two dynamic bodies, with rotation
    void CollisionResolution::resolveAdvancedDynamicCollision(DynamicBody* bodyA,
        DynamicBody* bodyB,
        const Vector2& normal,
        float penDepth,
        const std::vector<Vector2>& contactPoints,
        int contactCount)
    {
        //Get properties
        Vector2 positionA = bodyA->getPosition();
        Vector2 positionB = bodyB->getPosition();

        Vector2 linearVelocityA = bodyA->getVelocity();
        Vector2 linearVelocityB = bodyB->getVelocity();

        float angularVelocityA = bodyA->getAngularVelocity();
        float angularVelocityB = bodyB->getAngularVelocity();

        float restitutionA = bodyA->getRestitution();
        float restitutionB = bodyB->getRestitution();

        float invMassA = bodyA->getInvMass();
        float invMassB = bodyB->getInvMass();

        float invInertiaA = bodyA->getInvRotationalInertia();
        float invInertiaB = bodyB->getInvRotationalInertia();

        //Clamp restitution
        float e = std::min(std::max(std::min(restitutionA, restitutionB), 0.0f), 1.0f);

        //Move bodies to resolve penetration
        const float percent = 0.5f; // 50% correction
        bodyA->move(-normal * penDepth * percent / 2.0f);
        bodyB->move(normal * penDepth * percent / 2.0f);

        //Vectors to store values
        std::vector<Vector2> impulses;
        std::vector<Vector2> raValues;
        std::vector<Vector2> rbValues;

        //Calculate impulses for each contact point
        for (int i = 0; i < contactCount; i++)
        {
            Vector2 ra = contactPoints[i] - positionA;
            Vector2 rb = contactPoints[i] - positionB;
            raValues.push_back(ra);
            rbValues.push_back(rb);

            //Velocity at contact points
            Vector2 velA = linearVelocityA + Vector2(-ra.y, ra.x) * angularVelocityA;
            Vector2 velB = linearVelocityB + Vector2(-rb.y, rb.x) * angularVelocityB;

            Vector2 relVelocity = velB - velA;
            float contactVelocityMagnitude = relVelocity.projectOntoAxis(normal);

            if (contactVelocityMagnitude > 0)
            {
                impulses.push_back(Vector2());
                continue;
            }

            float raCrossN = ra.crossProduct(normal);
            float rbCrossN = rb.crossProduct(normal);

            float denom =
                invMassA + invMassB + (raCrossN * raCrossN) * invInertiaA + (rbCrossN * rbCrossN) * invInertiaB;

            float j = -(1.0f + e) * contactVelocityMagnitude / denom;
            j /= static_cast<float>(contactCount);

            Vector2 impulse = normal * j;
            impulses.push_back(impulse);
        }

        //Apply impulses
        Vector2 newLinearVelocityA = linearVelocityA;
        float newAngularVelocityA = angularVelocityA;

        Vector2 newLinearVelocityB = linearVelocityB;
        float newAngularVelocityB = angularVelocityB;

        for (int i = 0; i < contactCount; i++)
        {
            Vector2 impulse = impulses[i];
            Vector2 ra = raValues[i];
            Vector2 rb = rbValues[i];

            if (impulse.getLength() == 0.0f)
                continue;

            newLinearVelocityA += -impulse * invMassA;
            newAngularVelocityA += -ra.crossProduct(impulse) * invInertiaA;

            newLinearVelocityB += impulse * invMassB;
            newAngularVelocityB += rb.crossProduct(impulse) * invInertiaB;
        }

        bodyA->setVelocity(newLinearVelocityA);
        bodyA->setAngularVelocity(newAngularVelocityA);

        bodyB->setVelocity(newLinearVelocityB);
        bodyB->setAngularVelocity(newAngularVelocityB);
    }

}