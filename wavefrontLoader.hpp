#ifndef WAVEFRONT_LOADER
#define WAVEFRONT_LOADER

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <GL/gl.h>

#include <fstream>
#include <sstream>
#include <functional>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <stdexcept>

class mesh {
    friend class loader;
private:
    void initializeModel();

    std::vector <glm::vec4> vertices;
    std::vector <glm::vec3> normals;
    std::vector <GLushort> indices;

    GLuint normalBuffer;
    GLuint vertexBuffer;
    GLuint elementBuffer;
public:
public:
    mesh();
    ~mesh();
    void render();
};

class loader {
private:
public:
    static void load(std::string filename, mesh &m);
    static void load2(std::string filename, mesh &m);
};

#endif // #ifndef WAVEFRONT_LOADER
