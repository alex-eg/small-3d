#ifndef DYNAMICS
#define DYNAMICS

extern "C" {
#include <GL/gl.h>
}

#include <glm/glm.hpp>

#include "propPosition.hpp"

using glm::vec3;

class propertyDynamics {
private:
    vec3 _velocity;
    vec3 _angularVelocity; // Euler angles, to be replaced

    vec3 _acceleration;
    vec3 _angularAcceleration;
public:
    propertyDynamics();
    ~propertyDynamics();
    void updatePosition();
    
    vec3& acceleration();
    vec3& angularAcceleration();
};    

#endif // ifndef DYNAMICS
