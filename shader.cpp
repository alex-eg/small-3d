#include "shader.hpp"
// Shader

shader::shader(GLenum shaderType, std::string filename) : type(shaderType)
{
    location = glCreateShader(type); 
    loadFromFile(filename);
}

shader::shader()
{

}

shader::~shader()
{
    glDeleteShader(location);
}

void shader::getErrors()
{
    GLint length;
    GLchar* log;
    glGetShaderiv(location, GL_INFO_LOG_LENGTH, &length);
    log = new GLchar[length + 1];
    glGetShaderInfoLog(location, length, &length, log);
    std::cerr << "Shader compile error:\n" << log << "\n";
    delete [] log;
}

bool shader::compile()
{
    GLint compiled;
    const GLchar *cSource = source.c_str();
    glShaderSource (location, 1, &cSource, NULL);
    glCompileShader (location);
    glGetShaderiv (location, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
	isCompiled = false;
	getErrors();
	return false;
    }
    compiled = true;
    return true;
}

void shader::loadFromFile(std::string filename)
{
    std::ifstream file(filename);
    if (!file) {
	std::cerr << "Cannot open shader file " << filename << "!\n";
	throw std::invalid_argument(filename);
    }
    std::string line;
    while (std::getline(file, line))
	source += line + "\n";
}

// Shader program

shaderProgram::shaderProgram()
{
}

shaderProgram::shaderProgram(std::string vertexShaderSourceFilename, std::string fragmentShaderSourceFilename)
{
    vertexShader = shader(GL_VERTEX_SHADER, vertexShaderSourceFilename);
    fragmentShader = shader(GL_FRAGMENT_SHADER, fragmentShaderSourceFilename);
    location = glCreateProgram();
}

shaderProgram::~shaderProgram()
{
    glDeleteProgram(location);
}

void shaderProgram::getErrors()
{
    GLint length;
    GLchar* log; 
    glGetShaderiv(location, GL_INFO_LOG_LENGTH, &length);
    log = new GLchar[length + 1];
    glGetShaderInfoLog(location, length, &length, log);
    std::cerr << "Shader compile error:\n" << log << "\n";
    delete [] log;
}

bool shaderProgram::init()
{
    glAttachShader(location, vertexShader.location);
    glAttachShader(location, fragmentShader.location);
    glLinkProgram(location);
    GLint linked;
    glGetProgramiv(location, GL_LINK_STATUS, &linked);
    if (!linked) {
	getErrors();
	return false;
    }
    return true;
}

void shaderProgram::useVertexShader(shader vertex)
{
    vertexShader = vertex;
}

void shaderProgram::useFragmentShader(shader fragment)
{
    fragmentShader = fragment;
}

void shaderProgram::use(bool use)
{
    if (use) glUseProgram(location);
    else glUseProgram(0);
}
