#include "Camera.h"

#include <functional>
// x = yaw, y = pitch
void Camera::Rotate(const vec2& euler)
{
	vec3 front = {
			cos(Math::toRadians(euler.x)) * cos(Math::toRadians(euler.y)),
			sin(Math::toRadians(euler.y)),
			sin(Math::toRadians(euler.x)) * cos(Math::toRadians(euler.y)) };
	m_direction = vec3::normalise(front);

}



mat4 Camera::GetViewMatrix() const
{
	return mat4::lookAt(m_position, m_direction + m_position, UP);
}