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
        //Resolves a collision with no rotations by sorting it into respective function based on bodies
        void resolveBasicCollision(const Collision& collision);
        
        //Resolves a collision with rotation by sorting it into respective function based on bodies
        void resolveAdvancedCollision(const Collision& collision);

        //Resolve a collision between a dynamic body and a static body, no rotations
        void resolveBasicDynamicStaticCollision(
            DynamicBody* dynamicBody, StaticBody* staticBody, const Vector2& normal, float penDepth);

        //Resolve a collision between two dynamic bodies, no roations
        void resolveBasicDynamicCollision(
            DynamicBody* bodyA, DynamicBody* bodyB, const Vector2& normal, float penDepth);

        //Resolve a collision between a dynamic body and a static body, with rotations
        void resolveAdvancedDynamicStaticCollision(DynamicBody* dynamicBody,
            StaticBody* staticBody,
            const Vector2& normal,
            float penDepth,
            const std::vector<Vector2>& contactPoints,
            int contactCount);

        //Resolve a collision between two dynamic bodies, with rotation
        void resolveAdvancedDynamicCollision(DynamicBody* bodyA,
            DynamicBody* bodyB,
            const Vector2& normal,
            float penDepth,
            const std::vector<Vector2>& contactPoints,
            int contactCount);
    };
}