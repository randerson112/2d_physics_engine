// Implementations for useful API functions

#include "Engine.hpp"

namespace phys
{
    // Creates a circle body with the specified position, radius, and body type.
    // The function dynamically allocates the body and returns a pointer to it.
    // Parameters:
    // - position: The initial position of the circle in the physics world.
    // - radius: The radius of the circle.
    // - bodyType: Specifies whether the body is dynamic or static.
    // Returns:
    // - A pointer to the created PhysicsBody. The physics world will handle the memory once body is added.
    PhysicsBody* createCircleObject(const Vector2& position, float radius, BodyType bodyType)
    {
        PhysicsBody* circle;
        if (bodyType == BodyType::DynamicBody)
        {
            circle = new DynamicBody(position, new CircleCollider(radius, ColliderType::Solid));
        }
        else if (bodyType == BodyType::StaticBody)
        {
            circle = new StaticBody(position, new CircleCollider(radius, ColliderType::Solid));
        }
        return circle;
    }

    // Creates a rectangle body with the specified position, dimensions, and body type.
    // The function dynamically allocates the body and returns a pointer to it.
    // Parameters:
    // - position: The initial position of the rectangle in the physics world.
    // - dimensions: The width and height of the rectangle.
    // - bodyType: Specifies whether the body is dynamic or static.
    // Returns:
    // - A pointer to the created PhysicsBody. The physics world will handle the memory once body is added.
    PhysicsBody* createRectangleObject(const Vector2& position, const Vector2& dimensions, BodyType bodyType)
    {
        PhysicsBody* rectangle;
        if (bodyType == BodyType::DynamicBody)
        {
            rectangle = new DynamicBody(position, new RectCollider(dimensions, ColliderType::Solid));
        }
        else if (bodyType == BodyType::StaticBody)
        {
            rectangle = new StaticBody(position, new RectCollider(dimensions, ColliderType::Solid));
        }
        return rectangle;
    }
}