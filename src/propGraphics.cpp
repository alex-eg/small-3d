#include "propGraphics.hpp"

propertyGraphics::propertyGraphics()
{
    _model = NULL;
}

propertyGraphics::~propertyGraphics() {};

Shader*& propertyGraphics::shader()
{
    return _shader;
}

Renderable*& propertyGraphics::model()
{
    return _model;
}

propertyPosition*& propertyGraphics::position()
{
    return _position;
}

void propertyGraphics::render()
{
    _model->render();
}
