/*
Physics Engine Notes

*Engine*
    keep track of all physics bodies
    update all the physics bodies and apply gravity to ones that are affected by gravity
    use sfml to render all bodies to the demo window
    Add a feature to pause physics and unpause physics

*Physics Bodies*
    StaticBody - body that is not affected by gravity but other objects can collide with it
    RigidBody - body that is affected by gravity and collisions but cannot be controlled
    CharacterBody - body that is affected by gravity and collsions and can be controlled by player

All physics boddies will derive from a base PhysicsBody class.
Create a Collider class that takes the shape as a paramter and makes a collider that checks for collisions
The physics bodies will have a collider attribute that checks for collsions for that body

*Classes*
    PhysicsBody:
        StaticBody
        RigidBody
        CharacterBody

    Collider
*/

#include <SFML/Graphics.hpp>
#include <iostream>

#include "physics_engine.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Pysics Engine Demo");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        window.display();

    }

    Vector position(45, 8700);
    Vector normal = position.normalized();

    std::cout << normal.x << " " << normal.y << std::endl;

    return 0;
}