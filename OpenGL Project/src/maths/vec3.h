#pragma once
#include "vec2.h"
struct vec3
{

	float x, y, z;
	vec3();
	static vec3 UP;

	vec3(float x, float y, float z);
	vec3(const vec2 start, float z);

	float dot(const vec3& other);
	static float dot(const vec3& left, const vec3& right);
	static vec3 cross(const vec3& left, const vec3& right);
	static vec3 normalise(const vec3& other);

	float GetMagnitude() const;
	float angleBetween(const vec3& other);

	vec3 normalise();
	vec3& cross(const vec3& other);
	vec3& add(const vec3& other);
	vec3& subtract(const vec3& other);
	vec3& multiply(const float other);
	vec3& multiply(const vec3& other);
	vec3& divide(const vec3& other);
	vec3& divide(const float other);

	friend vec3 operator- (const vec3& right);
	friend vec3 operator+ (vec3 left, const vec3& right);
	friend vec3 operator- (vec3 left, const vec3& right);
	friend vec3 operator/ (vec3 left, const vec3& right);
	friend vec3 operator/ (vec3 left, const float right);
	friend vec3 operator* (vec3 left, const vec3& right);
	friend vec3 operator* (vec3 left, const float right);
	friend vec3 operator* (const float left, vec3 right);
	friend std::ostream& operator<<(std::ostream& stream, const vec3& vector);
	

	vec3& operator+= (const vec3& other);
	vec3& operator-= (const vec3& other);
	vec3& operator/= (const float other);
	vec3& operator*= (const float other);
	bool operator== (const vec3& other);
	bool operator!= (const vec3& other);



};