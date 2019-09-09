#pragma once
#include "vec2.h"
class vec3
{
public:
	float x = 0, y = 0, z = 0;

	vec3() {};
	constexpr vec3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {};
	constexpr vec3(const vec2& start, float z_) : x(start.x), y(start.y), z(z_) {};


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
	vec3& divide(const float other);

	friend vec3 operator- (const vec3& right);
	friend vec3 operator+ (vec3 left, const vec3& right);
	friend vec3 operator- (vec3 left, const vec3& right);
	friend vec3 operator/ (vec3 left, const float right);
	friend vec3 operator* (vec3 left, const float right);
	friend vec3 operator* (const float left, vec3 right);
	friend std::ostream& operator<<(std::ostream& stream, const vec3& vector);
	

	vec3& operator+= (const vec3& other);
	vec3& operator-= (const vec3& other);
	vec3& operator/= (const float other);
	vec3& operator*= (const float other);
	friend bool operator== (const vec3& lhs, const vec3& rhs);
	friend bool operator!= (const vec3& lhs, const vec3& rhs);



};