#ifndef CHARACTER_MOVEMENT_DEMO_HPP
#define CHARACTER_MOVEMENT_DEMO_HPP
#include "Engine.hpp"
#include <SFML/Graphics.hpp>

class CharacterMovementDemo
{
  public:
    // Constructor
    CharacterMovementDemo();

    // Destructor
    ~CharacterMovementDemo();

    // Starts the game and keeps up with it
    void run();

  private:
    // Window instance
    sf::RenderWindow m_window;

    // World instance
    phys::PhysicsWorld m_world;

    // Player instance
    phys::PhysicsBody* m_player;
    sf::Shape* m_playerVisual;

    // Map to pair the bodies of the engine with sfml bodies (used for rendering objects)
    std::unordered_map<phys::PhysicsBody*, sf::Shape*> m_bodyVisualMap;

    // Private functions used internally
    // Instantiates obstacles for character to move
    void instantiateStaticBodies();

    // Handle key press and window close events
    void handleEvents(float deltaTime);

    // Render the visuals
    void render();

    // Instantiates Player
    void instantiatePlayer();

    // update fuction
    void update(float deltaTime);
};

#endif
