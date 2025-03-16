//Implementation of engine class: manages and updates physics bodies

#include "core/Engine.hpp"

//Constructor to set default engine settings
Engine::Engine()
    : boundary(nullptr), gravityScale(1.0f), physicsProcess(true), collisionsProcess(true) {}

//Destructor to delete all dynamically allocated objects
Engine::~Engine()
{
    delete boundary;

    for (PhysicsBody* body: physicsBodies)
    {
        delete body;
    }

    physicsBodies.clear();
}

//Sets world boundary dimensions and type
void Engine::setWorldBoundaries(float newWidth, float newHeight, BoundaryType type)
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
void Engine::removeWorldBoundaries()
{
    if (boundary)
    {
        delete boundary;
        boundary = nullptr;
    }
}

//Adds a physics body to the world
void Engine::addBody(PhysicsBody* body)
{
    physicsBodies.push_back(body);

    if (boundary)
        if (boundary->placementEnforce(body)) //Enforce world boundary on body when added
            removeBody(body); //Delete the body if boundary type is delete and beyond boundary
}

//Removes a physics body from the world
void Engine::removeBody(PhysicsBody* body)
{
    auto it = std::find(physicsBodies.begin(), physicsBodies.end(), body);
    if (it != physicsBodies.end())
    {
        delete *it;
        physicsBodies.erase(it);
    }
}

//Updates physics bodies and checks for collisions
void Engine::update(float deltaTime)
{
    processPhysics(deltaTime);
    processCollisions();
}

//Updates physics bodies and applies gravity
void Engine::processPhysics(float deltaTime)
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
void Engine::processCollisions()
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

                //Get the body types
                BodyType typeA = bodyA->getType();
                BodyType typeB = bodyB->getType();

                //If both are static bodies, no need to check for a collision
                if (typeA == BodyType::StaticBody && typeB == BodyType::StaticBody)
                    continue;

                //If a collision is detected between the colliders, pass bodies to collision solver
                Collision* collision = CollisionDetection::checkCollision(bodyA, bodyB);
                if (collision)
                {
                    collisionSolver.addCollision(collision);
                }
            }
        }

        collisionSolver.resolveCollisions(); //Collision solver resolves all collisions detected this iteration
    }
}

//Applies the force of gravity to a dynamic body
void Engine::applyGravity(DynamicBody* body) const
{
    body->applyForce(gravity * gravityScale * body->getMass());
}

//Return true if given physics bodies are colliding
bool Engine::checkIfColliding(PhysicsBody* bodyA, PhysicsBody* bodyB)
{
    Collision* collision = CollisionDetection::checkCollision(bodyA, bodyB);
        
    if (collision != nullptr)
        return true;
    else
        return false;
}

//Pauses or resumes the physics processing
void Engine::setPhysicsProcess(bool processPhysics)
{
    physicsProcess = processPhysics;
}

//Pauses or resumes the collision detection
void Engine::setCollisionProcess(bool processCollisions)
{
    collisionsProcess = processCollisions;
}

//Sets the gravity scale of the world
void Engine::setGravityScale(float scaleValue)
{
    if (scaleValue >= 0) //Ensure non-negative gravity scale
    {
        gravityScale = scaleValue;
    }
}

//Returns the vector of physics bodies in the world
const std::vector<PhysicsBody*>& Engine::getBodies() const
{
    return physicsBodies;
}