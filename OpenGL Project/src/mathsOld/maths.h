#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

float toRadians(float degrees)
{
	return (float)((degrees * M_PI) / 180.0f);
}
float toDegrees(float radians)
{
	return (float)(radians * 180.0f / M_PI);
}