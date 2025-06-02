//Namespace for collision resolution functions

#include "physics/DynamicBody.hpp"
#include "physics/StaticBody.hpp"
#include "core/Vector2.hpp"
#include "collisions/Collision.hpp"
#include <vector>

namespace phys
{
    namespace CollisionResolution
    {
        //Resolves a collision by sorting it into respective function based on bodies
        void resolveCollision(const Collision& collision);

        //Resolve a collision between a dynamic body and a static body
        void resolveDynamicStaticCollision(
            DynamicBody* dynamicBody, StaticBody* staticBody, const Vector2& normal, float penDepth);

        //Resolve a collision between two dynamic bodies
        void resolveDynamicCollision(DynamicBody* bodyA, DynamicBody* bodyB, const Vector2& normal, float penDepth);
    };
}