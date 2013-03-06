#include "propPosition.hpp"

propertyPosition::propertyPosition() {};
propertyPosition::~propertyPosition() {};

mat3& propertyPosition::rotation()
{
    return _rotation;
}

mat3& propertyPosition::scale()
{
    return _scale;
}

mat4& propertyPosition::position()
{
    return _position;
}
