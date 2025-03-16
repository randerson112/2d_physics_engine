//Class defenition for physics bodies that are affected by gravity and forces
//Affected by gravity
//Affected by collisions with other bodies
//Has a collider to collide with other bodies
//Responds to basic physics but cannot be controlled

#ifndef DYNAMIC_BODY_HPP
#define DYNAMIC_BODY_HPP

#include "physics/PhysicsBody.hpp"
#include "core/Vector2.hpp"

class DynamicBody : public PhysicsBody
{
private:
    //Current velocity of the body
    Vector2 velocity;

    //Accumulated forces on the body
    Vector2 force;

    //Current acceleration of the body
    Vector2 acceleration;

    //Restitution or bounciness of the body
    float restitution;

    //Mass of the body
    float mass;

    //Flag that determines if gravity affects the body
    bool affectedByGravity;

public:
    //Constructor to set postion and collider
    DynamicBody(const Vector2& initialPosition, Collider* colliderInstance);

    //Applies an external force to the body
    void applyForce(const Vector2& forceToAdd);

    //Update the physics of the body in the world
    void update(float deltaTime) override;

    //Getters for member variables
    const Vector2& getVelocity() const;
    const Vector2& getForce() const;
    const Vector2& getAcceleration() const;
    float getRestitution() const;
    float getMass() const;
    bool isAffectedByGravity() const;

    //Setters for member variables
    void setVelocity(const Vector2& newVelocity);
    void setForce(const Vector2& newForce);
    void setAcceleration(const Vector2& newAcceleration);
    void setRestitution(float newRestitution);
    void setMass(float newMass);
    void setAffectedByGravity(bool boolValue);
};

#endif