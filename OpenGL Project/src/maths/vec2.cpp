#include "vec2.h"
#include <cassert>
float vec2::GetMagnitude() const
{
	return sqrt((x * x) + (y * y));
}

float vec2::dot(const vec2& other)
{
	return (x * other.x) + (y * other.y);
}

// Precond: this->magnitude != 0 and other->magnitude != 0
// Returns the angle between this and other in radians
float vec2::angleBetween(const vec2& other)
{
	assert(GetMagnitude() != 0 && other.GetMagnitude() != 0);
	return acos(dot(other) / (GetMagnitude() * other.GetMagnitude())); 
}
vec2 & vec2::operator+=(const vec2 & other)
{
	add(other);
	return *this;
}
vec2 & vec2::operator-=(const vec2 & other)
{
	subtract(other);
	return *this;
}
vec2 & vec2::operator/=(const vec2 & other)
{
	divide(other);
	return *this;
}
vec2 & vec2::operator*=(const vec2 & other)
{
	multiply(other);
	return *this;
}
std::ostream& operator<< (std::ostream& stream, const vec2& vector)
{
	stream << "Vec2: {" << vector.x << ", " << vector.y <<"}";
	return stream;
}

vec2& vec2::add(const vec2& other)
{
	x += other.x;
	y += other.y;
	return *this;
}
vec2& vec2::subtract(const vec2& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}
vec2& vec2::multiply(const vec2& other)
{
	x *= other.x;
	y *= other.y;
	return *this;
}
vec2& vec2::divide(const vec2& other)
{
	x /= other.x;
	y /= other.y;
	return *this;
}
vec2& operator+ (vec2& left, const vec2& right)
{
	return left.add(right);
}
vec2& operator- (vec2& left, const vec2& right)
{
	return left.subtract(right);
}
vec2& operator/ (vec2& left, const vec2& right)
{
	return left.divide(right);
}
vec2& operator* (vec2& left, const vec2& right)
{
	return left.multiply(right);
}

