//Implementation of engine class: manages and updates physics bodies

#include "core/Engine.hpp"

//Constructor to set default engine settings
Engine::Engine()
    : boundary(nullptr), gravityScale(1.0f), physicsProcess(true), collisionsProcess(true)
    {
        collisionSolver = new CollisionSolver();
    }

//Destructor to delete all dynamically allocated objects
Engine::~Engine()
{
    delete collisionSolver;
    delete boundary;

    for (PhysicsBody* body: physicsBodies)
    {
        delete body;
    }

    physicsBodies.clear();
}

//Sets boundary dimensions for the world
void Engine::setWorldBoundaries(float newWidth, float newHeight)
{
    //Create new boundary if no boundaries are active
    if (!boundary)
    {
        boundary = new WorldBoundary(newWidth, newHeight);
        return;
    }

    //Resize active boundary
    boundary->setDimensions(newWidth, newHeight);
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
        boundary->placementEnforce(body); //Keeps body within boundaries when added
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
    //If physics processing is disabled, return early
    if (!physicsProcess) return;

    //Loop through all physics bodies
    for (auto& body : physicsBodies)
    {
        //Extra logic for dynamic bodies
        if (body->getType() == BodyType::DynamicBody)
        {
            DynamicBody* dynamicBody = static_cast<DynamicBody*>(body);

            applyGravity(dynamicBody); //Apply gravity to dynamic bodies

            if (boundary)
                boundary->dynamicEnforce(dynamicBody); //Keep dynamic bodies within world boundaries
        }

        body->update(deltaTime); //Update all bodies
    }

    //If collisions processing is disabled, return early
    if (!collisionsProcess) return;

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
            if (CollisionDetection::checkCollision(colliderA, colliderB))
            {
                collisionSolver->addCollision(new Collision(bodyA, bodyB));
            }
        }
    }

    collisionSolver->resolveCollisions(); //Collision solver resolves all collisions detected this frame
}

//Applies the force of gravity to a dynamic body
void Engine::applyGravity(DynamicBody* body)
{
    body->applyForce(gravity * gravityScale * body->getMass());
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