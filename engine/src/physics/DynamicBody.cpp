//Class implementation for dynamic physics bodies

#include "physics/DynamicBody.hpp"

namespace phys
{
//Constructor to set members
DynamicBody::DynamicBody(const Vector2& position, Collider* collider)
: PhysicsBody(position, collider, BodyType::DynamicBody),
m_mass(1.0f),
m_restitution(0.6f),
m_velocity({0, 0}),
m_rotationalVelocity(0),
m_acceleration({0, 0}),
m_affectedByGravity(true) {}

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

    m_rotation += m_rotationalVelocity * deltaTime; //Update rotation based on rotation velocity
    m_collider->setRotation(m_rotation);

    m_force = {0, 0};
}

//Getters for member variables
const Vector2& DynamicBody::getVelocity() const
{
    return m_velocity;
}

float DynamicBody::getRotationalVelocity() const
{
    return m_rotationalVelocity;
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

bool DynamicBody::isAffectedByGravity() const
{
    return m_affectedByGravity;
}

//Setters for member variables
void DynamicBody::setVelocity(const Vector2& newVelocity)
{
    m_velocity = newVelocity;
}

void DynamicBody::setRotationalVelocity(float newRotationalVelocity)
{
    m_rotationalVelocity = newRotationalVelocity;
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