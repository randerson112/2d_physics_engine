//Implementation of engine class: manages and updates physics bodies

#include "Engine.hpp"

//Constructors and deconstructors
Engine::Engine() {};

Engine::~Engine() {};

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
        *it = nullptr;
        physicsBodies.erase(it);
    }
}

//Updates physics bodies and checks for collisions
void Engine::update(float deltaTime)
{
    for (auto& body : physicsBodies)
    {
        //body->update(deltaTime)
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