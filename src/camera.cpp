#include "camera.hpp"

realCamera::realCamera()
{
    up = glm::vec3(0.0, 1.0, 0.0);
    position = glm::vec3(0.0, 0.0, 2.0);
    target = glm::vec3(0.0, 0.0, 0.0);

    modelView = glm::lookAt(position, target, up);
    projection = glm::perspective(fovy, aspect, zNear, zFar);
}

realCamera::~realCamera()
{
}

void realCamera::setUpVector(glm::vec3 newUp)
{
    up = newUp;
    updateMatrices();
}

void realCamera::setPositionVector(glm::vec3 newPosition)
{
    position = newPosition;
    updateMatrices();
}

void realCamera::setTargetVector(glm::vec3 newTarget)
{
    target = newTarget;
    updateMatrices();
}

void realCamera::updateMatrices()
{
    projection = glm::perspective(fovy, aspect, zNear, zFar);

    modelView = glm::lookAt(position, target, up);
}

glm::mat4 realCamera::getModelViewMatrix() const
{
    return modelView;
}

glm::mat4 realCamera::getProjectionMatrix() const
{
    return projection;
}

void realCamera::render()
{
    updateMatrices();
}

/* Flying camera class */

float flyingCamera::maxMoveSpeed = 3.0f;
float flyingCamera::maxRotateSpeed = 10.0f;

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
    updateMatrices();
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
    updateMatrices();
}

void flyingCamera::rotateRoll(float degrees)
{
    glm::vec3 direction = target - position;
    direction = glm::normalize(direction); 

    glm::vec3 axis = direction; // Direction is axis
    glm::mat4 rot = glm::rotate(glm::mat4(1.0), degrees, axis);

    glm::mat3 rot3(rot);
    up = rot3 * up;
    updateMatrices();
}

void flyingCamera::moveForward(float meters)
{
    glm::vec3 direction = target - position;
    direction = glm::normalize(direction);
    position += direction * meters;
    updateMatrices();
}

void flyingCamera::moveSide(float meters)
{
    glm::vec3 direction = target - position;
    direction = glm::normalize(direction);
    glm::vec3 side = glm::cross(direction, up);
    position += side * meters;
    updateMatrices();
}

void flyingCamera::moveVertical(float meters)
{
    glm::vec3 normUp = glm::normalize(up);
    position += normUp * meters;
    updateMatrices();
}

void flyingCamera::updatePosition() // Dynamics have to be in another componemt!
{
    moveForward(velocityForward);
    moveSide(velocitySide);
    moveVertical(velocityVertical);

    rotateRoll(velocityRoll);
    rotatePitch(velocityPitch);
    rotateYaw(velocityYaw);

}

// Todo: move dynamics in another class! Or even PROPERTY
// Everyone like property-based engines!
// Keyword: message passing

void flyingCamera::setForwardSpeed(float meters_per_second)
{
    velocityForward = meters_per_second;
}
void flyingCamera::setSideSpeed(float meters_per_second)
{
    velocitySide = meters_per_second;
}
void flyingCamera::setVerticalSpeed(float meters_per_second)
{
    velocityVertical = meters_per_second;
}

void flyingCamera::setYawSpeed(float degrees_per_second)
{
    velocityYaw = degrees_per_second;
}

void flyingCamera::setPitchSpeed(float degrees_per_second)
{
    velocityPitch = degrees_per_second;
}

void flyingCamera::setRollSpeed(float degrees_per_second)
{
    velocityRoll = degrees_per_second;
}
