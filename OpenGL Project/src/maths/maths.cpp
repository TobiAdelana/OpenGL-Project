#include "maths.h"

float Math::Lerp(float a, float b, float t)
{
	return a * (1 - t) + b * t;
	
}
float Math::Clamp(float value, float min, float max)
{
	if (value > max)
		value = max;
	else if (value < min)
		value = min;
	return value;
}
float Math::Min(float value, float min)
{
	if (value > min)
		value = min;
	return value;
}
float Math::Max(float value, float max)
{
	if (value < max)
		value = max;
	return value;
}
