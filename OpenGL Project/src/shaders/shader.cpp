#include "shader.h"
#include <iostream>
#include <string>


Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource) : m_VertexSource(vertexSource), m_FragmentSource(fragmentSource)
{ 

	if (!load())
	{
		std::cout << "Error creating Shader" << std::endl;
	}
}

Shader::~Shader()
{
	glDeleteShader(m_VertexID);
	glDeleteShader(m_FragmentID);
	glDeleteProgram(m_programID);
}

void Shader::Uniform1f(const GLchar * name, GLfloat x)
{
	glUniform1f(glGetUniformLocation(m_programID, name), x);
}
void Shader::Uniform2f(const GLchar * name, vec2 vector)
{
	glUniform2f(glGetUniformLocation(m_programID, name), vector.x, vector.y);
}
void Shader::Uniform3f(const GLchar * name, vec3 vector)
{
	glUniform3f(glGetUniformLocation(m_programID, name), vector.x, vector.y, vector.z);
}
void Shader::Uniform4f(const GLchar * name, vec4 vector)
{
	glUniform4f(glGetUniformLocation(m_programID, name), vector.x, vector.y, vector.z, vector.w);
}
void Shader::UseShader()
{
	glUseProgram(m_programID);
}
void Shader::UniformLight(const GLchar * name, Light light)
{
	std::string light_name = name;
	glUniform3f(glGetUniformLocation(m_programID, (light_name + ".position").c_str()), light.m_position.x, light.m_position.y, light.m_position.z);
	glUniform3f(glGetUniformLocation(m_programID, (light_name + ".colour").c_str()), light.m_colour.x, light.m_colour.y, light.m_colour.z);
	
}
void Shader::UniformMatrix4f(const GLchar * name, GLsizei count, GLboolean transpose, mat4 matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(m_programID,name), count, transpose, matrix.elements);
}
void Shader::UniformMaterial(const GLchar * name, Material material)
{
	std::string material_name = name;
//	glUniform3f(glGetUniformLocation(m_programID, (name + ".ambientColour").c_str()), material.m_ambientColour.x, mater)
}
bool Shader::load()
{
	m_VertexID = glCreateShader(GL_VERTEX_SHADER);
	if (!m_VertexID)
	{
		std::cout << "Error occured when creating the vertex shader object" << std::endl;
		return false;
	}
	GLint compileStatus = GL_FALSE;
	const char* strVertexSource = m_VertexSource.c_str();
	const char* strFragmentSource = m_FragmentSource.c_str();
	glShaderSource(m_VertexID, 1, &strVertexSource, NULL);
	glCompileShader(m_VertexID);
	glGetShaderiv(m_VertexID, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus == GL_FALSE)
	{
		std::cout << "Failed to compile vertex shader" << std::endl;
		GLint bufLength = 0;
		glGetShaderiv(m_VertexID, GL_INFO_LOG_LENGTH, &bufLength);

		std::string buf;
		buf.reserve(bufLength);
		glGetShaderInfoLog(m_VertexID, bufLength, NULL, buf.data());
		std::cout << "Log: " << buf << std::endl;
		return false;
	}

	m_FragmentID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_FragmentID, 1, &strFragmentSource, NULL);
	glCompileShader(m_FragmentID);
	glGetProgramiv(m_programID, GL_COMPILE_STATUS, &compileStatus);
	if (!m_FragmentID)
	{
		GLint bufLength = 0;
		glGetShaderiv(m_FragmentID, GL_INFO_LOG_LENGTH, &bufLength);
		if (bufLength != 0) {
			std::string buf;
			buf.reserve(bufLength);
			glGetShaderInfoLog(m_FragmentID, bufLength, NULL, buf.data());
			if(compileStatus != GL_TRUE)
				std::cout << "Could not compile shader: " << buf << std::endl;
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
			std::string buf;
			buf.reserve(bufLength);
			glGetProgramInfoLog(m_programID, bufLength, NULL, buf.data());
			std::cout << "Could not link program: " << buf << '\n';
		}
		glDeleteProgram(m_programID);
		m_programID = 0;
		return false;
	}
	glUseProgram(m_programID);
	return true;
}