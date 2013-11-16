#ifndef APPLICATION
#define APPLICATION

#include <GL/glew.h>

#include <SDL/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/gl.h>
#include <GL/glut.h>

#include <functional>

#include "event.hpp"
#include "camera.hpp"
#include "mesh.hpp"
#include "shader.hpp"

class application {
private:
    flyingCamera cam;
    keyboardHandler keyboardKeyUp;
    keyboardHandler keyboardKeyDown;

    bool running = false;
    SDL_Surface *display;

    Mesh m;

    shaderProgram simple;

    GLuint vertexArrayID;
  
public:
    application();
    ~application();
    int start(int argc, char **argv);
    void render();
    void loop();
    void processEvent(SDL_Event &ev);
    void processKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
    void processKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
    void quit();
    bool init();
};

#endif // ifndef APPLICATION
