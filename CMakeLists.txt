#For building the physics engine library and demo executable together

#Define project and minimum version of cmake required
cmake_minimum_required(VERSION 3.10)
project(PhysicsEngineProject)

#Build engine static library
add_subdirectory(engine)

#Build the demo executable, which links to the engine library
add_subdirectory(demo)