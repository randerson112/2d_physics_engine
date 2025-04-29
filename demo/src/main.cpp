//SFML demo to provide a visual simulation of the engine
//Just renders all the physics body shapes while the engine does all the calculations

#include <SFML/Graphics.hpp>

#include "Engine.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode({1200, 800}), "Pysics Engine Demo");

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();
        window.display();

    }
}