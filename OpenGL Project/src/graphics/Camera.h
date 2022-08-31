#pragma once
#include "Window.h"
#include "../maths/maths.h"
#include "../maths/vec3.h"
#include "../maths/mat4.h"
constexpr vec3 UP{ 0.0f, 1.0f, 0.0f };
class Camera
{
public:
	Camera(const vec3& position, const vec3& direction) : m_position(position), m_direction(direction) {};
	Camera(const vec3& position, const vec3& direction, float speed) 
		: m_position(position), m_direction(direction), m_speed(speed) {};
	void Rotate(const vec2& euler);
	mat4 GetViewMatrix() const;
	mat4 GetProjectionMatrix();
private:
	float m_speed = 0;
	float sensitivity = 0;
	vec3 m_position, m_direction;
};

