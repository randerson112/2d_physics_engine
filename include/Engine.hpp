//Class defenition for the main engine
//The engine will keep track of all physics bodies positions in the world
//The engine call the update functions of all physics bodies every frame
//The engine will handle world constants like gravity and time

#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "Vector2.hpp"
#include "Collider.hpp"
#include "RectCollider.hpp"
#include "CircleCollider.hpp"
#include "PhysicsBody.hpp"
#include "StaticBody.hpp"
#include "DynamicBody.hpp"
#include "ControllableBody.hpp"

#include <memory>
#include <vector>

class Engine
{
public:
    //Constructors and deconstructors
    Engine();
    ~Engine();

    //Adds a physics body to the world
    void addBody(PhysicsBody* body);

    //Removes a physics body from the world
    void removeBody(PhysicsBody* body);

    //Updates physics bodies in the world, processes physics, and handles collisions
    //Parameter: time since last update call
    void update(float deltaTime);

    //Applies force of gravity on a body
    void applyGravity(DynamicBody* body);

    //Enables or disables physics
    //Paramter: true to enable, false to disable
    void setPhysicsProcess(bool boolValue);

    //Sets the gravity scale of the world
    //Paramter: a non-negative scale factor
    void setGravityScale(float scaleValue);

private:
    Vector2 gravity = {0.0f, 980.0f};

    //Gravity scale of the world
    float gravityScale;

    //Boolean to control whether physics is processed
    bool physicsProcess;

    //List of all physics bodies in the world
    std::vector<PhysicsBody*> physicsBodies;
};

#endif