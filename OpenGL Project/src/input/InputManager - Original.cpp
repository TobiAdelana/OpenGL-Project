#include "InputManager.h"

std::map<char*, Key> InputManager::keyboardKeys;
bool InputManager::keyboardButtons[1024];
// Temporary for Testing ------------------------
bool first = true, finish = false;
float timeStart;
float timeEnd;
float timeElapsed;
// ----------------------------------------------
void InputManager::RebindKey(const char* name, Key key)
{
	
}

float InputManager::GetAxis(char* name)
{
	Key result = keyboardKeys[name];
	double sensitivity = result.m_sensitivity / 9.5f;
	double gravity = result.gravity / 60.0f;

	// If the number is in the dead zone it is counted as 0
	if (keyboardButtons[result.m_positive] || keyboardButtons[result.m_altPositive])
	{
		
		if (result.snap && (result.m_axis < 0)) 
		{
			
			result.m_axis = 0;
		}
		result.m_axis = Math::Lerp(result.m_axis, 1, sensitivity);
	}
	if (keyboardButtons[result.m_negative] || keyboardButtons[result.m_altNegative])
	{
		
		if (result.snap && (result.m_axis > 0))
		{
			
			result.m_axis = 0;
		}
		result.m_axis = Math::Lerp(result.m_axis, -1, sensitivity);
	}
	else if (!(keyboardButtons[result.m_positive] || keyboardButtons[result.m_altPositive]))
	{
		result.m_axis = Math::Lerp(result.m_axis, 0, gravity);
		
	}
	if (abs(result.m_axis) < result.dead)
	{
		result.m_axis = 0;
		// std::cout << "dead" << std::endl;
		
	}

	// Temporary -------------

	result.m_axis = Math::Clamp(result.m_axis, -1.0f, 1.0f);

	float a = result.m_axis;
	float b = 0.9999999f;
	
	if ((a > 0) && (a < b))
	{
		if (first)
		{
			timeStart = Timer::getTime();
			first = false;
			std::cout << "First" << std::endl;
		}
	}
	else if ((a >= b) && (!finish))
	{
		
		timeEnd = Timer::getTime();
		timeElapsed = timeEnd - timeStart;
		std::cout << "Time: " << timeElapsed << std::endl;;
		finish = true;

	}
	
	//-----------
	keyboardKeys[name] = result;
	return result.m_axis;
	
	
}
void InputManager::Initalise()
{
	
	keyboardKeys.insert(std::pair<char*, Key>("Horizontal", Key(GLFW_KEY_D, GLFW_KEY_A, GLFW_KEY_RIGHT, GLFW_KEY_LEFT, 3, 0.01f, true, 3)));
	keyboardKeys.insert(std::pair<char*, Key>("Vertical", Key(GLFW_KEY_W, GLFW_KEY_S, GLFW_KEY_UP, GLFW_KEY_DOWN, 3, 0.01f, true, 3)));
	keyboardKeys.insert(std::pair<char*, Key>("Fire", Key(GLFW_MOUSE_BUTTON_1, GLFW_KEY_NONE, GLFW_KEY_NONE, GLFW_KEY_NONE, 1000, 0.01f, true, 10.0f)));
	keyboardKeys.insert(std::pair<char*, Key>("A", Key(GLFW_KEY_W, GLFW_KEY_S, GLFW_KEY_UP, GLFW_KEY_DOWN, 1000, 0.01f, true, 10.0f)));
	
}
/*
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (action)
	{
	case GLFW_PRESS:
		InputManager::keyboardButtons[key] = true;
		break;
	case GLFW_RELEASE:
		InputManager::keyboardButtons[key] = false;
		break;
	}
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	switch (action)
	{
	case GLFW_PRESS:
		InputManager::mouseButtons[button] = true;
		break;
	case GLFW_RELEASE:
		break;
	}
}
*/
