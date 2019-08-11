#include "mat3.h"



mat3::mat3(float elements[9])
{
	for (int i = 0; i < 9; i++)
		this->elements[i] = elements[i];
}

mat3::mat3()
{
	for (int i = 0; i < 9; i++)
		this->elements[i] = 0;
}


mat3::~mat3()
{
	
}

float * mat3::GetElements()
{

	return elements;
}

