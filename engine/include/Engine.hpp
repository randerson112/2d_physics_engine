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
     * @brief Creates a static circle body to be added to a physics world.
     * 
     * This function dynamically allocates a static circle body with the specified position and
     * radius. The caller is responsible for managing the memory of the
     * returned object unless it is added to a PhysicsWorld, which will handle its lifetime.
     * 
     * @param position The initial position of the circle in the physics world in meters (default: {0, 0}).
     * @param radius The radius of the circle in meters (default: 1.0f).
     * @return A pointer to the created StaticBody
     */
    StaticBody* createStaticCircle(const Vector2& position = {0, 0}, float radius = 1.0f);

    /**
     * @brief Creates a static rectangle body to be added to a physics world.
     * 
     * This function dynamically allocates a static rectangle body with the specified position and
     * dimensions. The caller is responsible for managing the memory of the
     * returned object unless it is added to a PhysicsWorld, which will handle its lifetime.
     * 
     * @param position The initial position of the rectangle in the physics world in meters (default: {0, 0}).
     * @param dimensions The width and height of the rectangle in meters (default: {1.0f, 1.0f}).
     * @return A pointer to the created StaticBody.
     */
    StaticBody* createStaticRectangle(const Vector2& position = {0, 0}, const Vector2& dimensions = {1.0f, 1.0f});

    /**
     * @brief Creates a dynamic circle body to be added to a physics world.
     * 
     * This function dynamically allocates a dynamic circle body with the specified position and
     * radius. The caller is responsible for managing the memory of the
     * returned object unless it is added to a PhysicsWorld, which will handle its lifetime.
     * 
     * @param position The initial position of the circle in the physics world in meters (default: {0, 0}).
     * @param radius The radius of the circle in meters (default: 1.0f).
     * @return A pointer to the created DynamicBody
     */
    DynamicBody* createDynamicCircle(const Vector2& position = {0, 0}, float radius = 1.0f);

    /**
     * @brief Creates a dynamic rectangle body to be added to a physics world.
     * 
     * This function dynamically allocates a dynamic rectangle body with the specified position and
     * dimensions. The caller is responsible for managing the memory of the
     * returned object unless it is added to a PhysicsWorld, which will handle its lifetime.
     * 
     * @param position The initial position of the rectangle in the physics world in meters (default: {0, 0}).
     * @param dimensions The width and height of the rectangle in meters (default: {1.0f, 1.0f}).
     * @return A pointer to the created DynamicBody.
     */
    DynamicBody* createDynamicRectangle(const Vector2& position = {0, 0}, const Vector2& dimensions = {1.0f, 1.0f});
}

#endif