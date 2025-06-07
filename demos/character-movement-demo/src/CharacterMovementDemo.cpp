#include "CharacterMovementDemo.hpp"

#include <iostream>

// Constants
const static int DEFAULT_WINDOW_WIDTH = 1200;
const static int DEFAULT_WINDOW_HEIGHT = 800;
const static float PIXELS_PER_METER = 50.0f; // Because the engine works in meters
float moveSpeed = 500.0f;

// Helper functions
// Converts a position in the engine in meters to a position in the window in pixels
sf::Vector2f getRenderPosition(const phys::Vector2& objectEnginePosition, const sf::Vector2u& windowSize)
{
    float windowWidth = static_cast<float>(windowSize.x);
    float windowHeight = static_cast<float>(windowSize.y);

    return {objectEnginePosition.x * PIXELS_PER_METER + windowWidth / 2,
        -objectEnginePosition.y * PIXELS_PER_METER + windowHeight / 2};
}

// Converts a position in the window in pixels to a position in the engine in meters
phys::Vector2 getEnginePosition(const sf::Vector2i& objectRenderPosition, const sf::Vector2u& windowSize)
{
    float windowWidth = static_cast<float>(windowSize.x);
    float windowHeight = static_cast<float>(windowSize.y);

    return {(objectRenderPosition.x - windowWidth / 2) / PIXELS_PER_METER,
        -(objectRenderPosition.y - windowHeight / 2) / PIXELS_PER_METER};
}

CharacterMovementDemo::CharacterMovementDemo() :
    m_world({DEFAULT_WINDOW_WIDTH / PIXELS_PER_METER, DEFAULT_WINDOW_HEIGHT / PIXELS_PER_METER}),
    m_window(sf::VideoMode({DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT}), "Physics Engine Character Movement Demo"),
    m_player(nullptr)
{
    m_world.setBoundaryType(phys::BoundaryType::Collidable);
    instantiateStaticBodies();
    instantiatePlayer();
}

CharacterMovementDemo::~CharacterMovementDemo() {}

void CharacterMovementDemo::run()
{
    sf::Clock fpsClock;

    // app runs while the window is opened and this loop runs while it is alive.
    while (m_window.isOpen())
    {
        float deltaTime = fpsClock.restart().asSeconds();

        // handle mouse events
        handleEvents(deltaTime);
        update(deltaTime);
        // render visuals
        render();
    }
}

void CharacterMovementDemo::instantiateStaticBodies()
{
    // Create a static rectangle
    // Define properties
    phys::Vector2 rectPosition = {-2, -5};
    phys::Vector2 dimensions = {4, 1};

    // Create the physics body and add to the world
    phys::StaticBody* rectangle = phys::createStaticRectangle(rectPosition, dimensions);
    m_world.addBody(rectangle);

    // Create a visual for the rectangle and map it to the body
    sf::RectangleShape* rectVisual =
        new sf::RectangleShape({dimensions.x * PIXELS_PER_METER, dimensions.y * PIXELS_PER_METER});
    rectVisual->setFillColor(sf::Color(255, 255, 255));
    rectVisual->setOrigin({dimensions.x / 2 * PIXELS_PER_METER, dimensions.y / 2 * PIXELS_PER_METER});
    rectVisual->setPosition(getRenderPosition(rectPosition, m_window.getSize()));
    m_bodyVisualMap[rectangle] = rectVisual;
}

void CharacterMovementDemo::handleEvents(float deltaTime)
{
    while (const std::optional event = m_window.pollEvent())
    {
        // Close window if close button is pressed
        if (event->is<sf::Event::Closed>())
        {
            m_window.close();
        }

        // Resize window event
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

        // Handle key press events
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            // Close the window if escape key is pressed
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
            {
                m_window.close();
            }

            // handle player movement events
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
            {
                m_player->move({-moveSpeed * deltaTime, 0});
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
            {
                m_player->move({moveSpeed * deltaTime, 0});
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Up)
            {
                m_player->move({0, moveSpeed * deltaTime});
            }
        }
    }
}

void CharacterMovementDemo::instantiatePlayer()
{
    phys::Vector2 rectPosition = {-2, -3};
    phys::Vector2 dimensions = {2, 4};

    // Create collider first
    // phys::RectCollider* collider = new phys::RectCollider(dimensions, phys::ColliderType::Solid);

    // Create body using the collider
    phys::DynamicBody* playerBody = phys::createDynamicRectangle(rectPosition, dimensions);

    // Add to the world
    m_world.addBody(playerBody);

    // Set player reference
    m_player = playerBody;

    // Create and assign visual
    sf::RectangleShape* visual =
        new sf::RectangleShape({dimensions.x * PIXELS_PER_METER, dimensions.y * PIXELS_PER_METER});
    visual->setFillColor(sf::Color::Red);
    visual->setOrigin({dimensions.x * PIXELS_PER_METER / 2, dimensions.y * PIXELS_PER_METER / 2});
    visual->setPosition(getRenderPosition(rectPosition, m_window.getSize()));

    m_playerVisual = visual;
    m_bodyVisualMap[playerBody] = visual;
}
void CharacterMovementDemo::update(float deltaTime)
{
    //Update the physics world
    m_world.update(deltaTime);

    for (auto it = m_bodyVisualMap.begin(); it != m_bodyVisualMap.end();)
    {
        // Reposition visual to match where their body is in the world
        it->second->setPosition(getRenderPosition(it->first->getPosition(), m_window.getSize()));
        ++it;
    }
}

void CharacterMovementDemo::render()
{
    // Clear the window to black
    m_window.clear();

    // Draw object visuals to the screen
    for (const auto& pair : m_bodyVisualMap)
    {
        m_window.draw(*pair.second);
    }

    m_window.display();
}
