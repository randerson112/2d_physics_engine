//Implementation of PhysicsWorld class: manages and updates physics bodies within it

#include "core/PhysicsWorld.hpp"

namespace phys
{
    //Constructor to set boundary dimensions and default world settings
    PhysicsWorld::PhysicsWorld(const Vector2& boundaryDimensions) :
        m_boundary(boundaryDimensions, BoundaryType::Delete),
        m_gravityScale(1.0f),
        m_processPhysics(true),
        m_processCollisions(true)
    {
    }

    //Destructor to delete all dynamically allocated objects
    PhysicsWorld::~PhysicsWorld()
    {
        for (PhysicsBody* body : m_physicsBodies)
        {
            delete body;
        }

        m_physicsBodies.clear();
    }

    //Sets world boundary dimensions
    void PhysicsWorld::setBoundaryDimensions(Vector2& newDimensions)
    {
        m_boundary.setDimensions(newDimensions);
    }

    //Sets world boundary type
    void PhysicsWorld::setBoundaryType(BoundaryType type)
    {
        m_boundary.setType(type);
    }

    //Adds a physics body to the world
    void PhysicsWorld::addBody(PhysicsBody* body)
    {
        m_physicsBodies.push_back(body);

        if (m_boundary.placementEnforce(body)) //Enforce world boundary on body when added
            removeBody(body);                  //Delete the body if boundary type is delete and beyond boundary
    }

    //Removes a physics body from the world
    void PhysicsWorld::removeBody(PhysicsBody* body)
    {
        auto it = std::find(m_physicsBodies.begin(), m_physicsBodies.end(), body);
        if (it != m_physicsBodies.end())
        {
            delete *it;
            m_physicsBodies.erase(it);
        }
    }

    //Updates physics bodies and checks for collisions
    void PhysicsWorld::update(float deltaTime)
    {
        updatePhysics(deltaTime);
        updateCollisions();
    }

    //Updates physics bodies and applies gravity
    void PhysicsWorld::updatePhysics(float deltaTime)
    {
        //If physics processing is disabled, return early
        if (!m_processPhysics)
            return;

        //Loop through all physics bodies
        for (size_t i = 0; i < m_physicsBodies.size();)
        {
            PhysicsBody* body = m_physicsBodies[i];

            //Extra logic for dynamic bodies
            if (body->getType() == BodyType::DynamicBody)
            {
                DynamicBody* dynamicBody = static_cast<DynamicBody*>(body);

                if (dynamicBody->isAffectedByGravity())
                    applyGravity(dynamicBody); //Apply gravity to dynamic bodies

                //Enforce boundaries on dynamic body
                if (m_boundary.dynamicEnforce(dynamicBody))
                {
                    removeBody(dynamicBody); //Delete the body if boundary type is delete and beyond boundary
                    continue;                //Do not increment index since body was deleted
                }
            }

            body->update(deltaTime); //Update all bodies
            i++;                     //Increment index
        }
    }

    //Detect and resolve collisions of physics bodies
    void PhysicsWorld::updateCollisions()
    {
        //If collisions processing is disabled, return early
        if (!m_processCollisions)
            return;

        //Iterate many times to resolve deep interpenetration
        const int ITERATIONS = 10;

        for (int i = 0; i < ITERATIONS; i++)
        {
            //Nested for loop to check every body against every other body
            for (size_t i = 0; i < m_physicsBodies.size(); i++)
            {
                PhysicsBody* bodyA = m_physicsBodies[i];

                for (size_t j = i + 1; j < m_physicsBodies.size(); j++)
                {
                    PhysicsBody* bodyB = m_physicsBodies[j];

                    //Get the colliders of the bodies
                    Collider* colliderA = bodyA->getCollider();
                    Collider* colliderB = bodyB->getCollider();

                    //Get collider types
                    ColliderType colliderTypeA = colliderA->getType();
                    ColliderType colliderTypeB = colliderB->getType();

                    //Get the body types
                    BodyType typeA = bodyA->getType();
                    BodyType typeB = bodyB->getType();

                    //If both are static bodies, no need to check for a collision
                    if (typeA == BodyType::StaticBody && typeB == BodyType::StaticBody)
                        continue;

                    //If one of the bodies has a trigger collider, no need to resolve collision
                    if (colliderTypeA == ColliderType::Trigger || colliderTypeB == ColliderType::Trigger)
                        continue;

                    //First check if AABBs are intersecting (Broad phase)
                    const AABB boundingBoxA = colliderA->getAABB();
                    const AABB boundingBoxB = colliderB->getAABB();

                    if (!CollisionDetection::checkAABBvsAABB(boundingBoxA, boundingBoxB))
                        continue;

                    //Check collision between colliders (Narrow phase)
                    Collision* collision = CollisionDetection::checkCollision(bodyA, bodyB);
                    if (collision)
                    {
                        CollisionResolution::resolveCollision(*collision); //Resolve collision
                    }

                    delete collision; //Delete collision data after resolution
                }
            }
        }
    }

    //Applies the force of gravity to a dynamic body
    void PhysicsWorld::applyGravity(DynamicBody* body) const
    {
        body->applyForce(m_gravity * m_gravityScale * body->getMass());
    }

    //Return true if given physics bodies are colliding
    bool PhysicsWorld::checkIfColliding(PhysicsBody* bodyA, PhysicsBody* bodyB)
    {
        Collision* collision = CollisionDetection::checkCollision(bodyA, bodyB);

        if (collision != nullptr)
            return true;
        else
            return false;
    }

    bool PhysicsWorld::checkIfOnFloor(const PhysicsBody* body) const
    {
        return m_boundary.checkIfOnFloor(body);
    }

    //Pauses or resumes the physics processing
    void PhysicsWorld::setPhysicsProcess(bool processPhysics)
    {
        m_processPhysics = processPhysics;
    }

    //Pauses or resumes the collision detection
    void PhysicsWorld::setCollisionProcess(bool processCollisions)
    {
        m_processCollisions = processCollisions;
    }

    //Sets the gravity scale of the world
    void PhysicsWorld::setGravityScale(float newScaleValue)
    {
        if (newScaleValue >= 0) //Ensure non-negative gravity scale
        {
            m_gravityScale = newScaleValue;
        }
    }

    //Returns the vector of physics bodies in the world
    const std::vector<PhysicsBody*>& PhysicsWorld::getBodies() const
    {
        return m_physicsBodies;
    }
}