#ifndef MESH
#define MESH

#include "propGraphics.hpp"

#include <GL/glew.h>

#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <fstream>
#include <sstream>
#include <functional>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <stdexcept>

class Mesh : public Renderable {
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
    Mesh();
    ~Mesh();
    void render();
    bool loadFromFile(std::string filename);
};

#endif // MESH
