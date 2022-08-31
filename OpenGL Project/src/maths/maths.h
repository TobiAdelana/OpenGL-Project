#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

namespace Math 
{
	float Lerp(float a, float b, float t);
	float Clamp(float value, float min, float max);
	float Min(float value, float min);
	float Max(float valuse, float max);
	inline float toRadians(float degrees)
	{
		return degrees * M_PI / 180.0f;
	}
	inline float toDegrees(float radians)
	{
		return radians * 180.0 / M_PI;
	}
};