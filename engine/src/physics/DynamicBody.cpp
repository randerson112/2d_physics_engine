//Class implementation for dynamic physics bodies

#include "physics/DynamicBody.hpp"
#include "collisions/CircleCollider.hpp"
#include "collisions/RectCollider.hpp"

namespace phys
{
    //Constructor to set members
    DynamicBody::DynamicBody(const Vector2& position, Collider* collider) :
        PhysicsBody(position, collider, BodyType::DynamicBody),
        m_mass(1.0f),
        m_restitution(0.6f),
        m_velocity({0, 0}),
        m_angularVelocity(0),
        m_acceleration({0, 0}),
        m_affectedByGravity(true)
    {
    }

    //Applies an external force to the body
    void DynamicBody::applyForce(const Vector2& forceToAdd)
    {
        m_force += forceToAdd;
    }

    //Update the physics of the body in the world
    void DynamicBody::update(float deltaTime)
    {
        m_acceleration = m_force / m_mass;
        m_velocity += m_acceleration * deltaTime; //Update velocity based on current acceleration

        m_position += m_velocity * deltaTime; //Update position based on current velocity
        m_collider->setPosition(m_position);

        m_rotation += m_angularVelocity * deltaTime; //Update rotation based on rotation velocity
        m_collider->setRotation(m_rotation);

        m_force = {0, 0};
    }

    //Calculates moment of rotational intertia based on shape
    float DynamicBody::calculateRotationalInertia()
    {
        ColliderShape shape = m_collider->getShape();

        //Circle intertia calculation
        if (shape == ColliderShape::Circle)
        {
            CircleCollider* collider = static_cast<CircleCollider*>(m_collider);
            float radius = collider->getRadius();

            return (1.0f / 2.0f) * m_mass * (radius * radius);
        }

        //Rectangle intertia calculation
        else if (shape == ColliderShape::Rectangle)
        {
            RectCollider* collider = static_cast<RectCollider*>(m_collider);
            float width = collider->getWidth();
            float height = collider->getHeight();

            return (1.0f / 12.0f) * m_mass * (width * width + height * height);
        }

        //Unknown shape
        else
        {
            return 0;
        }
    }

    float DynamicBody::getInvRotationalInertia()
    {
        float inertia = calculateRotationalInertia();
        if (inertia != 0)
        {
            return 1.0f / inertia;
        }
    }

    //Getters for member variables
    const Vector2& DynamicBody::getVelocity() const
    {
        return m_velocity;
    }

    float DynamicBody::getAngularVelocity() const
    {
        return m_angularVelocity;
    }

    const Vector2& DynamicBody::getForce() const
    {
        return m_force;
    }

    const Vector2& DynamicBody::getAcceleration() const
    {
        return m_acceleration;
    }

    float DynamicBody::getRestitution() const
    {
        return m_restitution;
    }

    float DynamicBody::getMass() const
    {
        return m_mass;
    }

    float DynamicBody::getInvMass() const
    {
        return 1 / m_mass;
    }

    bool DynamicBody::isAffectedByGravity() const
    {
        return m_affectedByGravity;
    }

    //Setters for member variables
    void DynamicBody::setVelocity(const Vector2& newVelocity)
    {
        m_velocity = newVelocity;
    }

    void DynamicBody::setAngularVelocity(float newAngularVelocity)
    {
        m_angularVelocity = newAngularVelocity;
    }

    void DynamicBody::setForce(const Vector2& newForce)
    {
        m_force = newForce;
    }

    void DynamicBody::setAcceleration(const Vector2& newAcceleration)
    {
        m_acceleration = newAcceleration;
    }

    void DynamicBody::setRestitution(float newRestitution)
    {
        if (newRestitution >= 0 && newRestitution <= 1)
            m_restitution = newRestitution;
    }

    void DynamicBody::setMass(float newMass)
    {
        if (newMass >= 0)
            m_mass = newMass;
    }

    void DynamicBody::setAffectedByGravity(bool affectedByGravity)
    {
        m_affectedByGravity = affectedByGravity;
    }
}