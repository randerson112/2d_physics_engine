//Class defenition for a collision resolver to resolve collisions between physics bodies

#include "physics/PhysicsBody.hpp"
#include <vector>

//Collision struct that stores pointers to two colliding bodies
struct Collision
{
    PhysicsBody* bodyA;
    PhysicsBody* bodyB;

    Collision(PhysicsBody* bodyA, PhysicsBody* bodyB)
        : bodyA(bodyA), bodyB(bodyB) {}
};

class CollisionSolver
{
private:
    //List of collision instances to resolve, passed from the engine
    std::vector<Collision*> collisions;

    //Resolve a collision with two rectangles
    void resolveRectRectCollision(PhysicsBody* rectA, PhysicsBody* rectB);

    //Resolve a collision with two circles
    void resolveCircleCircleCollision(PhysicsBody* circleA, PhysicsBody* circleB);

    //Resolve a collision with a rectangle and a circle
    void resolveRectCircleCollision(PhysicsBody* rect, PhysicsBody* circle);

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