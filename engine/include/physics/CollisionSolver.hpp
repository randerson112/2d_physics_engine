//Class defenition for a collision resolver to resolve collisions between physics bodies

#include "physics/PhysicsBody.hpp"
#include "collisions/Collision.hpp"
#include <vector>

class CollisionSolver
{
private:
    //List of collision instances to resolve, passed from the engine
    std::vector<Collision*> collisions;

    //Resolve a collision with two rectangles
    void resolveRectRectCollision(PhysicsBody* rectA, PhysicsBody* rectB, const Vector2& normal, float penDepth);

    //Resolve a collision with two circles
    void resolveCircleCircleCollision(PhysicsBody* circleA, PhysicsBody* circleB, const Vector2& normal, float penDepth);

    //Resolve a collision with a rectangle and a circle
    void resolveRectCircleCollision(PhysicsBody* rect, PhysicsBody* circle, const Vector2& normal, float penDepth);

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