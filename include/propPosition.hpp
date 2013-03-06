#ifndef POSITION
#define POSITION

extern "C" {
#include <GL/gl.h>
}

#include <glm/glm.hpp>
#include <vector>

using glm::mat4;
using glm::vec4;
using glm::mat3;
using std::vector;

class propertyPosition {
private:
    mat3 _rotation;
    mat3 _scale;
    mat4 _position; // actually, translation matrix
    vector <vec4> _gizmo; // bounding box
public:
    propertyPosition();
    ~propertyPosition();
    mat3& rotation();
    mat3& scale();
    mat4& position();
};

#endif // ifndef POSITION
