#include "mat4.h"
#include "maths.h"
#include <iostream>

mat4::mat4(float elements[16])
{
	for (int i = 0; i < 16; i++)
	{
		this->elements[i] = elements[i];
	}

}
mat4& mat4::add(const mat4& other)
{
	for (int i = 0; i < 16; i++)
	{
		elements[i] += other.elements[i];
	}
	return *this;
}
mat4& mat4::multiply(const mat4 & other)
{

	float data[16];
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			float sum = 0.0f;
			for (int e = 0; e < 4; e++)
			{
				sum += elements[x + e * 4] * other.elements[e + y * 4];
			}
			data[x + y * 4] = sum;
		}
	}
	memcpy(elements, data, 16 * sizeof(*elements));
	return *this;
}
mat4& mat4::multiply(const float other)
{
	for (int i = 0; i < 16; i++)
		elements[i] *= other;
	return *this;
}

mat4& mat4::subtract(const mat4& other)
{
	for (int i = 0; i < 16; i++)
		elements[i] -= other.elements[i];
	return *this;
}

float* mat4::Data()
{
	return this->elements;
	// TODO: insert return statement here
}

mat4 mat4::identity()
{
	mat4 result;
	result.elements[0] = 1.0f;
	result.elements[5] = 1.0f;
	result.elements[10] = 1.0f;
	result.elements[15] = 1.0f;
	return result;
}

mat4 mat4::scale(float scale)
{
	mat4 result;
	result.elements[0] = scale;
	result.elements[5] = scale;
	result.elements[10] = scale;
	result.elements[15] = 1.0f;
	return result;
}

mat4 mat4::scale(vec3 scale)
{
	mat4 result;
	result.elements[0] = scale.x;
	result.elements[5] = scale.y;
	result.elements[10] = scale.z;
	result.elements[15] = 1.0f;
	return result;
}

mat4 mat4::lookAt(const vec3& eye, const vec3& look, const vec3& up) 
{
	/*mat4 result;
	vec3 zAxis = vec3::normalise(eye - look);
	vec3 xAxis = vec3::normalise(vec3::cross(up, xAxis));
	vec3 yAxis = vec3::cross(zAxis, xAxis);

	result.elements[0] = xAxis.x;
	result.elements[1] = xAxis.y;
	result.elements[2] = xAxis.z;
	result.elements[3] = -vec3::dot(xAxis, eye);
	result.elements[4] = yAxis.x;
	result.elements[5] = yAxis.y;
	result.elements[6] = yAxis.z;
	result.elements[7] = -vec3::dot(yAxis, eye);
	result.elements[8] = zAxis.x;
	result.elements[10] = zAxis.y;
	result.elements[11] = zAxis.z;
	result.elements[12] = -vec3::dot(zAxis,eye);
	result.elements[15] = 1.0f;*/


	/*tvec3<T, P> const f(normalize(center - eye));
	tvec3<T, P> const s(normalize(cross(f, up)));
	tvec3<T, P> const u(cross(s, f));

	tmat4x4<T, P> Result(1);
	Result[0][0] = s.x;
	Result[1][0] = s.y;
	Result[2][0] = s.z;
	Result[0][1] = u.x;
	Result[1][1] = u.y;
	Result[2][1] = u.z;
	Result[0][2] = -f.x;
	Result[1][2] = -f.y;
	Result[2][2] = -f.z;
	Result[3][0] = -dot(s, eye);
	Result[3][1] = -dot(u, eye);
	Result[3][2] = dot(f, eye);
	return Result;*/

	const vec3 f = vec3::normalise(look - eye);
	const vec3 s = vec3::normalise(vec3::cross(f, up));
	const vec3 u = vec3::cross(s, f);
	mat4 result = mat4::identity();
	result.elements[0] = s.x;
	result.elements[1] = u.x;
	result.elements[2] = -f.x;
	result.elements[4] = s.y;
	result.elements[5] = u.y;
	result.elements[6] = -f.y;
	result.elements[8] = s.z;
	result.elements[9] = u.z;
	result.elements[10] = -f.z;
	result.elements[12] = -vec3::dot(s, eye);
	result.elements[13] = -vec3::dot(u, eye);
	result.elements[14] = vec3::dot(f, eye);
	result.elements[15] = 1.0f;
	return result;



	/*result.elements[0] = s.x;
	result.elements[1] = u.x;
	result.elements[2] = -f.x;
	result.elements[4] = s.y;
	result.elements[5] = u.y;
	result.elements[6] = -f.y;
	result.elements[8] = s.z;
	result.elements[9] = u.z;
	result.elements[10] = -f.z;
	result.elements[12] = -vec3::dot(s, eye);
	result.elements[13] = -vec3::dot(u, eye);
	result.elements[14] = vec3::dot(f, eye);*/


	/*mat4 result = mat4::identity();
	vec3 f = vec3::normalise(look - eye);
	vec3 uOld = vec3::normalise(up);
	vec3 s = vec3::cross(f, uOld);
	vec3 u = vec3::cross(s, f);
	mat4 m = mat4::identity();
	m.elements[0] = s.x;
	m.elements[1] = u.x;
	m.elements[2] = -f.x;
	m.elements[4] = s.y;
	m.elements[5] = u.y;
	m.elements[6] = -f.y;
	m.elements[8] = s.z;
	m.elements[9] = u.z;
	m.elements[10] = -f.z;
	mat4 t = mat4::identity();
	t.elements[12] = -eye.x;
	t.elements[13] = -eye.y;
	t.elements[14] = -eye.z;*/
	
		
}
mat4 mat4::translate(const vec3 & other)
{
	mat4 result = mat4::identity();
	result.elements[12] = other.x;
	result.elements[13] = other.y;
	result.elements[14] = other.z;
	return result;
}
mat4 mat4::transpose(const mat4 & object)
{
	mat4 result;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			result.elements[i + j * 4] = object.elements[j + i * 4];

	return result;
}
mat4 mat4::ortho(float left, float right, float bottom, float top, float near, float far)
{
	/*result.elements[0] = 2.0f / (right - left);
	result.elements[3] = (left + right) / (left - right);
	result.elements[5] = 2.0f / (top - bottom);
	result.elements[7] = (bottom + top) / (bottom - top);
	result.elements[10] = 2.0f / (near - far);
	result.elements[11] = (far + near) / (near - far);
	result.elements[15] = 1.0f;*/

	mat4 result;
	result.elements[0] = 2.0f / (right - left);
	result.elements[5] = 2.0f / (top - bottom);
	result.elements[10] = 2.0f / (near - far);
	result.elements[12] = (left + right) / (left - right);
	result.elements[13] = (bottom + top) / (bottom - top);
	result.elements[14] = (near + far) / (near - far);
	result.elements[15] = 1.0f;
	return result;


}
mat4 mat4::perspective(float fov, float aspectRatio, float near, float far)
{
	mat4 result;
	float a = 1.0f / (tan(Math::toRadians(fov) * 0.5f));
	float b = a / aspectRatio;

	result.elements[0] = b;
	result.elements[5] = a;
	result.elements[10] = (near + far) / (near - far);
	result.elements[11] = -1.0f;
	result.elements[14] = (2.0f * near * far) / (near - far);
	
	return result;

}
std::ostream& operator<<(std::ostream& stream, const mat4& matrix)
{
	std::cout << "hello" << std::endl;
	stream << "[";
		for (int i = 0; i < 15; i++)
		{
				stream << matrix.elements[i] << ", ";
		}
		stream << matrix.elements[15] << "]";
		return stream;
}
mat4 operator+(mat4 left, const mat4& right)
{
	return left.add(right);
}
mat4 operator-(mat4 left, const mat4& right)
{
	return left.subtract(right);
}
mat4 operator-(mat4 right)
{
	for (int i = 0; i < 16; i++)
	{
		right.elements[i] = -right.elements[i];
	}
	return right;
}
mat4 operator*(mat4 left, const mat4& right)
{
	return left.multiply(right);
}
mat4 operator*(float left,  mat4 right)
{
	return right.multiply(left);
}

mat4& mat4::operator*=(const mat4& other)
{

	return multiply(other);
}
mat4& mat4::operator+=(const mat4& other)
{
	return add(other);
}
mat4& mat4::operator-=(const mat4& other)
{
	return subtract(other);
}

