#ifndef GRAPHICS
#define GRAPHICS

#include "shader.hpp"
#include "propPosition.hpp"

class Renderable {
public:
    virtual void render() {};
};

class propertyGraphics {
private:
    Renderable *_model;
    Shader *_shader;
    propertyPosition *_position;
public:
    propertyGraphics();
    ~propertyGraphics();
    Shader*& shader();
    Renderable*& model();
    propertyPosition*& position();
    void render();
};

#endif // ifndef RENDERABLE
