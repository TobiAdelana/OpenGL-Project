#include "Camera.h"

Camera::Camera(vec3 position, vec3 direction)
{
	
	m_position = position;
	m_direction = direction;
}

Camera::Camera(vec3 position, vec3 direction, float speed)
{
	m_position = position;
	m_direction = direction;
	m_speed = speed;
}

							 // x = yaw, y = pitch
void Camera::Rotate(vec2& euler)
{
	vec3 front;
	front.x = cos(Math::toRadians(euler.x)) * cos(Math::toRadians(euler.y));
	front.y = sin(Math::toRadians(euler.y));
	front.z = sin(Math::toRadians(euler.x)) * cos(Math::toRadians(euler.y));
	m_direction = vec3::normalise(front);
}



mat4& Camera::GetViewMatrix() const
{
	return mat4::lookAt(m_position, m_direction + m_position, UP);
}