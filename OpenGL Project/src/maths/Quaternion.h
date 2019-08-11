#pragma once
#include "vec3.h"
#include "mat3.h"

struct Quaternion
{
	float w;
	vec3 v;
	mat3 ToMatrix();

public:
	Quaternion(float w, vec3 v);
	static Quaternion& Multiply			(const Quaternion& left, const Quaternion& right);
	static Quaternion& Multiply			(float factor, const Quaternion& quat);
	static Quaternion& Divide			(const Quaternion& quat, float factor);
	static Quaternion& Normalise		(const Quaternion& quat);
	static Quaternion& Add				(const Quaternion& left, const Quaternion& right);
	static Quaternion& EulerToQuat		(const vec3& other);
	static Quaternion Lerp				(const Quaternion& start, const Quaternion& end, float factor);
	static Quaternion Identity			();
	static Quaternion RotateAroundAxis	(float radians, vec3 axis);
	static Quaternion& TransformVector	(const Quaternion& quat, const vec3& vector);
	
	
	friend Quaternion& operator*(float left, const Quaternion& right);
	friend Quaternion& operator*(const Quaternion& quat, float factor);
	friend Quaternion operator*(const Quaternion& quat, const Quaternion& right);
	friend Quaternion& operator/(const Quaternion& quat, float factor);
	friend Quaternion& operator+(const Quaternion& left, const Quaternion& right);
	
	// Only true if the quaternion is a unit quaternion
	Quaternion Inverse();
	float GetMagnitude() const;
	vec3& ToEulerAngle(const Quaternion& quat);
};