#ifndef CAMERA
#define CAMERA

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <GL/gl.h>

#define PI 3.1415927

class camera {
private:
    glm::mat4 mv;
    glm::vec3 up;
    glm::vec3 position;
    glm::vec3 target;
    float fovy;
    float aspect;

    void updateModelViewMatrix();
public:
    camera();
    ~camera();
    void setUpVector(glm::vec3 newup);
    void setPosition(glm::vec3 newpos);
    void setTarget(glm::vec3 newtarget);

    void rotatePitch(float degrees);
    void rotateYaw(float degrees);
    void rotateRoll(float degrees);
    glm::mat4 getModelViewMatrix();
};

inline float toRadians(float degrees)
{
    return PI/180.0 * degrees;
}

#endif
