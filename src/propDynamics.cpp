#include "propDynamics.hpp"

propertyDynamics::propertyDynamics() {};
propertyDynamics::~propertyDynamics() {};

void propertyDynamics::updatePosition()
{
    _velocity += _acceleration;
    _angularVelocity += _angularAcceleration;
}

vec3& propertyDynamics::acceleration()
{
    return &_acceleration;
}

vec3& propertyDynamics::angularAcceleration()
{
    return &_angularAcceleration;
}
