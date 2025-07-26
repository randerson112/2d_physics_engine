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
    m_player(nullptr),
    m_font("demos/character-movement-demo/assets/arial.ttf"),
    m_coinCounter(m_font),
    m_coins(),
    m_collectedCoinCount(0)
{
    m_world.setBoundaryType(phys::BoundaryType::Collidable);
    m_world.setRotationalPhysics(false);

    m_coinCounter.setString("collected coins: ");
    m_coinCounter.setCharacterSize(30);
    m_coinCounter.setPosition({10, 30});
    m_coinCounter.setOutlineThickness(1.0f);
    m_coinCounter.setOutlineColor(sf::Color(255, 255, 255));

    instantiateStaticBodies();
    instantiateCoinsInitially();
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
        // handle player events
        updatePlayerMovement(deltaTime);

        //If coin is there, check for collision
        if (!m_coins.empty())
            updateCoin();

        update(deltaTime);
        // render visuals
        render();
    }
}

void CharacterMovementDemo::instantiateStaticBodies()
{
    std::vector<std::pair<phys::Vector2, phys::Vector2>> staticPlatforms = {{{-2, -5}, {4, 1}}, // position, dimensions
        {{3, -2}, {2, 1}},
        {{-4, 0}, {3, 1}},
        {{0, 3}, {5, 1}}};

    for (const auto& [pos, size] : staticPlatforms)
    {
        phys::StaticBody* rectangle = phys::createStaticRectangle(pos, size);
        m_world.addBody(rectangle);

        sf::RectangleShape* rectVisual =
            new sf::RectangleShape(sf::Vector2f(size.x * PIXELS_PER_METER, size.y * PIXELS_PER_METER));
        rectVisual->setFillColor(sf::Color::White);
        rectVisual->setOrigin(sf::Vector2f(size.x * PIXELS_PER_METER / 2, size.y * PIXELS_PER_METER / 2));
        rectVisual->setPosition(getRenderPosition(pos, m_window.getSize()));

        m_bodyVisualMap[rectangle] = rectVisual;
    }
}

void CharacterMovementDemo::createCoin()
{
    m_coins.push_back(createRandomCoin());
}

Coin CharacterMovementDemo::createRandomCoin()
{
    sf::Vector2u windowSize = m_window.getSize();
    const float radiusPixels = 0.5f * PIXELS_PER_METER;

    const int minX = static_cast<int>(radiusPixels);
    const int maxX = static_cast<int>(windowSize.x - radiusPixels);
    const int minY = static_cast<int>(radiusPixels);
    const int maxY = static_cast<int>(windowSize.y - radiusPixels);

    const int randX = rand() % (maxX - minX) + minX;
    const int randY = rand() % (maxY - minY) + minY;

    sf::Vector2i randomPixelPosition(randX, randY);
    phys::Vector2 position = getEnginePosition(randomPixelPosition, windowSize);

    phys::StaticBody* body = phys::createStaticCircle(position, 0.5f);
    body->getCollider()->setType(phys::ColliderType::Trigger);
    m_world.addBody(body);

    sf::CircleShape visual(radiusPixels);
    visual.setFillColor(sf::Color(255, 215, 0));
    visual.setOrigin(sf::Vector2f(radiusPixels, radiusPixels));
    visual.setPosition(getRenderPosition(position, windowSize));

    return {body, visual};
}

void CharacterMovementDemo::instantiateCoinsInitially()
{
    m_coins.clear();

    const int initialCoinCount = 5;
    for (int i = 0; i < initialCoinCount; ++i)
    {
        m_coins.push_back(createRandomCoin());
    }
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

        // close window on escape key press
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                m_window.close();

            if (keyPressed->scancode == sf::Keyboard::Scancode::Up && isPlayerTouchingGround())
                m_jumpPressed = true;
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
    }
}

void CharacterMovementDemo::instantiatePlayer()
{
    phys::Vector2 rectPosition = {-2, -3};
    phys::Vector2 dimensions = {1, 2};

    // Create body using the collider
    phys::DynamicBody* playerBody = phys::createDynamicRectangle(rectPosition, dimensions);
    playerBody->setRestitution(0.0f); //Removes bounciness

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

    m_jumpPressed = false;
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

void CharacterMovementDemo::updateCoin()
{
    int collectedCountThisFrame = 0;

    m_coins.erase(std::remove_if(m_coins.begin(),
                      m_coins.end(),
                      [this, &collectedCountThisFrame](Coin& coin)
                      {
                          if (coin.body && m_world.checkIfColliding(m_player, coin.body))
                          {
                              m_world.removeBody(coin.body);
                              ++collectedCountThisFrame;
                              ++m_collectedCoinCount;

                              return true;
                          }
                          return false;
                      }),
        m_coins.end());

    m_coinCounter.setString("collected coins: " + std::to_string(m_collectedCoinCount));
    // Create new coins
    for (int i = 0; i < collectedCountThisFrame; ++i)
    {
        createCoin();
    }
}

void CharacterMovementDemo::updatePlayerMovement(float deltaTime)
{
    const float moveSpeed = 7.0f;     // m/s
    const float jumpStrength = 10.0f; // m/s

    phys::Vector2 velocity = m_player->getVelocity();

    // Horizontal movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        velocity.x = -moveSpeed;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        velocity.x = moveSpeed;
    else
        velocity.x = 0;

    // Jumping
    if (m_jumpPressed)
    {
        velocity.y = jumpStrength;
        m_jumpPressed = false;
    }

    m_player->setVelocity(velocity);
}

bool CharacterMovementDemo::isPlayerTouchingGround() const
{
    return m_world.checkIfOnFloor(m_player) || m_player->getVelocity().y == 0;
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

    if (!m_coins.empty())
    {
        for (auto& m_coin : m_coins)
        {
            m_window.draw(m_coin.visual);
        }
    }

    m_window.draw(m_coinCounter);
    m_window.display();
}
