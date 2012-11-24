#include "camera.hpp"

camera::camera()
{
    up = glm::vec3(0.0, -1.0, 0.0);
    position = glm::vec3(0.0, 0.0, 1.0);
    center = glm::vec3(0.0, 0.0, 0.0);
    fovy = 50.0;
    aspect = 1.0;

    mv = glm::lookAt(eye, center, up);
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

void camera::setCenter(glm::vec3 newcenter)
{
    center = newcenter;
    updateModelViewMatrix();
}

void camera::updateModelViewMatrix()
{
    mv = glm::lookAt(eye, center, up);
    glLoadMatrixf(&mv[0][0]);
}
