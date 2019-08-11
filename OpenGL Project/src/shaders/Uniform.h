#pragma once
#include <GL\glew.h>
#include "shader.h"
#include "../maths/vec2.h"
#include "../maths/vec3.h"
#include "../maths/vec4.h"
class Uniform
{
public:
	static void Uniform1f(const Shader shader, const GLchar *name, GLfloat x);
	static void Uniform2f(const Shader shader, const GLchar *name, vec2 vector);
	static void Uniform3f(const Shader shader, const GLchar *name, vec3 vector);
	static void Uniform4f(const Shader shader, const GLchar *name, vec4 vector);

	static void UniformMatrix4f(const Shader shader, const GLchar *name, GLsizei count, GLboolean transpose, mat4 matrix);



};