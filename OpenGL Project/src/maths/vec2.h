#pragma once
#include <ostream>
struct vec2 {
	float x = 0, y = 0;
	constexpr vec2() {};
	constexpr vec2(float x_, float y_) : x(x_), y(y_) {};
	vec2& add(const vec2& other);
	vec2& subtract(const vec2& other);
	vec2& multiply(const vec2& other);
	vec2& divide(const vec2& other);

	float dot(const vec2& other);
	float GetMagnitude() const;
	float angleBetween(const vec2& other);
	friend std::ostream& operator<< (std::ostream& stream, const vec2& vector);
	friend vec2& operator+ (vec2& left, const vec2& right);
	friend vec2& operator- (vec2& left, const vec2& right);
	friend vec2& operator/ (vec2& left, const vec2& right);
	friend vec2& operator* (vec2& left, const vec2& right);
	
	vec2& operator+= (const vec2& other);
	vec2& operator-= (const vec2& other);
	vec2& operator/= (const vec2& other);
	vec2& operator*= (const vec2& other);

};