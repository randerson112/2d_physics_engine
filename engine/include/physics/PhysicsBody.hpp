//Base class defention for physics bodies
//All other physics bodies will inherit from this
//Handles basic physics properties such as position, velocity, and forces

#ifndef PHYSICS_BODY_HPP
#define PHYSICS_BODY_HPP

#include "core/Vector2.hpp"
#include "collisions/Collider.hpp"
#include <memory>

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
    Vector2 position;

    //Collider for detecting collisions
    Collider* collider;

    //Type of the body (static, dynamic...)
    BodyType type;

public:
    //Constructor
    PhysicsBody(const Vector2& initialPosition, Collider* colliderInstance, BodyType bodyType);

    //Destructor
    virtual ~PhysicsBody();

    //Updates the physics of the body in the world (implemented in derived classes)
    virtual void update(float deltaTime) = 0;

    //Moves a body by a relative amount
    void move(const Vector2& amountToMove);

    //Getters for member variables
    const Vector2& getPosition() const;
    Collider* getCollider() const;
    BodyType getType() const;

    //Setters for member variables
    void setPosition(const Vector2& newPosition);
    void setCollider(Collider* newCollider);
};

#endif