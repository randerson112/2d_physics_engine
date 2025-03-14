//Class defenition for a collision resolver to resolve collisions between physics bodies

#include "physics/DynamicBody.hpp"
#include "physics/StaticBody.hpp"
#include "core/Vector2.hpp"
#include "collisions/Collision.hpp"
#include <vector>

class CollisionSolver
{
private:
    //List of collision instances to resolve, passed from the engine
    std::vector<Collision*> collisions;

    //Resolve a collision between a dynamic body and a static body
    void resolveDynamicStaticCollision(DynamicBody* dynamicBody, StaticBody* staticBody, const Vector2& normal, float penDepth);

    //Resolve a collision between two dynamic bodies
    void resolveDynamicCollision(DynamicBody* bodyA, DynamicBody* bodyB, const Vector2& normal, float penDepth);

public:
    //Constructor needs no paramters
    CollisionSolver();

    //Destructor to delete collision objects
    ~CollisionSolver();

    //Loops through collisions vector and sort collisions to respective solvers
    void resolveCollisions();

    //Adds a collision instance to the vector, called from the engine
    void addCollision(Collision* newCollision);
};