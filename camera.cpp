#include "camera.hpp"

camera::camera()
{
    up = glm::vec3(0.0, -1.0, 0.0);
    position = glm::vec3(0.0, 1.0, 1.0);
    target = glm::vec3(0.0, 0.0, 0.0);
    fovy = 50.0;
    aspect = 1.0;

    mv = glm::lookAt(position, target, up);
}

camera::~camera()
{
}

void camera::setUpVector(glm::vec3 newup)
{
    up = newup;
    updateModelViewMatrix();
}

void camera::setPosition(glm::vec3 newpos)
{
    position = newpos;
    updateModelViewMatrix();
}

void camera::setTarget(glm::vec3 newtarget)
{
    target = newtarget;
    updateModelViewMatrix();
}

void camera::updateModelViewMatrix()
{
    glMatrixMode(GL_MODELVIEW);
    mv = glm::lookAt(position, target, up);
    glLoadMatrixf(&mv[0][0]);
}

glm::mat4 camera::getModelViewMatrix()
{
    return mv;
}

void camera::rotatePitch(float degrees)
{
    glm::vec3 dir = target - position;
    dir = glm::normalize(dir);
    glm::vec3 axis = glm::cross(dir, up);
    glm::mat4 rot = glm::rotate(glm::mat4(1.0), degrees, axis);
    glm::mat3 rot3(rot);
    up = rot3 * up;
    target = rot3 * target;
    glm::vec3 newDir = rot3 * dir;
    center = newDir + position;
    updateModelViewMatrix();
}

void camera::rotateYaw(float degrees)
{

}

void camera::rotateRoll(float degrees)
{

}
