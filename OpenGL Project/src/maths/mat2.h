#pragma once
#include <iostream>
#include <array>
struct mat2 {
private:
	std::array<float, 4> m_valuesArray;
public:
	mat2();
	mat2(std::array<float, 4> matrixArray);
	mat2& add(const mat2& other);
	mat2& subtract(const mat2& other);
	mat2& multiply(const float other);
	mat2& multiply(const mat2& other);
	float getDeterminant();
	mat2 getInverse();
	friend std::ostream& operator<<(std::ostream& stream, const mat2& matrix);

};