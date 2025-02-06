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
        for (size_t j = i + 1; j < physicsBodies.size(); j++)
        {
            //check if physicsBodies[i] and physicsBodies[j] are colliding
            //this will check every body for if it is colliding with any other body
            //physicsBodies[i]->checkCollision(physicsBodies[j]) Something like this
        }
    }
}

void Engine::applyGravity(DynamicBody* body)
{
    body->applyForce(gravity * gravityScale * body->getMass());
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