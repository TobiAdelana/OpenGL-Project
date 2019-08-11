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
	
	result.x = x *other.elements[0 * 4] + y*other.elements[0 * 4 + 1] + z*other.elements[0 * 4 + 2] + w*other.elements[0 * 4 + 3];
	result.y = x *other.elements[1 * 4] + y*other.elements[1 * 4 + 1] + z*other.elements[1 * 4 + 2] + w*other.elements[1 * 4 + 3];
	result.z = x *other.elements[2 * 4] + y*other.elements[2 * 4 + 1] + z*other.elements[2 * 4 + 2] + w*other.elements[2 * 4 + 3];
	result.w = x *other.elements[3 * 4] + y*other.elements[3 * 4 + 1] + z*other.elements[3 * 4 + 2] + w*other.elements[3 * 4 + 3];
	y = result.y;
	x = result.x;
	z = result.z;
	w = result.w;
	return *this;
		
}
std::ostream& operator<< (std::ostream& stream, const vec4& vector)
{
	stream << "Vec4: (" << vector.x << ", " << vector.y << ", "<< vector.z << ", " << vector.w << ")";
	return stream;
}