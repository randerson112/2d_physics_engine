//Class defenition for the main engine
//The engine will keep track of all physics bodies positions in the world
//The engine call the update functions of all physics bodies every frame
//The engine will handle world constants like gravity and time

#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "core/Vector2.hpp"
#include "core/WorldBoundary.hpp"
#include "collisions/Collider.hpp"
#include "collisions/RectCollider.hpp"
#include "collisions/CircleCollider.hpp"
#include "collisions/CollisionDetection.hpp"
#include "collisions/Collision.hpp"
#include "physics/PhysicsBody.hpp"
#include "physics/StaticBody.hpp"
#include "physics/DynamicBody.hpp"
#include "physics/CollisionSolver.hpp"

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

    //Keeps track of collision instances and resolves them
    CollisionSolver collisionSolver;

    //List of all physics bodies in the world
    std::vector<PhysicsBody*> physicsBodies;

public:
    //Constructors and deconstructors
    Engine();
    ~Engine();

    //Sets world boundary dimensions and type
    void setWorldBoundaries(float newWidth, float newHeight, BoundaryType type);

    //Removes boundaries from world
    void removeWorldBoundaries();

    //Adds a physics body to the world
    void addBody(PhysicsBody* body);

    //Removes a physics body from the world
    void removeBody(PhysicsBody* body);

    //Updates physics bodies in the world, processes physics, and handles collisions
    //Parameter: time since last update call
    //Calls processPhysics and processCollisions functions
    void update(float deltaTime);

    //Updates physics bodies and applies gravity
    void processPhysics(float deltaTime);

    /*
    -Note- processPhysics and processCollisions functions can be called seperately if needed, but
    both must be called for engine to function properly. Call update function if seperation is not needed
    */

    //Detect and resolve collisions of physics bodies
    void processCollisions();

    //Applies force of gravity on a body
    void applyGravity(DynamicBody* body) const;

    //Return true if given physics bodies are colliding
    //Must be called in between processPhysics and processCollisions
    bool checkIfColliding(PhysicsBody* bodyA, PhysicsBody* bodyB);

    //Enables or disables physics
    //Parameter: true to enable, false to disable
    void setPhysicsProcess(bool processPhysics);

    //Enables or disables collision detection
    //Parameter: true to enable, false to disable
    void setCollisionProcess(bool processCollisions);

    //Sets the gravity scale of the world
    //Parameter: a non-negative scale factor
    void setGravityScale(float scaleValue);

    //Returns the vector of physics bodies in the world
    const std::vector<PhysicsBody*>& getBodies() const;

    //Returns a pointer to the world boundary
    WorldBoundary* getBoundary() const;
};

#endif