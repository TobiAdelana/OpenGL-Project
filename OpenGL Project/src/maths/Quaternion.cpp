#include "Quaternion.h"

Quaternion::Quaternion(float w, vec3 v)
{
	this -> w = w;
	this -> v = v;
}

Quaternion Quaternion::Identity()
{
	return Quaternion(1, vec3(0,0,0));
}

float Quaternion::GetMagnitude() const
{
	float mag = (w * w) + (v.x * v.x) + (v.y * v.y) + (v.z * v.z);

	return sqrt(mag);
}

Quaternion Quaternion::Inverse()
{
	Quaternion result(w, -v);
	return result;
}


Quaternion& Quaternion::Multiply(const Quaternion& left, const Quaternion& right)
{
	float rw = right.w * left.w - vec3::dot(left.v,right.v);
	vec3 vector;
	vector = right.w * left.v + left.w * right.v + vec3::cross(left.v, right.v);
	Quaternion result(rw, vector);
	return result;

}

Quaternion& Quaternion::Multiply(float factor, const Quaternion & quat)
{
	float w = quat.w * factor;
	vec3 vector = quat.v * factor;
	Quaternion result(w, vector);
	return result;
}

Quaternion & Quaternion::Divide(const Quaternion & quat, float factor)
{
	float w = quat.w / factor;
	float x = quat.v.x / factor;
	float y = quat.v.y / factor;
	float z = quat.v.z / factor;
	Quaternion result = Quaternion(w, vec3(x, y, z));
	return result;
}

Quaternion & Quaternion::TransformVector(const Quaternion& quat, const vec3 & vector)
{
	Quaternion p = Quaternion(0, vector);
	Quaternion norm = Quaternion::Normalise(quat);
	Quaternion res = norm * p * norm.Inverse();
	return res;
}

Quaternion & Quaternion::Normalise(const Quaternion & quat)
{
	Quaternion result = quat / quat.GetMagnitude();
	return result;
}

Quaternion & Quaternion::Add(const Quaternion & left, const Quaternion & right)
{
	float w = left.w + right.w;
	vec3 vec = left.v + right.v;
	Quaternion res(w, vec);
	return res;
}

Quaternion & Quaternion::EulerToQuat(const vec3 & other)
{
	float c1 = cos(other.y / 2);
	float c2 = cos(other.z / 2);
	float c3 = cos(other.x / 2);
	float s1 = sin(other.y / 2);
	float s2 = sin(other.z / 2);
	float s3 = sin(other.x / 2);

	float w = c1 * c2 * c3 - s1 * s2 * s3;
	float x = s1 * s2 * c3 + c1 * c2 * s3;
	float y = s1 * c2 * c3 + c1 * s2 * s3;
	float z = c1 * s2 * c3 - s1 * c2 * s3;
	Quaternion res(w, vec3(x, y, z));
	return res;
}

Quaternion Quaternion::Lerp(const Quaternion & start, const Quaternion & end, float factor)
{
	return (1 - factor) * start + factor * end;
}

Quaternion Quaternion::RotateAroundAxis(float radians, const vec3 axis)
{
	Quaternion result = Quaternion(cos(radians / 2.0f), vec3::normalise(axis) * sin(radians / 2.0f));
	return result;
}

mat3 Quaternion::ToMatrix()
{
	float elements[9];
	elements[0] = 1 - 2 * v.y * v.y - 2 * v.z * v.z;
	elements[1] = 2 * v.x * v.y - 2 * w * v.z;
	elements[2] = 2 * v.x * v.z + 2 * w * v.y;
	elements[3] = 2 * v.x * v.y + 2 * w * v.z;
	elements[4] = 1 - 2 * v.x * v.x - 2 * v.z * v.z;
	elements[5] = 2 * v.y * v.z - 2 * w * v.x;
	elements[6] = 2 * v.x * v.z - 2 * w * v.y;
	elements[7] = 2 * v.y * v.z + 2 * w * v.x;
	elements[8] = 1 - 2 * v.x * v.x - 2 * v.y * v.y;

	return mat3(elements);
}

Quaternion& operator* (float left, const Quaternion& right)
{
	Quaternion result = Quaternion::Multiply(left, right);
	return result;
}

Quaternion& operator* (const Quaternion& quat, float factor)
{
	Quaternion result = Quaternion::Multiply(factor, quat);
	return result;
}
Quaternion operator*(const Quaternion& left, const Quaternion& right)
{
	Quaternion result = Quaternion::Multiply(left, right);
	return result;

}
Quaternion& operator+ (const Quaternion& left, const Quaternion& right)
{
	Quaternion result = Quaternion::Add(left, right);
	return result;
}
Quaternion& operator/ (const Quaternion& quat, float factor)
{
	Quaternion result = Quaternion::Divide(quat, factor);
	return result;
}