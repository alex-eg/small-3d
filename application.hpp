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
#include "wavefrontLoader.hpp"
#include "shader.hpp"

class application {
private:
    flyingCamera cam;
    keyboardHandler keyboard;

    bool running = false;
    SDL_Surface *display;

    mesh m;
    shaderProgram blinnPhong;
public:
    application();
    ~application();
    int start(int argc, char **argv);
    void render();
    void loop();
    void processEvent(SDL_Event &ev);
    void processKey(SDLKey sym, SDLMod mod, Uint16 unicode);
    void quit();
    bool init();
};

#endif // ifndef APPLICATION
