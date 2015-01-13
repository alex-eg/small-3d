#include "shader.hpp"

// Shader program

void shaderProgram::getCompileErrors(GLuint shaderID)
{
    GLint length;
    GLchar* log;
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
    if (length > 0) {
	log = new GLchar[length + 1];
	glGetShaderInfoLog(shaderID, length, NULL, log);
	std::cerr << "Shader reports: " <<  log << "\n";
	delete [] log;
    }
}

std::string shaderProgram::loadShaderSource(std::string filename)
{
    std::string source = "";
    std::ifstream file(filename);
    if (!file) {
	std::cerr << "Cannot open shader file " << filename << "!\n";
	throw std::invalid_argument(filename);
    }

    std::string line;
    while (std::getline(file, line))
	source += line + "\n";
    file.close();
    return source;
}

shaderProgram::shaderProgram()
{
}

shaderProgram::~shaderProgram()
{

}

void shaderProgram::getLinkErrors()
{
    GLint length;
    GLchar* log; 
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &length);
    if (length > 0) {
	log = new GLchar [length + 1];
	glGetProgramInfoLog(programID, length, NULL, log);
	std::cerr << "Shader program compile reports:\n" << log << "\n";
	delete [] log;
    }
}

bool shaderProgram::init(std::string vertexShaderSourceFilename, std::string fragmentShaderSourceFilename)
{

    GLuint vertexShaderID;
    vertexShaderID = glCreateShader(GL_VERTEX_SHADER); 
    
    std::string vertexShaderSource = loadShaderSource(vertexShaderSourceFilename);

    const GLchar *vertexShaderCSource = vertexShaderSource.c_str();
    glShaderSource (vertexShaderID, 1, &vertexShaderCSource, NULL);
    glCompileShader (vertexShaderID);

    getCompileErrors(vertexShaderID);

    GLuint fragmentShaderID;
    fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER); 
    
    std::string fragmentShaderSource = loadShaderSource(fragmentShaderSourceFilename);

    const GLchar *fragmentShaderCSource = fragmentShaderSource.c_str();
    glShaderSource (fragmentShaderID, 1, &fragmentShaderCSource, NULL);
    glCompileShader (fragmentShaderID);

    getCompileErrors(fragmentShaderID);

    programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);

    getLinkErrors();

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    return true;
}

GLuint shaderProgram::getUniformLocation(std::string name)
{
    const GLchar *cName = name.c_str();
    GLuint uniformID = glGetUniformLocation(programID, cName);
    return uniformID;
}

void shaderProgram::printProgramIntrospection()
{
    GLint numUniforms = 0;
    glGetProgramInterfaceiv(programID, GL_UNIFORM, GL_ACTIVE_RESOURCES, &numUniforms);
    const GLenum properties[4] = {GL_BLOCK_INDEX, GL_TYPE, GL_NAME_LENGTH, GL_LOCATION};
 
    for(int unif = 0; unif < numUniforms; ++unif) {
        GLint values[4];
        glGetProgramResourceiv(programID, GL_UNIFORM, unif, 4, properties, 4, NULL, values);
 
        //Skip any uniforms that are in a block.
        if(values[0] != -1)
            continue;
 
        //Get the name. Must use a std::vector rather than a std::string for C++03 standards issues.
        //C++11 would let you use a std::string directly.
        std::string nameData;
        glGetProgramResourceName(programID, GL_UNIFORM, unif, nameData.size(), NULL, &nameData[0]);
        std::string name(nameData.begin(), nameData.end() - 1);
    }
}

void shaderProgram::use(bool use)
{
    if (use) glUseProgram(programID);
    else glUseProgram(0);
}
