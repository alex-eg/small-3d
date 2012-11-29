#include "wavefrontLoader.hpp"

// Mesh class

mesh::mesh()
{

}

mesh::~mesh()
{

}

void mesh::render()
{
    
}

// Loader class (?)

void loader::load(std::string filename, mesh &m)
{
    std::fstream file(filename, std::ios::in);
    if (!file) {
	std::cerr << "Cannot open " << filename <<"!\n";
	return;
    }
    std::string line;
    std::map <std::string, std::function<void(std::string)> > processor;
    auto f = [&m](std::string command){
	std::istringstream s(command);
	GLushort a, b, c;
	s >> a; s >> b; s >> c;
	a--; b--; c--;
	m.elements.push_back(a);
	m.elements.push_back(b);
	m.elements.push_back(c);
    };
    processor["f "] = f;

    auto v = [&m](std::string command){
	std::istringstream s(command);
	 glm::vec4 v;
	 s >> v.x; s >> v.y; s >> v.z; v.w = 1.0f;
	 m.vertices.push_back(v);
    };
    processor["v "] = v;
    
    while (std::getline(file, line)) {
	std::string command = line.substr(0,2);
	auto f = processor[command];
	if (f) f(line.substr(2));
    }

    m.normals.resize(m.vertices.size(), glm::vec3(0.0, 0.0, 0.0));
    for (size_t i = 0; i < m.elements.size(); i+=3) {
	GLushort ia = m.elements[i];
	GLushort ib = m.elements[i+1];
	GLushort ic = m.elements[i+2];
	glm::vec3 normal = glm::normalize(glm::cross(
						     glm::vec3(m.vertices[ib]) - glm::vec3(m.vertices[ia]),
						     glm::vec3(m.vertices[ic]) - glm::vec3(m.vertices[ia])));
	m.normals[ia] = m.normals[ib] = m.normals[ic] = normal;
    } 
}
