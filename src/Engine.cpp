//Implementation of engine class: manages and updates physics bodies

#include "Engine.hpp"

//Constructor to set default gravity scale and enable physics
Engine::Engine() : gravityScale(1.0f), physicsProcess(true) {}

//Destructor to delete all physics bodies
Engine::~Engine()
{
    for (auto& body: physicsBodies)
    {
        delete body;
    }

    physicsBodies.clear();
}

//Adds a physics body to the world
void Engine::addBody(PhysicsBody* body)
{
    physicsBodies.push_back(body);
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
    if (physicsProcess)
    {
        for (auto& body : physicsBodies)
        {
            if (DynamicBody* dynamicBody = dynamic_cast<DynamicBody*>(body))
            {
                applyGravity(dynamicBody); //Apply gravity to dynamic bodies
            }

            body->update(deltaTime); //Update all bodies
        }

        for (size_t i = 0; i < physicsBodies.size(); i++)
        {
            PhysicsBody* bodyA = physicsBodies[i];

            for (size_t j = i + 1; j < physicsBodies.size(); j++)
            {
                PhysicsBody* bodyB = physicsBodies[j];

                Collider* colliderA = bodyA->getCollider();
                Collider* colliderB = bodyB->getCollider();

                if (colliderA->checkCollision(colliderB))
                {
                    resolveCollision(bodyA, bodyB);
                }
            }
        }
    }
}

void Engine::applyGravity(DynamicBody* body)
{
    body->applyForce(gravity * gravityScale * body->getMass());
}

void Engine::resolveCollision(PhysicsBody* bodyA, PhysicsBody* bodyB)
{
    //Simple collision resolution for now, just adjusting positions
    Vector2 overlap = bodyA->getPosition() - bodyB->getPosition();

    //Resolve overlap by moving them apart
    if (overlap.x > 0) {
        bodyA->setPosition(bodyA->getPosition() + Vector2(overlap.x / 2, 0));
        bodyB->setPosition(bodyB->getPosition() - Vector2(overlap.x / 2, 0));
    }
    if (overlap.y > 0) {
        bodyA->setPosition(bodyA->getPosition() + Vector2(0, overlap.y / 2));
        bodyB->setPosition(bodyB->getPosition() - Vector2(0, overlap.y / 2));
    }

    // Apply more complex resolution logic here, like adjusting velocities or applying forces
}

//Pauses or resumes the physics processing
void Engine::setPhysicsProcess(bool boolValue)
{
    physicsProcess = boolValue;
}

//Sets the gravity scale of the world
void Engine::setGravityScale(float scaleValue)
{
    if (scaleValue >= 0) //Ensure non-negative gravity scale
    {
        gravityScale = scaleValue;
    }
}