#For building the demo project
#Builds the engine static library and links it to the demo automatically

cmake_minimum_required(VERSION 3.3)
project(engineDemo)

#Sets C++ version required
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Find SFML on system
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

#Builds the engine static library
add_subdirectory(engine)

#Create the demo executable
add_executable(${PROJECT_NAME} demo/main.cpp)

#Include the engine headers
target_include_directories(${PROJECT_NAME} PRIVATE engine/include)

#Link the physics engine library
target_link_libraries(${PROJECT_NAME} PRIVATE PhysicsEngine)

#Link the SFML libraries
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics SFML::Window SFML::System)