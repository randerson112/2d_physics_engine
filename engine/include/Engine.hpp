// This is the main include entry point for the physics engine library.
// It provides high-level API functions for creating and managing physics objects
// such as circles and rectangles, and abstracts away the internal implementation details.

#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "core/PhysicsWorld.hpp"
#include "core/Vector2.hpp"
#include "core/WorldBoundary.hpp"
#include "collisions/AABB.hpp"
#include "collisions/Collider.hpp"
#include "collisions/RectCollider.hpp"
#include "collisions/CircleCollider.hpp"
#include "collisions/CollisionDetection.hpp"
#include "collisions/Collision.hpp"
#include "physics/PhysicsBody.hpp"
#include "physics/StaticBody.hpp"
#include "physics/DynamicBody.hpp"
#include "physics/CollisionResolution.hpp"

namespace phys
{
    /**
     * @brief Creates a circle body to be added to a physics world.
     * 
     * This function dynamically allocates a circle body with the specified position,
     * radius, and body type. The caller is responsible for managing the memory of the
     * returned object unless it is added to a PhysicsWorld, which will handle its lifetime.
     * 
     * @param position The initial position of the circle in the physics world (default: {0, 0}).
     * @param radius The radius of the circle (default: 1.0f).
     * @param bodyType Specifies whether the body is dynamic or static (default: DynamicBody).
     * @return A pointer to the created PhysicsBody.
     */
    PhysicsBody* createCircleObject(const Vector2& position = {0, 0}, float radius = 1.0f, BodyType bodyType = BodyType::DynamicBody);

    /**
     * @brief Creates a rectangle body to be added to a physics world.
     * 
     * This function dynamically allocates a rectangle body with the specified position,
     * dimensions, and body type. The caller is responsible for managing the memory of the
     * returned object unless it is added to a PhysicsWorld, which will handle its lifetime.
     * 
     * @param position The initial position of the rectangle in the physics world (default: {0, 0}).
     * @param dimensions The width and height of the rectangle (default: {1.0f, 1.0f}).
     * @param bodyType Specifies whether the body is dynamic or static (default: DynamicBody).
     * @return A pointer to the created PhysicsBody.
     */
    PhysicsBody* createRectangleObject(const Vector2& position = {0, 0}, const Vector2& dimensions = {1.0f, 1.0f}, BodyType bodyType = BodyType::DynamicBody);
}

#endif