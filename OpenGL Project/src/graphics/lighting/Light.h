#pragma once
#include "../../maths/vec3.h"
#include "../../maths/vec4.h"

enum class LightType
{
	DIRECTION, POINT, SPOT
};

struct Light
{
	vec3 m_position{};
	LightType type = LightType::POINT;
	vec3 m_colour = {};
	vec3 m_coneDirection{};
	float m_coneAngle;
	float m_intensity;
	float m_attenuation;
	float m_ambientCoefficient;

};


