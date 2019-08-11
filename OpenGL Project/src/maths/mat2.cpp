#include "mat2.h"

mat2::mat2() {
	m_value[0] = 1;
	m_value[1] = 0;
	m_value[2] = 0;
	m_value[3] = 1;
	
}
mat2::mat2(const float value[4]) {
	
	for (int i = 0;i < 4;i++)
	{
		m_value[i] = value[i];
	}
}
mat2& mat2::add(const mat2& other) {
	for (int i = 0;i < 4;i++)
	{
		m_value[i] += other.m_value[i];
	}
	return *this;
}
mat2& mat2::subtract(const mat2& other) {
	for (int i = 0;i < 4;i++)
	{
		m_value[i] -= other.m_value[i];
	}
	return *this;
}
mat2& mat2::multiply(const float other)
{
	for (int i = 0;i < 4;i++)
	{
		m_value[i] *= other;
	}
	return *this;
}
mat2& mat2::multiply(const mat2& other)
{
	float result[4] = {
		m_value[0] * other.m_value[0] + m_value[2] * other.m_value[1],
		m_value[1] * other.m_value[0] + m_value[3] * other.m_value[1],
		m_value[0] * other.m_value[2] + m_value[2] * other.m_value[3],
		m_value[1] * other.m_value[2] + m_value[3] * other.m_value[3] };
	
	for (int i = 0;i < 4;i++)
	{
		m_value[i] = result[i];
	}
	return *this;
}
float mat2::getDeterminant() {
	determinant = (m_value[0] * m_value[3]) - (m_value[2] * m_value[1]);
	return determinant;
}

mat2 mat2::inverse()
{
	mat2 other = mat2(new float[4]{ m_value[3], -m_value[1], -m_value[2], m_value[0] });
	return other.multiply(1.0f / getDeterminant());

}
std::ostream& operator<<(std::ostream& stream, const mat2& matrix)
{
	stream << "[" << matrix.m_value[0] << ", " << matrix.m_value[1] << ", " << matrix.m_value[2] << ", " << matrix.m_value[3] << "]";
	return stream;
}