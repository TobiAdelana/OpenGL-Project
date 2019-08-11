#include "vec4.h"

vec4::vec4()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 0.0f;
}

vec4::vec4(float x, float y, float z, float w): x(0.0f), y(0.0f), z(0.f), w(0.0f)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

vec4& vec4::multiply(const mat4& other)
{
	vec4 result;
	
	result.x = x *other.elements[0] + y*other.elements[4] + z*other.elements[8] + w*other.elements[12];
	result.y = x *other.elements[1] + y*other.elements[5] + z*other.elements[9] + w*other.elements[13];
	result.z = x *other.elements[2] + y*other.elements[6] + z*other.elements[10] + w*other.elements[14];
	result.w = x *other.elements[3] + y*other.elements[7] + z*other.elements[11] + w*other.elements[15];
	y = result.y;
	x = result.x;
	z = result.z;
	w = result.w;
	return *this;
		
}
vec4 vec4::multiply(const mat4& left, const vec4& right) 
{
	vec4 result;
	result.x = right.x * left.elements[0] + right.y * left.elements[4] + right.z * left.elements[8] + right.w * left.elements[12];
	result.y = right.x * left.elements[1] + right.y * left.elements[5] + right.z * left.elements[9] + right.w * left.elements[13];
	result.z = right.x * left.elements[2] + right.y * left.elements[6] + right.z * left.elements[10] + right.w * left.elements[14];
	result.w = right.x * left.elements[3] + right.y * left.elements[7] + right.z * left.elements[11] + right.w * left.elements[15];
	return result;
}
vec4 operator*(const mat4& left, const vec4& right)
{
	return vec4::multiply(left, right);
}
std::ostream& operator<< (std::ostream& stream, const vec4& vector)
{
	stream << "Vec4: (" << vector.x << ", " << vector.y << ", "<< vector.z << ", " << vector.w << ")";
	return stream;
}