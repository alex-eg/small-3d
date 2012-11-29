#ifndef WAVEFRONT_LOADER
#define WAVEFRONT_LOADER

#include <glm/glm.hpp>
#include <GL/gl.h>

#include <fstream>
#include <sstream>
#include <functional>
#include <string>
#include <vector>
#include <map>
#include <iostream>

class mesh {
    friend class loader;
private:
    std::string name;
    std::vector <glm::vec4> vertices;
    std::vector <glm::vec3> normals;
    std::vector <GLushort> elements;
public:
    mesh();
    ~mesh();
    void render();
};

class loader {
private:
public:
    static void load(std::string filename, mesh &m);
};

#endif
