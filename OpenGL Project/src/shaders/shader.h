#pragma once

#include <GL\glew.h>
#include "..\maths\vec2.h"
#include "..\maths\vec3.h"
#include "..\maths\vec4.h"
#include "..\maths\mat4.h"
#include "..\graphics\lighting\Light.h"
#include "..\graphics\Material.h"
#define SHADER_PROJECTION_MATRIX_NAME "proj_Matrix"
#define SHADER_VIEW_MATRIX_NAME "view_Matrix"
#define SHADER_MODEL_MATRIX_NAME "mod_Matrix"

class Shader
{
public:
	Shader(const std::string & vertexSource, const std::string & fragmentSource);
	Shader(const Shader&) = default;
	Shader& operator=(const Shader&) = default;
	~Shader();
	const std::string m_VertexSource, m_FragmentSource;

	void Uniform1f(const GLchar *name, GLfloat x);
	void Uniform2f(const GLchar *name, vec2 vector);
	void Uniform3f(const GLchar *name, vec3 vector);
	void Uniform4f(const GLchar *name, vec4 vector);
	void UseShader();

	void UniformLight(const GLchar * name, Light light);
	void UniformMatrix4f(const GLchar *name, GLsizei count, GLboolean transpose, mat4 matrix);
	void UniformMaterial(const GLchar *name, Material material);
private:
	GLuint m_VertexID, m_FragmentID, m_programID;
	bool load();

	
};