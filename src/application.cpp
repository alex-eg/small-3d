#include "application.hpp"

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

    //simple.init("shaders/vert.glsl", "shaders/frag.glsl");
    simple.init("shaders/light.vert.glsl", "shaders/light.frag.glsl");

    //loader::load("flatGlider-normals.obj", m);

    m.loadFromFile("resources/models/suzanne.obj");

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

    f = [this]{ this->simple.printProgramIntrospection(); };
    keyboardKeyUp.setAction(SDLK_i, f);
    
    return true;
}

void application::render()
{
    simple.use(true);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLuint lightPosition = simple.getUniformLocation("lightPosition");
    GLuint lightColor = simple.getUniformLocation("lightColor");

    GLuint ambient = simple.getUniformLocation("ambient"); 
    GLuint diffuse = simple.getUniformLocation("diffuse"); 
    GLuint specular = simple.getUniformLocation("specular"); 
    GLuint emission = simple.getUniformLocation("emission"); 
    GLuint shininess = simple.getUniformLocation("shininess"); 

    GLfloat lp[4] = {15.0, 15.0, 15.0, 1.0};
    glUniform4fv(lightPosition, 1, lp);

    GLfloat lc[4] = {0.7, 0.7, 0.7, 1.0};
    glUniform4fv(lightColor, 1, lc);

    GLfloat am[4] = {0.1, 0.1, 0.1, 1.0};
    glUniform4fv(ambient, 1, am);

    GLfloat df[4] = {0.3, 0.5, 0.8, 1.0};
    glUniform4fv(diffuse, 1, df);

    GLfloat sp[4] = {1.0, 1.0, 1.0, 1.0};
    glUniform4fv(specular, 1, sp);

    GLfloat em[4] = {0.0, 0.0, 0.0, 1.0};
    glUniform4fv(emission, 1, em);

    GLfloat sh = 500;
    glUniform1f(shininess, sh);

    GLuint MV = simple.getUniformLocation("MV");
    glm::mat4 MVm = cam.getModelViewMatrix();
    glUniformMatrix4fv(MV, 1, GL_FALSE, &MVm[0][0]);

    GLuint P = simple.getUniformLocation("P");
    glm::mat4 Pm = cam.getProjectionMatrix();
    glUniformMatrix4fv(P, 1, GL_FALSE, &Pm[0][0]);

    m.render();
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


