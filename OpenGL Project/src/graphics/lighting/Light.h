#pragma once
#include "../../maths/vec3.h"
#include "../../maths/vec4.h"

enum LightType
{
	DIRECTION, POINT, SPOT
};



struct Light
{
	vec3 m_position;
	LightType type;
	vec3 m_colour, m_coneDirection;
	float m_coneAngle, m_intensity, m_attenuation, m_ambientCoefficient;

};

struct SunLight : Light
{
	vec3 colour, direction;
};



