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
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0,                  // layout in shader program
    			  4,                  // size
    			  GL_FLOAT,           // type
    			  GL_FALSE,           // normalized?
    			  0,                  // stride
    			  (void*)0            // array buffer offset
    			  );

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glVertexAttribPointer(1,                  // layout in shader program
    			  3,                  // size
    			  GL_FLOAT,           // type
    			  GL_FALSE,           // normalized?
    			  0,                  // stride
    			  (void*)0            // array buffer offset
    			  );
    
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    glDisableVertexAttribArray(0);    
    glDisableVertexAttribArray(1);    
}

void mesh::initializeModel()
{
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals.size(), &normals[0], GL_STATIC_DRAW);

    glGenBuffers(1, &elementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * indices.size(), &indices[0], GL_STATIC_DRAW);
}

// Loader class

void loader::load(std::string filename, mesh &m)
{
    std::vector <glm::vec3> rawNormals;
    std::vector <glm::vec4> rawVertices;
    std::vector <GLushort> vertexIndex;
    std::vector <GLushort> normalIndex;
    
    std::ifstream file(filename);
    if (!file) {
	std::cerr << "Cannot open model file " << filename <<"!\n";
	throw std::invalid_argument(filename);
    }

    std::string line;
    std::map <std::string, std::function <void(std::string)> > processor;
    
    auto f = [&vertexIndex, &normalIndex](std::string command) {
	std::istringstream s(command);
	GLushort a, b, c, d, e ,f;
	s >> a;
	s.ignore(2);
	s >> b;
	
	a--; b--;
	vertexIndex.push_back(a);
	normalIndex.push_back(b);
	
	s >> c;
	s.ignore(2);
	s >> d;

	c--; d--;
	vertexIndex.push_back(c);
	normalIndex.push_back(d);

	s >> e;
	s.ignore(2);
	s >> f;

	e--; f--;
	vertexIndex.push_back(e);
	normalIndex.push_back(f);
    };
    processor["f "] = f;

    auto v = [&rawVertices](std::string command) {
	std::istringstream s(command);
	glm::vec4 v;
	s >> v.x; s >> v.y; s >> v.z; v.w = 1.0f;
	rawVertices.push_back(v);
    };
    processor["v "] = v;

    auto vn = [&rawNormals](std::string command) {
	std::istringstream s(command);
	glm::vec3 vn;
	s >> vn.x; s >> vn.y; s >> vn.z;
	rawNormals.push_back(vn);
    };
    processor["vn"] = vn;

    while (std::getline(file, line)) {
	std::string command = line.substr(0,2);
	auto f = processor[command];
	if (f) f(line.substr(2));
    }

    for (size_t i = 0; i < vertexIndex.size(); i++) {
	m.indices.push_back(vertexIndex[i]);
	m.vertices.push_back(rawVertices[vertexIndex[i]]);
	m.normals.push_back(rawNormals[normalIndex[i]]);
    }

    m.initializeModel();
}


void loader::load2(std::string filename, mesh &m)
{
    std::ifstream file(filename);
    if (!file) {
	std::cerr << "Cannot open model file " << filename <<"!\n";
	throw std::invalid_argument(filename);
    }

    std::string line;
    std::map <std::string, std::function <void(std::string)> > processor;
    
    auto f = [&m](std::string command) {
	std::istringstream s(command);
	GLushort a, b, c;
	s >> a; s >> b; s >> c;
	a--; b--; c--;
	m.indices.push_back(a);
	m.indices.push_back(b);
	m.indices.push_back(c);
    };
    processor["f "] = f;

    std::vector <glm::vec4> sharedVertices;
    
    auto sv = [&m, &sharedVertices](std::string command) {
	std::istringstream s(command);
	glm::vec4 v;
	s >> v.x; s >> v.y; s >> v.z; v.w = 1.0f;
	sharedVertices.push_back(v);
    };

    auto v = [&m](std::string command){
	std::istringstream s(command);
	glm::vec4 v;
	s >> v.x; s >> v.y; s >> v.z; v.w = 1.0f;
	m.vertices.push_back(v);
    };
    processor["v "] = sv;
    
    while (std::getline(file, line)) {
	std::string command = line.substr(0,2);
	auto f = processor[command];
	if (f) f(line.substr(2));
    }

    // m.normals.resize(m.vertices.size(), glm::vec3(0.0, 0.0, 0.0));
    // for (size_t i = 0; i < m.indices.size(); i+=3) {
    // 	GLushort ia = m.indices[i];
    // 	GLushort ib = m.indices[i+1];
    // 	GLushort ic = m.indices[i+2];
    // 	glm::vec3 normal = glm::normalize(glm::cross(
    // 						     glm::vec3(m.vertices[ib]) - glm::vec3(m.vertices[ia]),
    // 						     glm::vec3(m.vertices[ic]) - glm::vec3(m.vertices[ia])));
    // 	m.normals[ia] = m.normals[ib] = m.normals[ic] = normal;
    // }
    
    for (size_t i = 0; i < m.indices.size(); i++) {
     	m.vertices.push_back(sharedVertices[m.indices[i]]);
     	if ((i % 3) == 2) {
     	    GLushort ia = m.indices[i-2];
     	    GLushort ib = m.indices[i-1];
     	    GLushort ic = m.indices[i];
     	    glm::vec3 normal = glm::normalize(glm::cross(
							 glm::vec3(sharedVertices[ib]) - glm::vec3(sharedVertices[ia]),
							 glm::vec3(sharedVertices[ic]) - glm::vec3(sharedVertices[ia])
							 )
					      );
	    
	    for (int n = 0; n < 3; n++)
		m.normals.push_back(normal);
     	}
    }
    m.initializeModel();
}
