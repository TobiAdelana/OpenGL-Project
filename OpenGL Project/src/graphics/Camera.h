#pragma once
#include "Window.h"
#include "../maths/maths.h"
#include "../maths/vec3.h"
#include "../maths/mat4.h"
class Camera
{
public:
	Camera(vec3 position, vec3 direction);
	Camera(vec3 position, vec3 direction, float speed);
	const vec3 UP = vec3(0.0f, 1.0f, 0.0f);
	float m_speed;
	vec3 m_position, m_direction;
	void Rotate(vec2& euler);
	mat4& GetViewMatrix() const;
	mat4& GetProjectionMatrix();
	
};

