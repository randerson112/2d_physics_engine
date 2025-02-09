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
#include "CollisionDetection.hpp"
#include "WorldBoundary.hpp"

#include <memory>
#include <vector>

class Engine
{
private:
    //World boundaries for physics bodies, default no boundaries
    WorldBoundary* boundary;

    //Gravity force vector
    Vector2 gravity = {0.0f, -9.81f};

    //Gravity scale of the world
    float gravityScale;

    //Boolean to control whether physics is processed
    bool physicsProcess;

    //Boolean to control whether collisions are detected
    bool collisionsProcess;

    //List of all physics bodies in the world
    std::vector<PhysicsBody*> physicsBodies;

public:
    //Constructors and deconstructors
    Engine();
    ~Engine();

    //Sets world boundary dimensions for the world
    void setWorldBoundaries(float newWidth, float newHeight);

    //Removes boundaries from world
    void removeWorldBoundaries();

    //Adds a physics body to the world
    void addBody(PhysicsBody* body);

    //Removes a physics body from the world
    void removeBody(PhysicsBody* body);

    //Updates physics bodies in the world, processes physics, and handles collisions
    //Parameter: time since last update call
    void update(float deltaTime);

    //Applies force of gravity on a body
    void applyGravity(DynamicBody* body);

    //Resolve a collision between two bodies
    void resolveCollision(PhysicsBody* bodyA, PhysicsBody* bodyB);

    //Enables or disables physics
    //Parameter: true to enable, false to disable
    void setPhysicsProcess(bool processPhysics);

    //Enables or disables collision detection
    //Parameter: true to enable, false to disable
    void setCollisionProcess(bool processCollisions);

    //Sets the gravity scale of the world
    //Parameter: a non-negative scale factor
    void setGravityScale(float scaleValue);
};

#endif