#include "mat2.h"


mat2::mat2() : mat2({1, 0, 0, 1}) {}
mat2::mat2(std::array<float, 4> matrixArray) {
	m_valuesArray = matrixArray;
	
}
mat2& mat2::add(const mat2& other) {
	for (int i = 0;i < 4;i++)
	{
		m_valuesArray[i] += other.m_valuesArray[i];
	}
	return *this;
}
mat2& mat2::subtract(const mat2& other) {
	for (int i = 0;i < 4;i++)
	{
		m_valuesArray[i] -= other.m_valuesArray[i];
	}
	return *this;
}
mat2& mat2::multiply(const float other)
{
	for (int i = 0;i < 4;i++)
	{
		m_valuesArray[i] *= other;
	}
	return *this;
}
mat2& mat2::multiply(const mat2& other)
{
	std::array<float, 4> result = {
		m_valuesArray[0] * other.m_valuesArray[0] + m_valuesArray[2] * other.m_valuesArray[1],
		m_valuesArray[1] * other.m_valuesArray[0] + m_valuesArray[3] * other.m_valuesArray[1],
		m_valuesArray[0] * other.m_valuesArray[2] + m_valuesArray[2] * other.m_valuesArray[3],
		m_valuesArray[1] * other.m_valuesArray[2] + m_valuesArray[3] * other.m_valuesArray[3] };

	m_valuesArray = result;
	return *this;
}
float mat2::getDeterminant() {
	float determinant = (m_valuesArray[0] * m_valuesArray[3]) - (m_valuesArray[2] * m_valuesArray[1]);
	return determinant;
}

mat2 mat2::getInverse()
{
	mat2 other = mat2({ m_valuesArray[3], -m_valuesArray[1], -m_valuesArray[2], m_valuesArray[0] });
	return other.multiply(1.0f / getDeterminant());

}
std::ostream& operator<<(std::ostream& stream, const mat2& matrix)
{
	stream << "[" << matrix.m_valuesArray[0] << ", " << matrix.m_valuesArray[1] << ", " << matrix.m_valuesArray[2] << ", " << matrix.m_valuesArray[3] << "]";
	return stream;
}