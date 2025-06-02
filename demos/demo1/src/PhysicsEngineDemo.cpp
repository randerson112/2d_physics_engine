#include "PhysicsEngineDemo.hpp"
#include <iostream>

//Implementation for physics engine demo class

//Constants
const static int DEFAULT_WINDOW_WIDTH = 1200;
const static int DEFAULT_WINDOW_HEIGHT = 800;
const static float PIXELS_PER_METER = 50.0f; //Because the engine works in meters

//Helper functions
//Converts a position in the engine in meters to a position in the window in pixels
sf::Vector2f getRenderPosition(const phys::Vector2& objectEnginePosition, const sf::Vector2u& windowSize)
{
    float windowWidth = static_cast<float>(windowSize.x);
    float windowHeight = static_cast<float>(windowSize.y);

    return {objectEnginePosition.x * PIXELS_PER_METER + windowWidth / 2,
        -objectEnginePosition.y * PIXELS_PER_METER + windowHeight / 2};
}

//Converts a position in the window in pixels to a position in the engine in meters
phys::Vector2 getEnginePosition(const sf::Vector2i& objectRenderPosition, const sf::Vector2u& windowSize)
{
    float windowWidth = static_cast<float>(windowSize.x);
    float windowHeight = static_cast<float>(windowSize.y);

    return {(objectRenderPosition.x - windowWidth / 2) / PIXELS_PER_METER,
        -(objectRenderPosition.y - windowHeight / 2) / PIXELS_PER_METER};
}

//Constructor
PhysicsEngineDemo::PhysicsEngineDemo() :
    m_window(sf::VideoMode({DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT}), "Physics Engine Demo"),
    m_font("../../../demos/demo1/assets/arial.ttf"),
    m_fpsText(m_font),
    m_objectCountText(m_font),
    m_world({DEFAULT_WINDOW_WIDTH / PIXELS_PER_METER, DEFAULT_WINDOW_HEIGHT / PIXELS_PER_METER}),
    m_fpsDisplayTimer(0.5f),
    m_objectSpawnTimer(0.01f),
    m_gen(m_rd()),
    m_rgbRange(1, 255),
    m_radiusRange(0.1f, 0.5f),
    m_rectSizeRange(0.1f, 1.0f)
{
    //Setup FPS text
    m_fpsText.setString("fps: ");
    m_fpsText.setCharacterSize(30);
    m_fpsText.setOutlineThickness(1.0f);
    m_fpsText.setOutlineColor(sf::Color(39, 125, 88));

    //Setup object count text
    m_objectCountText.setString("objects: ");
    m_objectCountText.setCharacterSize(30);
    m_objectCountText.setPosition({0, 30});
    m_objectCountText.setOutlineThickness(1.0f);
    m_objectCountText.setOutlineColor(sf::Color(207, 111, 37));

    //Instantiate initial static bodies
    instantiateStaticBodies();
}

//Runs the main loop
void PhysicsEngineDemo::run()
{
    sf::Clock fpsClock;

    while (m_window.isOpen())
    {
        float deltaTime = fpsClock.restart().asSeconds();

        handleEvents();
        handleMouseInputs();
        update(deltaTime);
        render();
    }
}

//Instantiates initial static bodies
void PhysicsEngineDemo::instantiateStaticBodies()
{
    //Create a static rectangle
    //Define properties
    phys::Vector2 rectPosition = {-2, -2.5};
    phys::Vector2 dimensions = {4, 1};

    //Create the physics body and add to the world
    phys::StaticBody* rectangle = phys::createStaticRectangle(rectPosition, dimensions);
    m_world.addBody(rectangle);

    //Create a visual for the rectangle and map it to the body
    sf::RectangleShape* rectVisual =
        new sf::RectangleShape({dimensions.x * PIXELS_PER_METER, dimensions.y * PIXELS_PER_METER});
    rectVisual->setFillColor(sf::Color(m_rgbRange(m_gen), m_rgbRange(m_gen), m_rgbRange(m_gen)));
    rectVisual->setOrigin({dimensions.x / 2 * PIXELS_PER_METER, dimensions.y / 2 * PIXELS_PER_METER});
    rectVisual->setPosition(getRenderPosition(rectPosition, m_window.getSize()));
    m_bodyVisualMap[rectangle] = rectVisual;

    //Create a static circle
    //Define properties
    phys::Vector2 circlePosition = {2, -2.5};
    float radius = 1;

    //Create a physics body and add it to the world
    phys::StaticBody* circle = phys::createStaticCircle(circlePosition, radius);
    m_world.addBody(circle);

    //Create a visual for the circle and map it to the body
    sf::CircleShape* circleVisual = new sf::CircleShape(radius * PIXELS_PER_METER);
    circleVisual->setFillColor(sf::Color(m_rgbRange(m_gen), m_rgbRange(m_gen), m_rgbRange(m_gen)));
    circleVisual->setOrigin({radius * PIXELS_PER_METER, radius * PIXELS_PER_METER});
    circleVisual->setPosition(getRenderPosition(circlePosition, m_window.getSize()));
    m_bodyVisualMap[circle] = circleVisual;
}

//Handles events like window resizing and key presses
void PhysicsEngineDemo::handleEvents()
{
    while (const std::optional event = m_window.pollEvent())
    {
        //Close window if close button is pressed
        if (event->is<sf::Event::Closed>())
        {
            m_window.close();
        }

        //Resize window event
        if (event->is<sf::Event::Resized>())
        {
            //Update view size
            sf::View view(sf::FloatRect({0, 0}, sf::Vector2f(m_window.getSize())));
            m_window.setView(view);

            //Calculate new window dimensions
            float windowWidth = static_cast<float>(m_window.getSize().x);
            float windowHeight = static_cast<float>(m_window.getSize().y);

            //Resize world boundaries
            phys::Vector2 newDimensions = {windowWidth / PIXELS_PER_METER, windowHeight / PIXELS_PER_METER};
            m_world.setBoundaryDimensions(newDimensions);
        }

        //Key pressed events
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            //Close the window if escape key is pressed
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
            {
                m_window.close();
            }

            //If the P key is held down, pause physics
            if (keyPressed->scancode == sf::Keyboard::Scancode::P)
            {
                m_world.setPhysicsProcess(false);
            }

            //If the C key is held down, disable collision detection
            if (keyPressed->scancode == sf::Keyboard::Scancode::C)
            {
                m_world.setCollisionProcess(false);
            }

            if (keyPressed->scancode == sf::Keyboard::Scancode::B)
            {
                m_world.setBoundaryType(phys::BoundaryType::Collidable);
            }
        }

        //Key released events
        if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
        {
            //If the P key is released, resume physics
            if (keyReleased->scancode == sf::Keyboard::Scancode::P)
            {
                m_world.setPhysicsProcess(true);
            }

            //If the C key is released, enable collision detection
            if (keyReleased->scancode == sf::Keyboard::Scancode::C)
            {
                m_world.setCollisionProcess(true);
            }

            //If the B key is released, set boundary to delete
            if (keyReleased->scancode == sf::Keyboard::Scancode::B)
            {
                m_world.setBoundaryType(phys::BoundaryType::Delete);
            }
        }
    }
}

//Handles mouse button inputs
void PhysicsEngineDemo::handleMouseInputs()
{
    //If the left mouse button is held down
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && m_objectSpawnTimer.timeout())
    {
        spawnDynamicCircle();
    }

    //If the right mouse button is held down
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && m_objectSpawnTimer.timeout())
    {
        spawnDynamicRectangle();
    }
}

//Updates the physics world, texts, and visuals
void PhysicsEngineDemo::update(float deltaTime)
{
    //Update the physics world
    m_world.update(deltaTime);

    //Step timers
    m_fpsDisplayTimer.step(deltaTime);
    m_objectSpawnTimer.step(deltaTime);

    //Update fps text
    if (m_fpsDisplayTimer.timeout())
    {
        m_fpsText.setString("fps: " + std::to_string(static_cast<int>(1.f / deltaTime + 0.5f)));
        m_fpsDisplayTimer.reset();
    }

    //Update object count text
    m_objectCountText.setString("objects: " + std::to_string(m_world.getBodies().size()));

    //If the engine has deleted bodies, delete the respective visuals
    std::vector<phys::PhysicsBody*> existingBodies = m_world.getBodies();
    for (auto it = m_bodyVisualMap.begin(); it != m_bodyVisualMap.end();)
    {
        if (std::find(existingBodies.begin(), existingBodies.end(), it->first) == existingBodies.end())
        {
            //Delete the body-visual pair if the body is no longer in the engine bodies
            delete it->second;
            it = m_bodyVisualMap.erase(it);
        }
        else
        {
            //Reposition visual to match where their body is in the world
            it->second->setPosition(getRenderPosition(it->first->getPosition(), m_window.getSize()));
            ++it;
        }
    }
}

// Renders visuals to the window
void PhysicsEngineDemo::render()
{
    //Clear the window to black
    m_window.clear();

    //Draw object visuals to the screen
    for (const auto& pair : m_bodyVisualMap)
    {
        m_window.draw(*pair.second);
    }

    //Draw text
    m_window.draw(m_fpsText);
    m_window.draw(m_objectCountText);

    //Display all images to window
    m_window.display();
}

//Spawns a dynamic circle object at the mouse position
void PhysicsEngineDemo::spawnDynamicCircle()
{
    //Get the mouse position and convert it to position in meters for the engine
    sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);
    phys::Vector2 engineMousePosition = getEnginePosition(mousePosition, m_window.getSize());

    //Create the dynamic body in the engine
    float randRadius = m_radiusRange(m_gen);
    phys::DynamicBody* newCircle = phys::createDynamicCircle(engineMousePosition, randRadius);
    m_world.addBody(newCircle);

    //Create a visual for the dynamic body
    sf::CircleShape* bodyVisual = new sf::CircleShape(randRadius * PIXELS_PER_METER);
    bodyVisual->setFillColor(sf::Color(m_rgbRange(m_gen), m_rgbRange(m_gen), m_rgbRange(m_gen)));
    bodyVisual->setOrigin({randRadius * PIXELS_PER_METER, randRadius * PIXELS_PER_METER});
    bodyVisual->setPosition(getRenderPosition(newCircle->getPosition(), m_window.getSize()));

    //Map body to visual
    m_bodyVisualMap[newCircle] = bodyVisual;

    //Reset spawn cooldown timer
    m_objectSpawnTimer.reset();
}

//Spawns a dynamic rectangle object at the mouse position
void PhysicsEngineDemo::spawnDynamicRectangle()
{
    //Get the mouse position and convert it to position in meters for the world
    sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);
    phys::Vector2 engineMousePosition = getEnginePosition(mousePosition, m_window.getSize());

    //Create the dynamic rect body in the world
    float randSize = m_rectSizeRange(m_gen);
    phys::Vector2 randDimensions = {randSize, randSize};
    float randWidth = randDimensions.x;
    float randHeight = randDimensions.y;
    phys::DynamicBody* newRect = phys::createDynamicRectangle(engineMousePosition, randDimensions);
    m_world.addBody(newRect);

    //Create a rectangle visual for the dynamic body
    sf::RectangleShape* rectVisual =
        new sf::RectangleShape({randWidth * PIXELS_PER_METER, randHeight * PIXELS_PER_METER});
    rectVisual->setFillColor(sf::Color(m_rgbRange(m_gen), m_rgbRange(m_gen), m_rgbRange(m_gen)));
    rectVisual->setOrigin({randWidth / 2 * PIXELS_PER_METER, randHeight / 2 * PIXELS_PER_METER});
    rectVisual->setPosition(getRenderPosition(newRect->getPosition(), m_window.getSize()));

    //Map the body to its visual
    m_bodyVisualMap[newRect] = rectVisual;

    //Reset spawn cooldown timer
    m_objectSpawnTimer.reset();
}