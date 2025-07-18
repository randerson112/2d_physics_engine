//Class defenition for physics bodies that are affected by gravity and forces
//Affected by gravity
//Affected by collisions with other bodies
//Has a collider to collide with other bodies
//Responds to basic physics but cannot be controlled

#ifndef DYNAMIC_BODY_HPP
#define DYNAMIC_BODY_HPP

#include "physics/PhysicsBody.hpp"
#include "core/Vector2.hpp"

namespace phys
{
    class DynamicBody : public PhysicsBody
    {
      private:
        //Current velocity of the body
        Vector2 m_velocity;

        //rate of change of rotation
        float m_angularVelocity;

        //Accumulated forces on the body
        Vector2 m_force;

        //Current acceleration of the body
        Vector2 m_acceleration;

        //Restitution or bounciness of the body
        float m_restitution;

        //Mass of the body
        float m_mass;

        //Flag that determines if gravity affects the body
        bool m_affectedByGravity;

      public:
        //Constructor to set postion and collider
        DynamicBody(const Vector2& position, Collider* collider);

        //Applies an external force to the body
        void applyForce(const Vector2& force);

        //Update the physics of the body in the world
        void update(float deltaTime) override;

        //Calculates moment of rotational intertia based on shape
        float calculateRotationalInertia();
        float getInvRotationalInertia();

        //Getters for member variables
        const Vector2& getVelocity() const;
        float getAngularVelocity() const;
        const Vector2& getForce() const;
        const Vector2& getAcceleration() const;
        float getRestitution() const;
        float getMass() const;
        float getInvMass() const;
        bool isAffectedByGravity() const;

        //Setters for member variables
        void setVelocity(const Vector2& newVelocity);
        void setAngularVelocity(float newAngularVelocity);
        void setForce(const Vector2& newForce);
        void setAcceleration(const Vector2& newAcceleration);
        void setRestitution(float newRestitution);
        void setMass(float newMass);
        void setAffectedByGravity(bool affectedByGravity);
    };
}

#endif