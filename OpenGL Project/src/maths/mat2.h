#pragma once
#include <iostream>
#include <array>
struct mat2 {
private:
	float m_value[4];
	float determinant;
public:
	mat2();
	mat2(const float value[4]);
	mat2& add(const mat2& other);
	mat2& subtract(const mat2& other);
	mat2& multiply(const float other);
	mat2& multiply(const mat2& other);
	float getDeterminant();
	mat2 inverse();
	friend std::ostream& operator<<(std::ostream& stream, const mat2& matrix);

};