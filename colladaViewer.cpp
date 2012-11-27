#include "colladaViewer.hpp"
#include "camera.hpp"
#include "Teapot.h"

#define SIZE 600

using glm::mat4;
using glm::vec3;

flyingCamera cam;

bool running = false;
SDL_Surface *display;

float fovy = 60.0;
float zNear = 1.0;
float zFar = 99.0;
float aspect = 1.0;

void render();
void loop();
void processEvent(SDL_Event &ev);
void processKey(SDLKey sym, SDLMod mod, Uint16 unicode);
void quit();
bool init();
bool cube(float size);

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
    glMatrixMode(GL_MODELVIEW);

    glm::mat4 mv = cam.getModelViewMatrix();
    glLoadMatrixf(&mv[0][0]);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Teapot::TeapotWired(.4);
    cube(.2);

    SDL_GL_SwapBuffers();
}

void loop()
{
    SDL_Delay(10);
}

void quit()
{
    SDL_FreeSurface(display);
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
    case SDLK_LEFT : {
	cam.rotateYaw(5.0);
	break;
    }
    case SDLK_RIGHT : {
	cam.rotateYaw(-5.0);
	break;
    }
    case SDLK_UP : {
	cam.rotatePitch(5.0);
	break;
    }
    case SDLK_DOWN : {
	cam.rotatePitch(-5.0);
	break;
    }
    case SDLK_w : {
	cam.moveForward(1.0);
	break;
    }
    case SDLK_s : {
	cam.moveForward(-1.0);
	break;
    }
    case SDLK_a : {
	cam.moveSide(-1.0);
	break;
    }
    case SDLK_d : {
	cam.moveSide(1.0);
	break;
    }
    default: break;
    }
}

bool init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) return false;
    if ((display = SDL_SetVideoMode(SIZE, SIZE, 32, SDL_GL_DOUBLEBUFFER | SDL_OPENGL)) == NULL) return false;

    SDL_WM_GrabInput(SDL_GRAB_ON);
    SDL_ShowCursor(SDL_DISABLE);
    SDL_WarpMouse(SIZE/2, SIZE/2);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glViewport(0, 0, SIZE, SIZE);

    glMatrixMode(GL_PROJECTION);
    mat4 persp = glm::perspective(fovy, aspect, zNear, zFar);
    glLoadMatrixf(&persp[0][0]);

    glMatrixMode(GL_MODELVIEW);
    mat4 mv = cam.getModelViewMatrix();
    glLoadMatrixf(&mv[0][0]);

    return true;
}

bool cube(float size)
{    
#define V(a,b,c) glVertex3d( a size, b size, c size );
#define N(a,b,c) glNormal3d( a, b, c );
	
  glBegin( GL_QUADS );
  N( 1.0, 0.0, 0.0); V(+,-,+); V(+,-,-); V(+,+,-); V(+,+,+);
  N( 0.0, 1.0, 0.0); V(+,+,+); V(+,+,-); V(-,+,-); V(-,+,+);
  N( 0.0, 0.0, 1.0); V(+,+,+); V(-,+,+); V(-,-,+); V(+,-,+);
  N(-1.0, 0.0, 0.0); V(-,-,+); V(-,+,+); V(-,+,-); V(-,-,-);
  N( 0.0,-1.0, 0.0); V(-,-,+); V(-,-,-); V(+,-,-); V(+,-,+);
  N( 0.0, 0.0,-1.0); V(-,-,-); V(-,+,-); V(+,+,-); V(+,-,-);
  glEnd();
  
#undef V
#undef N
  
  return true;
}
