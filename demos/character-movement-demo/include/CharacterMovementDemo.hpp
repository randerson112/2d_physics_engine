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
    phys::DynamicBody* m_player;
    sf::Shape* m_playerVisual;

    // Coin instance
    //TODO: make this a list or a map of coins
    phys::StaticBody* m_coin;
    sf::CircleShape m_coinVisual;

    //Jump button pressed this frame
    bool m_jumpPressed;

    // Map to pair the bodies of the engine with sfml bodies (used for rendering objects)
    std::unordered_map<phys::PhysicsBody*, sf::Shape*> m_bodyVisualMap;

    // Private functions used internally
    // Instantiates obstacles for character to move
    void instantiateStaticBodies();

    // Instantiates a coin for player to collect
    //TODO: make this instantiate a list of coins at random locations instead of only 1
    void instantiateCoin();

    // Handle key press and window close events
    void handleEvents(float deltaTime);

    // Render the visuals
    void render();

    // Instantiates Player
    void instantiatePlayer();

    // update fuction
    void update(float deltaTime);

    // Check if coin is touched
    //TODO: make this loop through all coins and check for collision with player
    void updateCoin();

    // handles player movement controls
    void updatePlayerMovement(float deltaTime);

    // check if the player is touching the ground (used for jumping logic)
    bool isPlayerTouchingGround() const;
};

#endif
