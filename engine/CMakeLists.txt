#For building the engine as a static library for linking

cmake_minimum_required(VERSION 3.3)
project(PhysicsEngine)

#Set C++ version required
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Create a static library for the physics engine
add_library(PhysicsEngine STATIC)

#Include directories for public headers
target_include_directories(PhysicsEngine PUBLIC include)

#Get all source files for compiling
file(GLOB_RECURSE ENGINE_SOURCES src/*.cpp)
target_sources(PhysicsEngine PRIVATE ${ENGINE_SOURCES})