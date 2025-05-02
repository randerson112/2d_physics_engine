# 2D Physics Engine

A basic 2D physics simulator using C++ and SFML. This project is an ambitious goal of mine that I want to challenge myself to complete. I want this engine to be able to simulate gravity, forces, and collisions between different physics bodies. The engine only keeps track of the mathematical aspects and manages all the physics bodies in space. **Rendering must be done outside of the engine.** I provide a visual demo using SFML to show what the engine does and how it can be used. This is a work in progress, and I have much more work to do.

---

## Features

### Physics Engine
- **Physics Bodies**:
  - Supports **dynamic bodies** (affected by gravity and forces).
  - Supports **static bodies** (fixed in space, used for walls, platforms, etc.).

- **Forces and Gravity**:
  - Apply external forces to dynamic bodies.
  - Simulate gravity with customizable gravity scale.

- **Collision Detection**:
  - Detect and resolve collisions between:
    - Circle vs. Circle
    - Rectangle vs. Rectangle
    - Circle vs. Rectangle
  - Axis-Aligned Bounding Box (AABB) for broad-phase collision detection.

- **Collision Resolution**:
  - Resolves collisions between dynamic and static bodies.
  - Resolves collisions between two dynamic bodies with restitution and impulse-based physics.

- **World Boundaries**:
  - Configurable world boundaries with two modes:
    - **Collidable**: Bodies bounce off the boundary.
    - **Delete**: Bodies are removed when they leave the boundary.

- **Physics World Management**:
  - Add and remove physics bodies dynamically.
  - Enable or disable physics processing and collision detection.
  - Customizable world gravity and boundary dimensions.

### Demo
- Visualizes a use of the physics engine using **SFML**.
- Allows spawning of dynamic circles and rectangles with random sizes and colors.
- Displays FPS and the number of active objects in the simulation.
- Supports resizing the window and dynamically adjusting world boundaries.

---

## How to Build

### Prerequisites
- **C++ Compiler**: A compiler that supports C++17 (e.g., GCC 10+, Clang 10+, or MSVC 2019+).
- **CMake**: Version 3.10 or higher.
- **SFML**: Version 3.0 or higher (for the demo).

### Building the Project

1. Clone the repository:
```bash
git clone https://github.com/randerson112/2d_physics_engine.git
cd 2d_physics_engine
```

2. Create a build directory:
- **On MacOS/Linux**
```bash
mkdir build
cd build
```

- **On Windows**
```bash
md build
cd build
```

3. Configure the project with CMake:
```bash
cmake ..
```

4. Build the project:
```bash
cmake --build .
```

---

## Running the Demo

1. Navigate to **build/demo**, there should now be an executable called **PhysicsEngineDemo**

2. Run the executable:
- **On MacOS/Linux**
```bash
./PhysicsEngineDemo
```

- **On Windows**
```bash
PhysicsEngineDemo.exe
```

### Demo Controls

The demo allows you to interact with the simulation using the following controls:

- **Left Mouse Button**: Spawns dynamic circle objects at the mouse position with a random radius and color.
- **Right Mouse Button**: Spawns dynamic rectangle objects at the mouse position with random dimensions and color.
- **P Key**: Hold down to pause physics, release to resume.
- **C Key**: Hold down to disable collisions, release to enable.
- **B Key**: Hold down to make window borders collidable, release to disable.
- **Window Resize**: You can resize the window to dynamically adjust the world boundaries to match the new window size.
- **Escape Key**: Closes the demo window.

---

## Example Engine Usage - Non-Visual

This Simple demo calculates how long it takes for a body dropped from 500 meters to hit the ground. It also states the objects velocity at impact.

```cpp
#include "Engine.hpp"
#include <iostream>

int main()
{
    phys::PhysicsWorld world;

    // Create a dynamic circle body
    phys::DynamicBody* body = phys::createDynamicCircle({0, 500});
    world.addBody(body);

    double timeElapsed = 0;
    double delta = 1.0 / 1000; // Small step amount for better accuracy

    // Simulate until the body reaches the ground
    while (body->getPosition().y >= 0)
    {
        world.update(delta);
        timeElapsed += delta;
    }

    std::cout << "Time to reach the ground: " << timeElapsed << " seconds" << std::endl;
    std::cout << "Object y velocity at impact: " << body->getVelocity().y << " meters per second" << std::endl;

    return 0;
}
```

**Refer to the demo source code for more example usage**

---

## Future Goals

- Add support for polygonal colliders.
- Implement rotational physics for bodies.
- Add support for trigger colliders and custom collision callbacks.
- Add collision layers and masks to seperate bodies.
- Improve performance with spatial partitioning (e.g., quadtrees).
- Expand the demo with more interactive features.