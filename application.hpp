#include <SDL/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/gl.h>
#include <GL/glut.h>
#include <functional>

#include "event.hpp"
#include "camera.hpp"

class application {
private:
    flyingCamera cam;
    keyboardHandler keyboard;

    bool running = false;
    SDL_Surface *display;

    float fovy = 60.0;
    float zNear = 1.0;
    float zFar = 99.0;
    float aspect = 1.0;

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
