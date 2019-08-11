#pragma once
#include "mat4.h"
struct vec4
{
	float x, y, z, w;
	vec4();
	vec4(float x, float y, float z, float w);
	static vec4 multiply(const mat4& left, const vec4& right);
	vec4& multiply(const mat4& other);
	friend vec4 operator*(const mat4& left, const vec4& right);
	friend std::ostream& operator<< (std::ostream& stream, const vec4& vector);

};