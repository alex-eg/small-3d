#ifndef CAMERA
#define CAMERA

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <GL/gl.h>

#define PI 3.1415927

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
    glm::mat4 mv;
    glm::vec3 up;
    glm::vec3 position;
    glm::vec3 target;
    float fovy;
    float aspect;

    void updateModelViewMatrix();
public:
    realCamera();
    ~realCamera();

    void setUpVector(glm::vec3 newUp);
    void setPositionVector(glm::vec3 newPos);
    void setTargetVector(glm::vec3 newTarget);

    /*    void rotatePitch(float degrees);
    void rotateYaw(float degrees)  ;
    void rotateRoll(float degrees) ;
    				   
    void moveForward(float meters) ;
    void moveSide(float meters)    ;
    void moveVertical(float meters);*/

    glm::mat4 getModelViewMatrix();
};

class flyingCamera : public realCamera {
public:
    flyingCamera();
    ~flyingCamera();

    void rotatePitch(float degrees);
    void rotateYaw(float degrees);
    void rotateRoll(float degrees);

    void moveForward(float meters);
    void moveSide(float meters);
    void moveVertical(float meters);
};

#endif
