//Implementation of PhysicsWorld class: manages and updates physics bodies within it

#include "core/PhysicsWorld.hpp"

namespace phys
{
    //Constructor to set boundary dimensions and default world settings
    PhysicsWorld::PhysicsWorld(const Vector2& boundaryDimensions) :
        m_boundary(boundaryDimensions, BoundaryType::Delete),
        m_quadtree(boundaryDimensions),
        m_gravityScale(1.0f),
        m_processPhysics(true),
        m_processCollisions(true),
        m_rotationalPhysics(true)
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

        // === Broad Phase ===

        m_quadtree.clear();

        // Insert all bodies into quadtree
        for (auto body : m_physicsBodies)
        {
            m_quadtree.insert(body);
        }

        // Gather potentially colliding pairs
        std::vector<std::pair<PhysicsBody*, PhysicsBody*>> potentialCollisions;
        m_quadtree.gatherPairs(potentialCollisions);

        // === Narrow Phase ===

        const int ITERATIONS = 3;
        for (int i = 0; i < ITERATIONS; i++)
        {
            for (auto [bodyA, bodyB] : potentialCollisions)
            {
                // Check for collision between AABB
                if (!bodyA->getCollider()->getAABB().intersects(bodyB->getCollider()->getAABB()))
                    continue;

                // Check for collision between shapes
                Collision* collision = CollisionDetection::checkCollision(bodyA, bodyB);
                if (collision)
                {
                    // Resolve collision
                    if (m_rotationalPhysics)
                        CollisionResolution::resolveAdvancedCollision(*collision);
                    else
                        CollisionResolution::resolveBasicCollision(*collision);
                }

                // Delete collision data
                delete collision;
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

    //Enables or disables rotational physics in the world
    void PhysicsWorld::setRotationalPhysics(bool rotationalPhysics)
    {
        m_rotationalPhysics = rotationalPhysics;
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