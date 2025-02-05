//Base class defenition for physics body colliders
//Collider objects will be attributes of physics bodies
//The collider will determine the shape of the physics body
//The collider will detect collisions between other colliders

#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include "PhysicsBody.hpp"
#include "Vector2.hpp"

enum class ColliderShape
{
    Rectangle,
    Circle
};

class Collider
{
protected:
    //Position of collider in world
    Vector2 position;

    //position relative to parent body, default no offset
    Vector2 offset;

    //The parent of the collider, a physics body
    PhysicsBody* parent;

    //Shape of the collider
    ColliderShape shape;

public:
    Collider(Vector2 initialPosition = {0, 0}, Vector2 offset = {0, 0}, ColliderShape shapeType);

    virtual ~Collider() = default;

    //Checks for collision with another collider
    virtual PhysicsBody* checkCollision(Collider& otherCollider) = 0;

    //Getters for member variables
    Vector2 getPosition();
    Vector2 getOffset();
    PhysicsBody* getParent();
    ColliderShape getShape();

    //Setters for member variables
    void setPosition(Vector2 newPosition);
    void setOffset(Vector2 newOffest);
    void setParent(PhysicsBody* newParent);

    //Maybe a method to change the shape of the collider in the future
};

#endif