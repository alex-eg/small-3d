#ifndef LIGHT
#define LIGHT

#include <GL/gl.h>
#include <glm/glm.hpp>

class light
{
private:
    glm::vec4 color;
    glm::vec4 position;
public:
    light();
    ~light();
    light& operator=(const light &right);
    void setPosition(glm::vec4 pos);
    void setColor(glm::vec4 col);
};

#endif // ifndef LIGHT
