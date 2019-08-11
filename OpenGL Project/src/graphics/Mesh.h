#pragma once
#include "../maths/vec3.h"
#include "../shaders/shader.h"
#include "../shaders/Uniform.h"
#include <sstream>
#include <string>
#include <vector>
#include <GL\glew.h>

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

	Mesh(std::vector<Vertex> vertices,  std::vector<GLuint> indices, std::vector<Texture> textures);
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices);
	Mesh(const char* fileName);
	~Mesh();
	bool Draw(Shader shader);
private:
	GLuint VBO, VAO, EBO;
	void cleanUp();
	void init();
};