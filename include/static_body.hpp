#ifndef STATIC_BODY_HPP
#define STATIC_BODY_HPP

#include "physics_body.hpp"

class StaticBody : PhysicsBody
{
    //Not affected by gravity
    //Has a collider so other objects can collide with it
    //Uses include grounds, walls, boundaries, etc
};

#endif