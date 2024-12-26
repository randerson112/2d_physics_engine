#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "vectors.hpp"
#include "colliders.hpp"
#include "physics_body.hpp"
#include "static_body.hpp"
#include "dynamic_body.hpp"
#include "controllable_body.hpp"

#include <memory>
#include <vector>

class PhysicsEngine
{
    //Store all physics bodies in the scene in a vector
    //Update all physics bodies in the scene in the update method
    //Call the update method in the window loop
    //Control gravity from here and be able to set the gravity scale
};

#endif