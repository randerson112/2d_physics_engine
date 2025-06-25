//Base class implementation for physics bodies

#include "physics/PhysicsBody.hpp"

namespace phys
{
    //Constructor to set position, collider, and body type
    PhysicsBody::PhysicsBody(const Vector2& position, Collider* collider, BodyType bodyType) :
        m_position(position), m_collider(collider), m_type(bodyType), m_rotation(0)
    {
        collider->setParent(this);                                   //Attach the collider to body
        collider->setPosition(m_position + m_collider->getOffset()); //Set the position of the collider to body position
    }

    //Destructor to delete collider memory
    PhysicsBody::~PhysicsBody()
    {
        delete m_collider;
    }

    //Moves a body by a relative amount
    void PhysicsBody::move(const Vector2& amountToMove)
    {
        setPosition({m_position.x + amountToMove.x, m_position.y + amountToMove.y});
    }

    //Rotates the body by given radians
    void PhysicsBody::rotate(const float radians)
    {
        m_rotation += radians;
        m_collider->rotate(radians); //Also rotate collider
    }

    //Getters for member variables
    const Vector2& PhysicsBody::getPosition() const
    {
        return m_position;
    }

    float PhysicsBody::getRotation() const
    {
        return m_rotation;
    }

    Collider* PhysicsBody::getCollider() const
    {
        return m_collider;
    }

    BodyType PhysicsBody::getType() const
    {
        return m_type;
    }

    //Setters for member variables
    void PhysicsBody::setPosition(const Vector2& newPosition)
    {
        m_position = newPosition;
        m_collider->setPosition(m_position); //Also move collider to new position
    }

    void PhysicsBody::setRotation(const float newRotation)
    {
        m_rotation = newRotation;
        m_collider->setRotation(m_rotation); //Also rotate collider
    }

    void PhysicsBody::setCollider(Collider* newCollider)
    {
        if (m_collider) //If there is an active collider already
        {
            delete m_collider; //Delete current collider
        }

        m_collider = newCollider;
    }
}