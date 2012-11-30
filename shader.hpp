#ifndef SHADER
#define SHADER

#include <GL/glew.h>
#include <GL/gl.h>

#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>

class shader {
    friend class shaderProgram;
private:
    std::string source = "";
    GLuint location;
    bool isCompiled = false;
    GLenum type;

    void getErrors();
public:
    shader();
    shader(GLenum shaderType, std::string filename);
    ~shader();
    bool compile();
    void loadFromFile(std::string filename);
};

class shaderProgram {
private:
    GLuint location;
    shader vertexShader;
    shader fragmentShader;

    void getErrors();
public:
    shaderProgram();
    shaderProgram(shader vertex, shader fragment);
    shaderProgram(std::string vertexShaderSourceFilename, std::string fragmentShaderSourceFilename);
    ~shaderProgram();
    void useVertexShader(shader vertex);
    void useFragmentShader(shader fragment);
    bool init();
    void use(bool use);
};

#endif // ifndef SHADER
