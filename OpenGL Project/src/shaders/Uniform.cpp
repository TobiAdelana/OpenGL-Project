#include "Uniform.h"
#include <GL\glew.h>
#include "shader.h"

void Uniform::Uniform1f(const Shader shader, const GLchar * name, GLfloat x)
{
	GLint uniformLoc = glGetUniformLocation(shader.m_programID, name);
	glUniform1f(uniformLoc, x);
}
void Uniform::Uniform2f(const Shader shader, const GLchar * name, vec2 vector)
{
	GLint uniformLoc = glGetUniformLocation(shader.m_programID, name);
	glUniform2f(uniformLoc, vector.x, vector.y);
}
void Uniform::Uniform3f(const Shader shader, const GLchar * name, vec3 vector)
{
	GLint uniformLoc = glGetUniformLocation(shader.m_programID, name);
	glUniform3f(uniformLoc, vector.x, vector.y, vector.z);
}
void Uniform::Uniform4f(const Shader shader, const GLchar * name, vec4 vector)
{
	GLint uniformLoc = glGetUniformLocation(shader.m_programID, name);
	glUniform4f(uniformLoc, vector.x, vector.y, vector.z, vector.w);
}
void Uniform::UniformMatrix4f(const Shader shader, const GLchar * name, GLsizei count, GLboolean transpose, mat4 matrix)
{
	GLint uniformLoc = glGetUniformLocation(shader.m_programID, name);
	glUniformMatrix4fv(uniformLoc, count, transpose, &matrix.elements[0]);
}




