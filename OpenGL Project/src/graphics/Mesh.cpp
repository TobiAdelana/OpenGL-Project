#include "Mesh.h"
#define MESH_POSITION_LAYOUT 0
#define MESH_COLOUR_LAYOUT 1
/*
#include <assimp\assimp.h>
#include <assimp\aiScene.h>
#include <assimp\aiPostProcess.h>

*/

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const std::vector<Texture>& textures )
{
	m_indices = indices;
	m_textures = textures;
	m_vertices = vertices;
	init();
}
Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices)
{
	m_indices = indices;
	m_vertices = vertices;
	init();
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
void Mesh::init()
{
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint), &m_indices[0], GL_STATIC_DRAW);

	//	Position data
	glEnableVertexAttribArray(MESH_POSITION_LAYOUT);
	glVertexAttribPointer(MESH_POSITION_LAYOUT, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	// Normal data
	glEnableVertexAttribArray(MESH_COLOUR_LAYOUT);
	
	glVertexAttribPointer(MESH_COLOUR_LAYOUT, 3, GL_FLOAT, GL_FALSE,  sizeof(Vertex), (GLvoid *)offsetof(Vertex, normal));
	// Texcoords data
	
	// POSSIBLY:	UNNECESSARY CODE 
	glBindVertexArray(0);
}

bool Mesh::Draw(Shader shader)
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
	//POSSIBLY: UNNECESSARY CODE
	glBindVertexArray(0);
	return true;
}

bool Mesh::LoadObj(const std::string& filename)
{
	std::ifstream file(filename, std::ifstream::in);
	
	if (!file.is_open()) return false;
	std::string line;
	std::vector<vec3> vertex_positions, normal_positions;
	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		char in;
		iss >> in;
		if (in == 'v')
		{
			iss >> in;
			float x, y, z;
			iss >> x >> y >> z;
			if (in == 'n')	normal_positions.push_back(vec3(x, y, z));
			else			vertex_positions.push_back(vec3(x, y, z));
		}
		else if (in == 'f')
		{
			for (int i = 0; i < 3; ++i)
			{
				std::string vert;
				iss >> vert;
				int vertex_index = std::stoi(vert.substr(0, vert.find("//")));
				int normal_index = std::stoi(vert.substr(vert.find("//") + 2, vert.length()));
				// std::cout << std::to_string(vertex_index) << std::endl;
				m_vertices.push_back(Vertex(vertex_positions[vertex_index - 1],
					normal_positions[normal_index - 1]));
				m_indices.push_back(indexCount);
				indexCount += 1;
				
			}
		}

	}
	file.close();
	init();
	return true;
}