#include "application.hpp"
#include "Teapot.h"

#define SIZE 600

using glm::mat4;
using glm::vec3;

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

bool application::init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) return false;
    if ((display = SDL_SetVideoMode(SIZE, SIZE, 32, SDL_GL_DOUBLEBUFFER | SDL_OPENGL)) == NULL) return false;

    //SDL_WM_GrabInput(SDL_GRAB_ON);
    //SDL_ShowCursor(SDL_DISABLE);
    //SDL_WarpMouse(SIZE/2, SIZE/2);

    std::cout << "OpenGL version " << glGetString(GL_VERSION) << "\n";
    std::cout << "GLSL version " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";

    // glewExperimental = GL_TRUE; 
    if (glewInit() != GLEW_OK) {
    	std::cerr << "GLEW init failed!";
    	exit(0);
    }

    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);

    simple.init("shaders/vert.glsl", "shaders/frag.glsl");

    loader::load("flatGlider.obj", m);

    glGenBuffers(1, &modelvert);
    glBindBuffer(GL_ARRAY_BUFFER, modelvert);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m.vertices.size(), &m.vertices[0], GL_STATIC_DRAW);

    glEnable(GL_DEPTH_TEST);

    glClearColor(0.0f, 0.0f, 0.3f, 0.0f);
    glViewport(0, 0, SIZE, SIZE);

    cam.render();

    // Move dynamics in another class!
    // Key DOWN
    std::function <void()> f;
    f = [this]{ this->cam.setYawSpeed(1.0); };
    keyboardKeyDown.setAction(SDLK_LEFT, f);

    f = [this]{ this->cam.setYawSpeed(-1.0); };
    keyboardKeyDown.setAction(SDLK_RIGHT, f);

    f = [this]{ this->cam.setPitchSpeed(1.0); };
    keyboardKeyDown.setAction(SDLK_UP, f);

    f = [this]{ this->cam.setPitchSpeed(-1.0); };
    keyboardKeyDown.setAction(SDLK_DOWN, f);

    f = [this]{ this->cam.setForwardSpeed(.07); };
    keyboardKeyDown.setAction(SDLK_w, f);

    f = [this]{ this->cam.setForwardSpeed(-.07); };
    keyboardKeyDown.setAction(SDLK_s, f);

    f = [this]{ this->cam.setRollSpeed(-1.0); };
    keyboardKeyDown.setAction(SDLK_q, f);

    f = [this]{ this->cam.setRollSpeed(1.0); };
    keyboardKeyDown.setAction(SDLK_e, f);
    // Key UP

    f = [this]{ this->running = false; };
    keyboardKeyUp.setAction(SDLK_ESCAPE, f);

    f = [this]{ this->cam.setYawSpeed(0.0); };
    keyboardKeyUp.setAction(SDLK_LEFT, f);

    f = [this]{ this->cam.setYawSpeed(0.0); };
    keyboardKeyUp.setAction(SDLK_RIGHT, f);

    f = [this]{ this->cam.setPitchSpeed(0.0); };
    keyboardKeyUp.setAction(SDLK_UP, f);

    f = [this]{ this->cam.setPitchSpeed(0.0); };
    keyboardKeyUp.setAction(SDLK_DOWN, f);

    f = [this]{ this->cam.setForwardSpeed(0.0); };
    keyboardKeyUp.setAction(SDLK_w, f);

    f = [this]{ this->cam.setForwardSpeed(0.0); };
    keyboardKeyUp.setAction(SDLK_s, f);

    f = [this]{ this->cam.setRollSpeed(0.0); };
    keyboardKeyUp.setAction(SDLK_q, f);

    f = [this]{ this->cam.setRollSpeed(0.0); };
    keyboardKeyUp.setAction(SDLK_e, f);

    return true;
}

void application::render()
{
    simple.use(true);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLuint matrixID = simple.getUniformLocation("MVP");
    glm::mat4 MVP = cam.getProjectionMatrix() * cam.getModelViewMatrix();
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, modelvert);
    glVertexAttribPointer(0,                  // layout in shader program
			  4,                  // size
			  GL_FLOAT,           // type
			  GL_FALSE,           // normalized?
			  0,                  // stride
			  (void*)0            // array buffer offset
			  );
    
    glDrawArrays(GL_TRIANGLES, 0, m.vertices.size()); 
    
    glDisableVertexAttribArray(0);

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
	processKeyUp(ev.key.keysym.sym, ev.key.keysym.mod, ev.key.keysym.unicode);
	break;
    }
    case SDL_KEYDOWN: {
	processKeyDown(ev.key.keysym.sym, ev.key.keysym.mod, ev.key.keysym.unicode);	
	break;
    }
    default: break;
    }
}

void application::processKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    keyboardKeyUp.process(sym);
}

void application::processKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    keyboardKeyDown.process(sym);
}
