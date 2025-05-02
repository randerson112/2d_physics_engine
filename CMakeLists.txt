#For building the physics engine library and demo executable together

#Define project and minimum version of cmake required
cmake_minimum_required(VERSION 3.10)
project(PhysicsEngineProject)

#Allow engine to be built without a demo if specified
option(BUILD_DEMO "Build the physics engine demo" ON)

#Build engine static library
add_subdirectory(engine)

#Build the demo executable unless specified not to
if(BUILD_DEMO)
    add_subdirectory(demo)
endif()