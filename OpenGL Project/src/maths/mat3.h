#pragma once
class mat3
{
public:
	mat3(float elements[9]);
	mat3();
	~mat3();


	mat3& multiply(const mat3& other);
	mat3& multiply(const float other);

	mat3& add(const mat3& other);
	mat3& subtract(const mat3& other);
	void SetElements(const float elements[9]);
	float* GetElements();

	friend mat3 operator+(mat3 left, const mat3& right);
	friend mat3 operator*(mat3 left, const mat3& right);
	friend mat3 operator*(float left, mat3 right);
	friend mat3 operator-(mat3 left, const mat3& right);
	friend mat3 operator-(mat3 right);
private:
	float elements[9];
};

