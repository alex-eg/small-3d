#ifndef SHADER
#define SHADER

#include <GL/glew.h>
#include <GL/gl.h>

#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>

class Shader {

    int very_stub;
};

class shaderProgram {
private:
    GLuint programID;

    void getLinkErrors();
    void getCompileErrors(GLuint shaderID);
    std::string loadShaderSource(std::string filename);
public:
    shaderProgram();
    ~shaderProgram();
    bool init(std::string vertexShaderSourceFilename, std::string fragmentShaderSourceFilename);
    void use(bool use);
    GLuint getUniformLocation(std::string name);
};

#endif // ifndef SHADER
