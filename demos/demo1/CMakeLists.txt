#For building the demo project
#Builds the engine static library and links it to the demo automatically

cmake_minimum_required(VERSION 3.10)
project(PhysicsEngineDemo1)

#Sets C++ version required
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Include FetchContent module
include(FetchContent)

#Fetch SFML
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
)
FetchContent_MakeAvailable(SFML)

#Create the demo executable
add_executable(${PROJECT_NAME})

#Link all source files to target
file(GLOB_RECURSE DEMO_SOURCES src/*.cpp)
target_sources(${PROJECT_NAME} PRIVATE ${DEMO_SOURCES})

#Set include directory
target_include_directories(${PROJECT_NAME} PRIVATE include)

#Link the physics engine library
target_link_libraries(${PROJECT_NAME} PRIVATE PhysicsEngineLibrary)

#Link the SFML libraries
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics SFML::Window SFML::System)