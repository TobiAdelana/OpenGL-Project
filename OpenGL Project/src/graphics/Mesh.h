#pragma once
#include "../maths/vec3.h"
#include "../shaders/shader.h"
#include "../shaders/Uniform.h"
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>

#include <GL/glew.h>

struct Vertex
{
	Vertex(vec3 position, vec3 normal) 
	{
		this->position = position;
		this->normal = normal;
		//this->texCoords = texCoords;
	};
	vec3 position;
	vec3 normal;
};

struct Texture
{
	GLuint id;
	std::string type;
};

class Mesh
{
public:
	std::vector<Vertex> m_vertices;
	std::vector<Texture>m_textures;
	std::vector<GLuint> m_indices;
	Mesh() {};
	Mesh(const std::vector<Vertex>& vertices,	const std::vector<GLuint>& indices, const std::vector<Texture>& textures);
	Mesh(const std::vector<Vertex>& vertices,	const std::vector<GLuint>& indices);
	~Mesh();
	bool Draw(Shader shader);
	bool LoadObj(const std::string& filename);
private:
	GLuint VBO =0, VAO= 0, EBO =0;
	unsigned int indexCount = 0;
	void init();
};