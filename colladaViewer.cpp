#include "colladaViewer.hpp"

#define SIZE 600

using glm::mat4;
using glm::vec3;

vec3 eye = vec3(0.0, 0.0, 5.0);
vec3 up = vec3(0.0, 1.0, 0.0);
vec3 center = vec3(0.0, 0.0, 0.0);

bool running = false;
SDL_Surface *display;

int fovy = 60;
float zNear = 1.0;
float zFar = 99.0;
float aspect = 1.0;

void render();
void loop();
void processEvent(SDL_Event &ev);
void processKey(SDLKey sym, SDLMod mod, Uint16 unicode);
void quit();
bool init();

int main(int argc, char **argv)
{
    SDL_Event event;

    if (!init()) exit(-1);

    running = true;
    while (running) {
	while (SDL_PollEvent(&event))
	    processEvent(event);
	loop();
	render();
    }
    quit();
    return 0;
}

void render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSolidTeapot(1);
    SDL_GL_SwapBuffers();
}

void loop()
{
    SDL_Delay(10);
}

void quit()
{
    SDL_Quit();
}

void processEvent(SDL_Event &ev)
{
    switch (ev.type){
    case SDL_QUIT : {
	running = false;
	break;
    }
    case SDL_KEYUP : {
	processKey(ev.key.keysym.sym, ev.key.keysym.mod, ev.key.keysym.unicode);
	break;
    }
    default: break;
    }
}

void processKey(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    switch (sym) {
    case SDLK_ESCAPE : {
	running = false;
	break;
    }
    default: break;
    }
}

bool init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) return false;
    if ((display = SDL_SetVideoMode(SIZE, SIZE, 32, SDL_GL_DOUBLEBUFFER | SDL_OPENGL)) == NULL) return false;

    return true;

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glViewport(0, 0, SIZE, SIZE);

    glMatrixMode(GL_PROJECTION);
    glm::mat4 mv = glm::perspective(fovy, aspect, zNear, zFar);
    glLoadMatrixf(&mv[0]);

    glMatrixMode(GL_MODELVIEW);
    mv = glm::lookAt(eye, center, up);
    glLoadMatrixf(&mv[0]);

    return true;
}
