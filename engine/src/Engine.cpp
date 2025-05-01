// Implementations for useful API functions

#include "Engine.hpp"

namespace phys
{
    StaticBody* createStaticCircle(const Vector2& position, float radius)
    {
        return new StaticBody(position, new CircleCollider(radius, ColliderType::Solid));
    }

    StaticBody* createStaticRectangle(const Vector2& position, const Vector2& dimensions)
    {
        return new StaticBody(position, new RectCollider(dimensions, ColliderType::Solid));
    }

    DynamicBody* createDynamicCircle(const Vector2& position, float radius)
    {
        return new DynamicBody(position, new CircleCollider(radius, ColliderType::Solid));
    }

    DynamicBody* createDynamicRectangle(const Vector2& position, const Vector2& dimensions)
    {
        return new DynamicBody(position, new RectCollider(dimensions, ColliderType::Solid));
    }
}