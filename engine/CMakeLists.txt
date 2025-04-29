#For building the engine as a static library for linking

cmake_minimum_required(VERSION 3.3)
project(PhysicsEngineLibrary)

#Set C++ version required
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Create a static library for the physics engine
add_library(${PROJECT_NAME} STATIC)

#Include directories for public headers
target_include_directories(${PROJECT_NAME} PUBLIC include)

#Link source files to target
file(GLOB_RECURSE ENGINE_SOURCES src/*.cpp)
target_sources(${PROJECT_NAME} PRIVATE ${ENGINE_SOURCES})