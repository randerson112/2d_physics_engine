//Class defenition for physics worlds
//Physics worlds will keep track of all bodies within it
//Physics worlds call the update functions of all physics bodies every frame
//Physics worlds will handle world constants like gravity

#ifndef PHYSICS_WORLD_HPP
#define PHYSICS_WORLD_HPP

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
#include "physics/CollisionResolution.hpp"

#include <vector>

namespace phys
{
    class PhysicsWorld
    {
      private:
        //World boundaries for physics bodies
        WorldBoundary m_boundary;

        //Gravity force vector
        const Vector2 m_gravity = {0.0f, -9.81f};

        //Gravity scale of the world
        float m_gravityScale;

        //Boolean to control whether physics is processed
        bool m_processPhysics;

        //Boolean to control whether collisions are detected
        bool m_processCollisions;

        //List of all physics bodies in the world
        std::vector<PhysicsBody*> m_physicsBodies;

      public:
        //Constructor to set world boundary dimensions
        PhysicsWorld(const Vector2& boundaryDimensions);

        //Destructor
        ~PhysicsWorld();

        //Sets world boundary dimensions
        void setBoundaryDimensions(Vector2& newDimensions);

        //Sets the type of the world boundaries
        void setBoundaryType(BoundaryType newType);

        //Adds a physics body to the world
        void addBody(PhysicsBody* body);

        //Removes a physics body from the world
        void removeBody(PhysicsBody* body);

        //Updates physics bodies in the world, processes physics, and handles collisions
        //Parameter: time since last update call
        //Calls processPhysics and processCollisions functions
        void update(float deltaTime);

        //Updates physics bodies and applies gravity
        void updatePhysics(float deltaTime);

        /*
    -Note- processPhysics and processCollisions functions can be called seperately if needed, but
    both must be called for the world to function properly. Call update function if seperation is not needed
    */

        //Detect and resolve collisions of physics bodies
        void updateCollisions();

        //Applies force of gravity on a dynamic body
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
        void setGravityScale(float newScaleValue);

        //Returns the vector of physics bodies in the world
        const std::vector<PhysicsBody*>& getBodies() const;
    };
}

#endif