#pragma once
#include "../maths/vec2.h"
#include "../utils/Timer.h"
#include "../maths/maths.h"
#include "../graphics/window.h"
#include <GLFW/glfw3.h>
#include <map>
#include <array>
#include <vector>


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

using CursorPosCallback = void(*)(Window* win, vec2 position);
using KeyBindings = std::map<const char*, Key>;
// using KeyState = std::array<bool, InputManager::NUM_KEYS>;
class InputManager
{
public:
	static void Initalise();
	static void AddWindow(const Window& window);
	static void RebindKey(const char* name, const Key& key);
	static void SetCursorPosCallbackFunc(const Window& window, CursorPosCallback callbackFunc);
	static const Key& GetKey(const char* name);
	static float GetAxis(const char* name);
	static float GetAxisRaw(const char* name);

	static std::map<const char*, Key> keyboardKeys;
	static constexpr int NUM_KEYS = 1024;
	// static bool keyboardButtons[NUM_KEYS];
	static std::array<bool, NUM_KEYS> keyboardButtons;

private:
	static std::vector<Window> windows;
	static CursorPosCallback cursorPosCallbackFunc;

	static std::array<bool, GLFW_MOUSE_BUTTON_LAST + 1> mouseButtons;
	static std::array<bool, 14> joystickButtons[14];

};
