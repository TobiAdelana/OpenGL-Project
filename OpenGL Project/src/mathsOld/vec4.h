#pragma once
#include "mat4.h"
struct vec4
{
	float x, y, z, w;
	vec4();
	vec4(float x, float y, float z, float w);
	vec4& multiply(const mat4& other);
	friend std::ostream& operator<< (std::ostream& stream, const vec4& vector);

};