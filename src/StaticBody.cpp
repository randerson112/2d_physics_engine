//Class implementation for static physics bodies

#include "StaticBody.hpp"

//Sets position and collider
StaticBody::StaticBody(Vector2 initialPosition, Collider* colliderInstance)
    : PhysicsBody(initialPosition, colliderInstance) {}

//Static body does not need update method since it is not affected by physics