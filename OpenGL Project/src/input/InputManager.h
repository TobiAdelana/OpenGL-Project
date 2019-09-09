#pragma once
#include "../maths/vec2.h"
#include <GLFW\glfw3.h>
#include "../utils/Timer.h"
#include "../maths/maths.h"
#include <map>


struct Key
{
	Key(int positive, int negative, float axis) 
		: m_positive(positive), m_negative(negative) {};
	Key() {};
	Key(int positive, int negative, int altPositive, int altNegative, 
		int gravity, float dead, bool snap,  float sensitivity, bool invert = false) :
		m_positive(positive), m_negative(negative), m_altNegative(altNegative), 
		m_altPositive(altPositive), m_sensitivity(sensitivity)
	{
		this->gravity = gravity;
		this->dead = dead;
		this->snap = snap;
		this->invert = invert;
		m_axis = 0;
	};

	int m_positive		= GLFW_KEY_UNKNOWN;
	int m_negative		= GLFW_KEY_UNKNOWN;
	int m_altPositive	= GLFW_KEY_UNKNOWN;
	int m_altNegative	= GLFW_KEY_UNKNOWN;
	int gravity = 0;
	float dead = 0.0;
	bool snap = false;
	bool invert = false;
	float m_sensitivity;
	float m_axis;
};
class InputManager
{
public:
	static void Initalise();
	static void RebindKey(char* name, const Key& key);
	static const Key& GetKey(char* name);
	static float GetAxis(char* name);
	static float GetAxisRaw(char* name);

	static std::map<char*, Key> keyboardKeys;
	static bool keyboardButtons[1024];

private:
	static bool mouseButtons[GLFW_MOUSE_BUTTON_LAST + 1];
	static bool joystickButtons[14];

};
