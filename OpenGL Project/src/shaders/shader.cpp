#include "shader.h"
#include <iostream>
#include <string>


Shader::Shader(const char* vertexSource, const char* fragmentSource) : m_VertexSource(vertexSource), m_FragmentSource(fragmentSource)
{ 

	if (!load())
	{
		std::cout << "Error creating Shader" << std::endl;
	}
}

void Shader::cleanUp()
{
	glDeleteShader(m_VertexID);
	glDeleteShader(m_FragmentID);
	glDeleteProgram(m_programID);
}
void Shader::Uniform1f(const GLchar * name, GLfloat x)
{
	glUniform1f(glGetUniformLocation(this->m_programID, name), x);
}
void Shader::Uniform2f(const GLchar * name, vec2 vector)
{
	glUniform2f(glGetUniformLocation(this->m_programID, name), vector.x, vector.y);
}
void Shader::Uniform3f(const GLchar * name, vec3 vector)
{
	glUniform3f(glGetUniformLocation(this->m_programID, name), vector.x, vector.y, vector.z);
}
void Shader::Uniform4f(const GLchar * name, vec4 vector)
{
	
	glUniform4f(glGetUniformLocation(this->m_programID, name), vector.x, vector.y, vector.z, vector.w);
}
void Shader::UseShader()
{
	glUseProgram(m_programID);
}
void Shader::UniformLight(const GLchar * name, Light light)
{
	
	// TODO: Finish function
}
void Shader::UniformMatrix4f(const GLchar * name, GLsizei count, GLboolean transpose, mat4 matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(this->m_programID,name), count, transpose, matrix.elements);
}
bool Shader::load()
{
	m_VertexID = glCreateShader(GL_VERTEX_SHADER);
	if (!m_VertexID)
	{
		std::cout << "Error occured when creating the vertex shader object" << std::endl;
		return false;
	}
	glShaderSource(m_VertexID, 1, &m_VertexSource, NULL);
	glCompileShader(m_VertexID);
	m_FragmentID = glCreateShader(GL_FRAGMENT_SHADER);
	GLint compileStatus = GL_FALSE;
	glShaderSource(m_FragmentID, 1, &m_FragmentSource, NULL);
	glCompileShader(m_FragmentID);
	glGetProgramiv(m_programID, GL_COMPILE_STATUS, &compileStatus);
	if (!m_FragmentID)
	{
		GLint bufLength = 0;
		glGetShaderiv(m_FragmentID, GL_INFO_LOG_LENGTH, &bufLength);
		if (bufLength) {
			char* buf = (char*)malloc(bufLength);
			if (buf) {
				glGetShaderInfoLog(m_FragmentID, bufLength, NULL, buf);
				if(compileStatus != GL_TRUE)
					std::cout << "Not Compiled"<< std::endl;
				std::cout << "Could not compile shader: " << buf << std::endl;
				free(buf);
			}
		}
		glDeleteProgram(m_programID);
		m_FragmentID = 0;
		std::cout << "Error occured when creating the fragment shader object" << std::endl;
		return false;
	}
	m_programID = glCreateProgram();
	if (!m_programID)
	{
		std::cout << "Error occured when creating the program object" << std::endl;
		return false;
	}
	glAttachShader(m_programID, m_VertexID);
	glAttachShader(m_programID, m_FragmentID);
	glLinkProgram(m_programID);
	GLint linkStatus = GL_FALSE;
	glGetProgramiv(m_programID, GL_LINK_STATUS, &linkStatus);
	if (linkStatus != GL_TRUE)
	{
		GLint bufLength = 0;
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH,
			&bufLength);
		if (bufLength) {
			char* buf = (char*)malloc(bufLength);
			if (buf) {
				glGetProgramInfoLog(m_programID, bufLength, NULL, buf);
				printf("Could not link program:\n%s\n", buf);
				free(buf);
			}
		}
		glDeleteProgram(m_programID);
		m_programID = 0;
		return false;
	}
	glUseProgram(m_programID);
	return true;
}