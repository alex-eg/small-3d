#ifndef CAMERA
#define CAMERA

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <GL/gl.h>

#define PI 3.14159265

// Interface class
class camera {
public:
    virtual void setUpVector(glm::vec3 newUp)         = 0;
    virtual void setPositionVector(glm::vec3 newPos)  = 0;
    virtual void setTargetVector(glm::vec3 newTarget) = 0;
						
    virtual void rotatePitch(float degrees) = 0;
    virtual void rotateYaw(float degrees)   = 0;
    virtual void rotateRoll(float degrees)  = 0;

    virtual void moveForward(float meters)  = 0;
    virtual void moveSide(float meters)     = 0;
    virtual void moveVertical(float meters) = 0;
};

class realCamera : public camera {
protected:
    glm::mat4 modelView;
    glm::mat4 projection;
    glm::vec3 up;
    glm::vec3 position;
    glm::vec3 target;

    float fovy = 60.0;
    float aspect = 1.0;
    float zNear = 0.1;
    float zFar = 99.0;

    void updateMatrices();
public:
    realCamera();
    ~realCamera();

    void setUpVector(glm::vec3 newUp);
    void setPositionVector(glm::vec3 newPos);
    void setTargetVector(glm::vec3 newTarget);

    void render();

    glm::mat4 getModelViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;
};

class flyingCamera : public realCamera {
private:
    static float maxMoveSpeed;
    static float maxRotateSpeed;

    float velocityForward = 0;
    float velocitySide = 0;
    float velocityVertical = 0;

    float velocityYaw = 0;
    float velocityPitch = 0;
    float velocityRoll = 0;

    void rotateYaw(float degrees);
    void rotatePitch(float degrees);
    void rotateRoll(float degrees);

    void moveForward(float meters);
    void moveSide(float meters);
    void moveVertical(float meters);
public:
    flyingCamera();
    ~flyingCamera();

    void updatePosition();

    void setForwardSpeed(float meters_per_second);
    void setSideSpeed(float meters_per_second);
    void setVerticalSpeed(float meters_per_second);
	 
    void setYawSpeed(float degrees_per_second);
    void setPitchSpeed(float degrees_per_second);
    void setRollSpeed(float degrees_per_second);
};

#endif // ifndef CAMERA
