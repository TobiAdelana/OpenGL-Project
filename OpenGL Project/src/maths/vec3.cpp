#include "vec3.h"
#include <iostream>

vec3& vec3::cross(const vec3& other)
{
	float xComp = (y * other.z) - (z * other.y);
	float yComp = (z * other.x) - (x * other.z);
	float zComp = (x * other.y) - (y * other.x);
	this->x = xComp;
	this->y = yComp;
	this->z = zComp;
	*this = cross(*this, other);
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


vec3 vec3::normalise()
{
	return (*this / GetMagnitude());
}
vec3 vec3::normalise(const vec3& other)
{
	return (other / other.GetMagnitude());
}

vec3& vec3::add(const vec3& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}
vec3& vec3::subtract(const vec3 & other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}
vec3& vec3::multiply(const float other)
{
	x *= other;
	y *= other;
	z *= other;
	return *this;
}
vec3& vec3::divide(const float other)
{
	x /= other;
	y /= other;
	z /= other;
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

vec3 operator- (const vec3& right)
{
	return vec3(-right.x, -right.y, -right.z);

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
vec3 operator* (const float left, vec3 right)
{
	return right.multiply(left);
}
vec3 operator/ (vec3 left, const float right)
{
	return left.divide(right);
}


vec3& vec3::operator+= (const vec3& other)
{
	return add(other);
}
vec3& vec3::operator-= (const vec3& other)
{
	return subtract(other);
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


bool operator==(const vec3& lhs, const vec3& rhs)
{
	return(lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z);
}
bool operator!= (const vec3& lhs, const vec3& rhs)
{
	return !(lhs == rhs);
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

float vec3::GetMagnitude() const
{
	return sqrt((x*x) + (y*y) + (z*z));
}

float vec3::angleBetween(const vec3& other)
{
	return acos((dot(other)/(other.GetMagnitude() * GetMagnitude())));
}


