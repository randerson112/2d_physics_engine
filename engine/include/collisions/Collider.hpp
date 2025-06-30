//Base class defenition for physics body colliders
//Collider objects will be members of physics bodies
//The collider will determine the shape of the physics body
//The collider will detect collisions between other colliders

#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include "physics/PhysicsBody.hpp"
#include "core/Vector2.hpp"
#include "collisions/AABB.hpp"
#include <vector>

namespace phys
{
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
        Vector2 m_position;

        //position relative to parent body, default no offset
        Vector2 m_offset;

        //rotation in degrees
        float m_rotation;

        //The parent of the collider, a physics body
        PhysicsBody* m_parent;

        //Shape of the collider
        ColliderShape m_shape;

        //Type of collider, solid or trigger
        ColliderType m_type;

        //Bounding box for broad collision detection
        AABB m_boundingBox;

        //Collision layers, what layers does this collider belong to
        std::vector<unsigned int> m_collisionLayers;

        //Collisions masks, what layers does this collider collide with
        std::vector<unsigned int> m_collisionMasks;

        //Update AABB mins and maxes
        virtual void updateAABB() = 0;

      public:
        //Constructor to set shape and collider type
        Collider(ColliderShape colliderShape, ColliderType ColliderType);

        virtual ~Collider();

        //Rotate collider by amount of radians
        void rotate(float radians);

        //Getters for member variables
        const Vector2& getPosition() const;
        float getRotation() const;
        const Vector2& getOffset() const;
        PhysicsBody* getParent() const;
        ColliderShape getShape() const;
        ColliderType getType() const;
        const AABB& getAABB() const;

        //Setters for member variables
        void setPosition(const Vector2& newPosition);
        void setRotation(float newRotation);
        void setOffset(const Vector2& newOffest);
        void setParent(PhysicsBody* newParent);
        void setType(ColliderType newType);

        //Collision layers and masks
        const std::vector<unsigned int>& getCollisionLayers() const;
        const std::vector<unsigned int>& getCollisionMasks() const;
        void setCollisionLayers(const std::vector<unsigned int>& newLayers);
        void setCollisionMasks(const std::vector<unsigned int>& newMasks);

        void addCollisionLayer(unsigned int newLayer);
        void addCollisionMask(unsigned int newMask);
        void removeCollisionLayer(unsigned int layer);
        void removeCollisionMask(unsigned int mask);

        bool isOnLayer(unsigned int layer);
        bool collidesWithLayer(unsigned int layer);
    };
}

#endif