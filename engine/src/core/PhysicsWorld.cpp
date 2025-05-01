//Implementation of PhysicsWorld class: manages and updates physics bodies within it

#include "core/PhysicsWorld.hpp"

namespace phys
{
//Constructor to set default world settings
PhysicsWorld::PhysicsWorld()
    : boundary(nullptr), gravityScale(1.0f), physicsProcess(true), collisionsProcess(true) {}

//Destructor to delete all dynamically allocated objects
PhysicsWorld::~PhysicsWorld()
{
    delete boundary;

    for (PhysicsBody* body: physicsBodies)
    {
        delete body;
    }

    physicsBodies.clear();
}

//Sets world boundary dimensions and type
void PhysicsWorld::setWorldBoundaries(float newWidth, float newHeight, BoundaryType type)
{
    //Create new boundary if no boundaries are active
    if (!boundary)
    {
        boundary = new WorldBoundary(newWidth, newHeight, type);
        return;
    }

    //Resize active boundary
    boundary->setDimensions(newWidth, newHeight);

    //Set type
    boundary->setType(type);
}

//Removes boundaries from world
void PhysicsWorld::removeWorldBoundaries()
{
    if (boundary)
    {
        delete boundary;
        boundary = nullptr;
    }
}

//Adds a physics body to the world
void PhysicsWorld::addBody(PhysicsBody* body)
{
    physicsBodies.push_back(body);

    if (boundary)
        if (boundary->placementEnforce(body)) //Enforce world boundary on body when added
            removeBody(body); //Delete the body if boundary type is delete and beyond boundary
}

//Removes a physics body from the world
void PhysicsWorld::removeBody(PhysicsBody* body)
{
    auto it = std::find(physicsBodies.begin(), physicsBodies.end(), body);
    if (it != physicsBodies.end())
    {
        delete *it;
        physicsBodies.erase(it);
    }
}

//Updates physics bodies and checks for collisions
void PhysicsWorld::update(float deltaTime)
{
    processPhysics(deltaTime);
    processCollisions();
}

//Updates physics bodies and applies gravity
void PhysicsWorld::processPhysics(float deltaTime)
{
    //If physics processing is disabled, return early
    if (!physicsProcess) return;

    //Loop through all physics bodies
    for (size_t i = 0; i < physicsBodies.size();)
    {
        PhysicsBody* body = physicsBodies[i];

        //Extra logic for dynamic bodies
        if (body->getType() == BodyType::DynamicBody)
        {
            DynamicBody* dynamicBody = static_cast<DynamicBody*>(body);

            if (dynamicBody->isAffectedByGravity())
                applyGravity(dynamicBody); //Apply gravity to dynamic bodies

            //Enforce boundaries on dynamic body
            if (boundary && boundary->dynamicEnforce(dynamicBody))
            {
                removeBody(dynamicBody); //Delete the body if boundary type is delete and beyond boundary
                continue; //Do not increment index since body was deleted
            }
        }

        body->update(deltaTime); //Update all bodies
        i++; //Increment index
    }
}

//Detect and resolve collisions of physics bodies
void PhysicsWorld::processCollisions()
{
    //If collisions processing is disabled, return early
    if (!collisionsProcess) return;

    //Iterate many times to resolve deep interpenetration
    const int ITERATIONS = 10;

    for (int i = 0; i < ITERATIONS; i++)
    {
        //Nested for loop to check every body against every other body
        for (size_t i = 0; i < physicsBodies.size(); i++)
        {
            PhysicsBody* bodyA = physicsBodies[i];

            for (size_t j = i + 1; j < physicsBodies.size(); j++)
            {
                PhysicsBody* bodyB = physicsBodies[j];

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

                if (!CollisionDetection::checkAABBvsAABB(boundingBoxA, boundingBoxB)) continue;

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
    body->applyForce(gravity * gravityScale * body->getMass());
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

//Pauses or resumes the physics processing
void PhysicsWorld::setPhysicsProcess(bool processPhysics)
{
    physicsProcess = processPhysics;
}

//Pauses or resumes the collision detection
void PhysicsWorld::setCollisionProcess(bool processCollisions)
{
    collisionsProcess = processCollisions;
}

//Sets the gravity scale of the world
void PhysicsWorld::setGravityScale(float scaleValue)
{
    if (scaleValue >= 0) //Ensure non-negative gravity scale
    {
        gravityScale = scaleValue;
    }
}

//Returns the vector of physics bodies in the world
const std::vector<PhysicsBody*>& PhysicsWorld::getBodies() const
{
    return physicsBodies;
}

//Returns a pointer to the boundary
WorldBoundary* PhysicsWorld::getBoundary() const
{
    if (boundary)
        return boundary;

    return nullptr;
}
}