#For building the demo project
#Builds the engine static library and links it to the demo automatically

cmake_minimum_required(VERSION 3.3)
project(PhysicsEngineDemo)

#Sets C++ version required
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Find SFML on system
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

#Create the demo executable
add_executable(${PROJECT_NAME})

#Link all source files to target
file(GLOB_RECURSE DEMO_SOURCES src/*.cpp)
target_sources(${PROJECT_NAME} PRIVATE ${DEMO_SOURCES})

#Link the physics engine library
target_link_libraries(${PROJECT_NAME} PRIVATE PhysicsEngineLibrary)

#Link the SFML libraries
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics SFML::Window SFML::System)