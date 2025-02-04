//Implementation of engine class: manages and updates physics bodies

#include "Engine.hpp"

//Constructors and deconstructors
Engine::Engine() {};

Engine::~Engine() {};

//Adds a physics body to the world
void Engine::addBody(std::unique_ptr<PhysicsBody> body)
{
    physicsBodies.push_back(body);
}

//Removes a physics body from the world
void Engine::removeBody(std::unique_ptr<PhysicsBody> body)
{
    auto it = std::find_if(physicsBodies.begin(), physicsBodies.end(),
        [&body](const std::unique_ptr<PhysicsBody>& b) {
            return b.get() == body.get();  // Compare the raw pointers
        });

    if (it != physicsBodies.end())
    {
        physicsBodies.erase(it); //remove the physics body from list
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