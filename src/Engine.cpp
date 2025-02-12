//Implementation of engine class: manages and updates physics bodies

#include "Engine.hpp"

//Constructor to set default gravity scale and enable physics
Engine::Engine()
    : boundary(nullptr), gravityScale(1.0f), physicsProcess(true), collisionsProcess(true)
    {
        collisionSolver = new CollisionSolver();
    }

//Destructor to delete all physics bodies and world boundary
Engine::~Engine()
{
    delete boundary;

    for (auto& body: physicsBodies)
    {
        delete body;
    }

    physicsBodies.clear();
}

//Sets boundary dimensions for the world
void Engine::setWorldBoundaries(float newWidth, float newHeight)
{
    //Create new boundary if no boundaries are active
    if (boundary == nullptr)
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
    delete boundary;
    boundary = nullptr;
}

//Adds a physics body to the world
void Engine::addBody(PhysicsBody* body)
{
    physicsBodies.push_back(body);

    boundary->placementEnforce(body); //Keeps body within boundaries when added
}

//Removes a physics body from the world
void Engine::removeBody(PhysicsBody* body)
{
    auto it = std::find(physicsBodies.begin(), physicsBodies.end(), body);
    if (it != physicsBodies.end())
    {
        physicsBodies.erase(it);
    }

    delete body;
}

//Updates physics bodies and checks for collisions
void Engine::update(float deltaTime)
{
    if (physicsProcess)
    {
        for (auto& body : physicsBodies)
        {
            if (DynamicBody* dynamicBody = dynamic_cast<DynamicBody*>(body))
            {
                applyGravity(dynamicBody); //Apply gravity to dynamic body

                if (boundary != nullptr)
                    boundary->dynamicEnforce(dynamicBody); //Keep dynamic body within world boundaries
            }

            body->update(deltaTime); //Update body physics
        }

        if (collisionsProcess)
        {
            for (size_t i = 0; i < physicsBodies.size(); i++)
            {
                PhysicsBody* bodyA = physicsBodies[i];

                for (size_t j = i + 1; j < physicsBodies.size(); j++)
                {
                    PhysicsBody* bodyB = physicsBodies[j];

                    Collider* colliderA = bodyA->getCollider();
                    Collider* colliderB = bodyB->getCollider();

                    if (CollisionDetection::checkCollision(colliderA, colliderB))
                    {
                        collisionSolver->addCollision(new Collision(bodyA, bodyB));
                    }
                }
            }

            collisionSolver->resolveCollisions();
        }
    }
}

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