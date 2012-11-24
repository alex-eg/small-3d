#ifndef CAMERA
#define CAMERA

#include <glm/glm.hpp>
#include <GL/gl.h>

class camera {
private:
    glm::mat4 mv;
    glm::vec3 up;
    glm::vec3 position;
    glm::vec3 center;
    float fovy;
    float aspect;

    void updateModelViewMatrix();
public:
    camera();
    ~camera();
    void setUpVector(glm::vec3 newup);
    void setPosition(glm::vec3 newpos);
    void setCenter(glm::vec3 newcenter);

    void rotatePitch(float degrees);
    void rotateYaw(float degrees);
    void rotateRoll(float degrees);
    glm::mat4 getModelViewMatrix();
};

#endif
