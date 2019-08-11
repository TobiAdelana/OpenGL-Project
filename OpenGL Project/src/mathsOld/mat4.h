#pragma once
#include "vec3.h"

struct mat4
{
	mat4();
	mat4(float elements[16]);
	mat4& multiply(const mat4& other);
	mat4& multiply(const float other);
	mat4& add(const mat4& other);
	mat4& subtract(const mat4& other);

	static mat4 identity();
	static mat4 scale(float scale);
	static mat4 scale(vec3 scale);
	static mat4 inverse(const mat4& object);
	static mat4 ortho(float left, float right, float bottom, float top, float near, float far);
	static mat4 perspective(float fov, float aspect, float near, float far);
	static mat4 lookAt(const vec3& eye, const vec3& look, const vec3& up);
	static mat4 translate(const vec3& other);
	float elements[16];

	friend std::ostream& operator<<(std::ostream& stream, const mat4& matrix);
	friend mat4 operator+(mat4 left, const mat4& right);
	friend mat4 operator*(mat4 left, const mat4& right);
	friend mat4 operator*(float left, mat4 right);
	friend mat4 operator-(mat4 left, const mat4& right);
	friend mat4 operator-(mat4 right);

	mat4& operator+=(const mat4& other);
	mat4& operator-=(const mat4& other);
	mat4& operator*=(const mat4& other);
private:
	float determinant;
};
