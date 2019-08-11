#include "vec3.h"
#include <iostream>

vec3::vec3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	magnitude = 0.0f;
}

vec3::vec3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	updateMagnitude();
}

vec3::vec3(const vec2 start, float z) : z(0.0f)
{
	vec3(start.x, start.y, z);
	updateMagnitude();
}
vec3& vec3::cross(const vec3& other)
{
	float xComp = (y * other.z) - (z * other.y);
	float yComp = (z * other.x) - (x * other.z);
	float zComp = (x * other.y) - (y * other.x);
	this->x = xComp;
	this->y = yComp;
	this->z = zComp;
	*this = cross(*this, other);
	updateMagnitude();
	return *this;
}
vec3 vec3::cross(const vec3& left, const vec3& right)
{
	float xComp = (left.y * right.z) - (left.z * right.y);
	float yComp = (left.z * right.x) - (left.x * right.z);
	float zComp = (left.x * right.y) - (left.y * right.x);
	return vec3(xComp, yComp, zComp);
}
float vec3::dot(const vec3& left, const vec3& right)
{
	return (left.x * right.x) + (left.y * right.y) + (left.z * right.z);
}

void vec3::updateMagnitude()
{
	magnitude = sqrt(x*x + y*y + z*z);
}
vec3 vec3::normalise()
{
	return (*this / magnitude);
}
vec3 vec3::normalise(const vec3& other)
{
	std::cout << "---------------------------" << std::endl;
	std::cout << other.magnitude << std::endl;
	return (other / other.magnitude);
}

vec3& vec3::add(const vec3& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	updateMagnitude();
	return *this;
}
vec3& vec3::subtract(const vec3 & other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	updateMagnitude();
	return *this;
}
vec3& vec3::multiply(const float other)
{
	x *= other;
	y *= other;
	z *= other;
	updateMagnitude();
	return *this;
}
vec3& vec3::divide(const float other)
{
	x /= other;
	y /= other;
	z /= other;
	updateMagnitude();
	return *this;
}
//vec3& vec3::multiply(const vec3 & other)
//{
//	x *= other.x;
//	y *= other.y;
//	z *= other.z;
//	updateMagnitude();
//	return *this;
//}
//vec3& vec3::divide(const vec3 & other)
//{
//	x /= other.x;
//	y /= other.y;
//	z /= other.z;
//	updateMagnitude();
//	return *this;
//}
vec3 operator+ (vec3 left, const vec3& right)
{
	return left.add(right);
}
vec3 operator- (vec3 left, const vec3& right)
{
	return left.subtract(right);
}
//vec3 operator/ (vec3 left, const vec3& right)
//{
//	return left.divide(right);
//}
//vec3 operator* (vec3 left, const vec3& right)
//{
//	return left.multiply(right);
//}
vec3 operator* (vec3 left, const float right)
{
	return left.multiply(right);
}
vec3 operator/ (vec3 left, const float right)
{
	return left.divide(right);
}

vec3& vec3::operator+= (const vec3& other)
{
	add(other);
	return *this;
}
vec3& vec3::operator-= (const vec3& other)
{
	subtract(other);
	return *this;
}
vec3& vec3::operator*= (const float other)
{
	return multiply(other);
}
vec3& vec3::operator/= (const float other)
{
	return divide(other);
}

//vec3& vec3::operator/= (const vec3& other)
//{
//	divide(other);
//	return *this;
//}
//vec3& vec3::operator*= (const vec3& other)
//{
//	multiply(other);
//	return *this;
//}
bool vec3::operator== (const vec3& other)
{
	return (x == other.x) && (y == other.y) && (z == other.z);
}
bool vec3::operator!= (const vec3& other)
{
	return !(*this == other);
}
std::ostream& operator<<(std::ostream& stream, const vec3& vector)
{
	stream << "Vec3 : {" << vector.x << ", " << vector.y << ", " << vector.z << "}";
	return stream;
}

float vec3::dot(const vec3& other)
{

	return (x * other.x) + (y * other.y) + (z * other.z);
}

float vec3::angleBetween(const vec3& other)
{
	return acos((dot(other)/(other.magnitude * magnitude)));
}


