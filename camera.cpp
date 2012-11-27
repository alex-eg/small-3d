#include "camera.hpp"

realCamera::realCamera()
{
    up = glm::vec3(0.0, -1.0, 0.0);
    position = glm::vec3(0.0, 1.0, 1.0);
    target = glm::vec3(0.0, 0.0, 0.0);
    fovy = 50.0;
    aspect = 1.0;

    mv = glm::lookAt(position, target, up);
}

realCamera::~realCamera()
{
}

void realCamera::setUpVector(glm::vec3 newUp)
{
    up = newUp;
    updateModelViewMatrix();
}

void realCamera::setPositionVector(glm::vec3 newPosition)
{
    position = newPosition;
    updateModelViewMatrix();
}

void realCamera::setTargetVector(glm::vec3 newTarget)
{
    target = newTarget;
    updateModelViewMatrix();
}

void realCamera::updateModelViewMatrix()
{
    glMatrixMode(GL_MODELVIEW);
    mv = glm::lookAt(position, target, up);
    glLoadMatrixf(&mv[0][0]);
}

glm::mat4 realCamera::getModelViewMatrix()
{
    return mv;
}

/* Flying camera class */

flyingCamera::flyingCamera() : realCamera() {};
flyingCamera::~flyingCamera() {};

void flyingCamera::rotatePitch(float degrees)
{
    glm::vec3 direction = target - position;
    direction = glm::normalize(direction);
    glm::vec3 axis = glm::cross(direction, up);
    glm::mat4 rot = glm::rotate(glm::mat4(1.0), degrees, axis);
    glm::mat3 rot3(rot);
    up = rot3 * up;
    glm::vec3 newDir = rot3 * direction;
    target = newDir + position;
    updateModelViewMatrix();
}

void flyingCamera::rotateYaw(float degrees)
{
    glm::vec3 direction = target - position;
    direction = glm::normalize(direction);
    glm::vec3 axis = glm::normalize(up);
    glm::mat4 rot = glm::rotate(glm::mat4(1.0), degrees, axis);
    glm::mat3 rot3(rot);
    glm::vec3 newDir = rot3 * direction;
    target = newDir + position;
    updateModelViewMatrix();
}

void flyingCamera::rotateRoll(float degrees)
{

}

void flyingCamera::moveForward(float meters)
{
    glm::vec3 direction = target - position;
    direction = glm::normalize(direction);
    position += direction * meters;
    updateModelViewMatrix();
}

void flyingCamera::moveSide(float meters)
{
    glm::vec3 direction = target - position;
    direction = glm::normalize(direction);
    glm::vec3 side = glm::cross(direction, up);
    position += side * meters;
    updateModelViewMatrix();
}

void flyingCamera::moveVertical(float meters)
{
    glm::vec3 normUp = glm::normalize(up);
    position += normUp * meters;
    updateModelViewMatrix();
}
