#pragma once
#include "../maths/vec2.h"
#include <GLFW\glfw3.h>
#include "../utils/Timer.h"
#include "../maths/maths.h"
#include <map>
#define GLFW_KEY_NONE GLFW_KEY_UNKNOWN


struct Key
{
	Key(int positive, int negative, float axis) : m_positive(positive), m_negative(negative)
	{
		
	};
	Key() 
	{
		m_positive = GLFW_KEY_NONE;
		m_negative = GLFW_KEY_NONE;
		m_altPositive = GLFW_KEY_NONE;
		m_altNegative = GLFW_KEY_NONE;
		gravity = 0;
		dead = 0;
		m_axis = 0;
		snap = false;
	};
	Key(int positive, int negative, int altPositive, int altNegative, int gravity, float dead, bool snap,  float sensitivity, bool invert = false) : m_positive(positive), m_negative(negative), m_altNegative(altNegative), m_altPositive(altPositive), m_sensitivity(sensitivity)
	{
		this->gravity = gravity;
		this->dead = dead;
		this->snap = snap;
		this->invert = invert;
		m_axis = 0;
	};
	int m_positive, m_negative;
	int m_altPositive, m_altNegative;
	int gravity;
	float dead;
	bool snap, invert = false;
	float m_sensitivity;
	float m_axis;
};
class InputManager
{
public:
	static void Initalise();
	static void RebindKey(char* name, Key key);
	static Key GetKey(char* name);
	static float GetAxis(char* name);
	static float GetAxisRaw(char* name);
	static std::map<char*, Key> keyboardKeys;
	static bool keyboardButtons[1024];

private:
	static bool mouseButtons[GLFW_MOUSE_BUTTON_LAST + 1];
	static bool joystickButtons[14];

};
