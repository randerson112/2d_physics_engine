#ifndef DEMO_HPP
#define DEMO_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <random>
#include "Engine.hpp"
#include "Timer.hpp"

//Physics engine demo class defenition
//An interactable visual demonstration of the physics engine that allows you
//to spawn circles and rectangles as well as pause physics and collisions

class PhysicsEngineDemo
{
  public:
    //Constructor
    PhysicsEngineDemo();

    //Runs the main loop of the demo
    void run();

  private:
    //Window and rendering
    sf::RenderWindow m_window;
    sf::Font m_font;
    sf::Text m_fpsText;
    sf::Text m_objectCountText;

    //Physics world
    phys::PhysicsWorld m_world;

    //Timers for FPS display and object spawning cooldown
    Timer m_fpsDisplayTimer;
    Timer m_objectSpawnTimer;

    //Map to pair physics bodies with their visuals
    std::unordered_map<phys::PhysicsBody*, sf::Shape*> m_bodyVisualMap;

    //Random number generators
    std::random_device m_rd;
    std::mt19937 m_gen;
    std::uniform_int_distribution<int> m_rgbRange;
    std::uniform_real_distribution<float> m_radiusRange;
    std::uniform_real_distribution<float> m_rectSizeRange;

    //Private helper functions
    //Spawn initial static bodies into the world
    void instantiateStaticBodies();

    //Handle key press and window close events
    void handleEvents();

    //Handles mouse inputs to spawn objects
    void handleMouseInputs();

    //Updates the physics world and visuals
    void update(float deltaTime);

    //Render the visuals
    void render();

    //Spawn a dynamic circle body at mouse position
    void spawnDynamicCircle();

    //Spawn a dynamic rectangle body at mouse position
    void spawnDynamicRectangle();
};

#endif