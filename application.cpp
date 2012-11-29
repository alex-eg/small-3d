#include "application.hpp"
#include "Teapot.h"

#define SIZE 600

using glm::mat4;
using glm::vec3;

bool cube(float size);

int main(int argc, char **argv)
{
    application app;
    return app.start(argc, argv);
}

application::application()
{
    running = false;
}

application::~application()
{
}

int application::start(int argc, char** argv)
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

void application::render()
{
    glMatrixMode(GL_MODELVIEW);

    glm::mat4 mv = cam.getModelViewMatrix();
    glLoadMatrixf(&mv[0][0]);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Teapot::TeapotWired(.4);
    cube(.2);

    SDL_GL_SwapBuffers();
}

void application::loop()
{
    cam.updatePosition();
    SDL_Delay(10);
}

void application::quit()
{
    SDL_FreeSurface(display);
    SDL_Quit();
}

void application::processEvent(SDL_Event &ev)
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

void application::processKey(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    keyboard.process(sym);
}

bool application::init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) return false;
    if ((display = SDL_SetVideoMode(SIZE, SIZE, 32, SDL_GL_DOUBLEBUFFER | SDL_OPENGL)) == NULL) return false;

    //SDL_WM_GrabInput(SDL_GRAB_ON);
    //SDL_ShowCursor(SDL_DISABLE);
    //SDL_WarpMouse(SIZE/2, SIZE/2);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glViewport(0, 0, SIZE, SIZE);

    loader::load("flatGlider.obj", m);

    cam.render();

    std::function <void()> f;
    f = [this]{ this->running = false; };
    keyboard.addAction(SDLK_ESCAPE, f);

    f = [this]{ this->cam.addYawSpeed(.02); };
    keyboard.addAction(SDLK_LEFT, f);

    f = [this]{ this->cam.addYawSpeed(-.02); };
    keyboard.addAction(SDLK_RIGHT, f);

    f = [this]{ this->cam.addPitchSpeed(.02); };
    keyboard.addAction(SDLK_UP, f);

    f = [this]{ this->cam.addPitchSpeed(-.02); };
    keyboard.addAction(SDLK_DOWN, f);

    f = [this]{ this->cam.addForwardSpeed(.02); };
    keyboard.addAction(SDLK_w, f);

    f = [this]{ this->cam.addForwardSpeed(-.02); };
    keyboard.addAction(SDLK_s, f);

    //f = [cam]{ cam.rotateYaw(5.0); };
    //keyboard.addAction(SDL_LEFT, f);
    
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
