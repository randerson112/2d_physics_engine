//Base class defention for physics bodies
//All other physics bodies will inherit from this
//Handles basic physics properties such as position, velocity, and forces

#ifndef PHYSICS_BODY_HPP
#define PHYSICS_BODY_HPP

#include "core/Vector2.hpp"
#include "collisions/Collider.hpp"
#include <memory>

namespace phys
{
    enum class BodyType
    {
        StaticBody,
        DynamicBody,
        ControllableBody
    };

    class Collider;

    class PhysicsBody
    {
      protected:
        //Position of body in the world
        Vector2 m_position;

        //rotation in degrees
        float m_rotation;

        //Collider for detecting collisions
        Collider* m_collider;

        //Type of the body (static, dynamic...)
        BodyType m_type;

      public:
        //Constructor
        PhysicsBody(const Vector2& position, Collider* collider, BodyType bodyType);

        //Destructor
        virtual ~PhysicsBody();

        //Updates the physics of the body in the world (implemented in derived classes)
        virtual void update(float deltaTime) = 0;

        //Moves a body by a relative amount
        void move(const Vector2& amountToMove);

        //Rotates the body by given radians
        void rotate(const float radians);

        //Getters for member variables
        const Vector2& getPosition() const;
        float getRotation() const;
        Collider* getCollider() const;
        BodyType getType() const;

        //Setters for member variables
        void setPosition(const Vector2& newPosition);
        void setRotation(float newRotation);
        void setCollider(Collider* newCollider);
    };
}

#endif