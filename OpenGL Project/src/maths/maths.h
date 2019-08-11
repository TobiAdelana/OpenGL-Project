#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

#define MATH_PI 3.14159265358979323846


struct Math 
{
public:
	static float Lerp(float a, float b, float t);
	static float Clamp(float value, float min, float max);
	static float Min(float value, float min);
	static float Max(float valuse, float max);

	static inline float toRadians(float degrees)
	{
		return (float)((degrees * M_PI) / 180.0f);
	}

	static inline float toDegrees(float radians)
	{
		return (float)(radians * 180.0f / M_PI);
	}
};