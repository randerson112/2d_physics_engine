//Base class defenition for physics body colliders
//Collider objects will be members of physics bodies
//The collider will determine the shape of the physics body
//The collider will detect collisions between other colliders

#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include "physics/PhysicsBody.hpp"
#include "core/Vector2.hpp"
#include "collisions/AABB.hpp"

enum class ColliderShape
{
    Rectangle,
    Circle
};

enum class ColliderType
{
    Solid,
    Trigger
};

class PhysicsBody;

class Collider
{
protected:
    //position of the collider in the world
    Vector2 position;

    //position relative to parent body, default no offset
    Vector2 offset;

    //The parent of the collider, a physics body
    PhysicsBody* parent;

    //Shape of the collider
    ColliderShape shape;

    //Type of collider, solid or trigger
    ColliderType type;

    //Bounding box for broad collision detection
    AABB boundingBox;

    //Update AABB mins and maxes
    virtual void updateAABB() = 0;

public:
    //Constructor to set shape and collider type
    Collider(ColliderShape shapeType, ColliderType type);

    virtual ~Collider();

    //Getters for member variables
    const Vector2& getPosition() const;
    const Vector2& getOffset() const;
    PhysicsBody* getParent() const;
    ColliderShape getShape() const;
    ColliderType getType() const;
    const AABB& getAABB() const;

    //Setters for member variables
    void setPosition(const Vector2& newPosition);
    void setOffset(const Vector2& newOffest);
    void setParent(PhysicsBody* newParent);
    void setType(ColliderType newType);

    //Maybe a method to change the shape of the collider in the future
};

#endif