#include "InputManager.h"
#include <iostream>
std::map<char*, Key> InputManager::keyboardKeys;
bool InputManager::keyboardButtons[1024];
// Temporary for Testing ------------------------
bool first = true, finish = false;
float timeStart;
float timeEnd;
float timeElapsed;
// ----------------------------------------------
void InputManager::RebindKey(char* name, const Key& key)
{
	keyboardKeys[name] = key;
}
float InputManager::GetAxis(char* name)
{
	Key& result = keyboardKeys[name];
	double sensitivity = result.m_sensitivity * Timer::GetDeltaTime();
	double gravity = result.gravity * Timer::GetDeltaTime();

	// If the number is in the dead zone it is counted as 0
	
	if (keyboardButtons[result.m_positive] || keyboardButtons[result.m_altPositive])
	{
		
		result.m_axis += sensitivity;
		if (result.snap && (result.m_axis < 0)) 
		{
			result.m_axis = 0;
		}
	}
	else if (keyboardButtons[result.m_negative] || keyboardButtons[result.m_altNegative])
	{
		
		result.m_axis -= sensitivity;
		if (result.snap && (result.m_axis > 0))
		{
			result.m_axis = 0;
		}
	}
	else if (!(keyboardButtons[result.m_positive] || keyboardButtons[result.m_altPositive]))
	{
		
		if (result.m_axis < 0)
		{
			result.m_axis += gravity;
			result.m_axis = Math::Min(result.m_axis, 0);
		}
		else if (result.m_axis > 0)
		{
			result.m_axis -= gravity;
			result.m_axis = Math::Max(result.m_axis, 0);
		}
	}
	if (abs(result.m_axis) < result.dead)
	{
		result.m_axis = 0;
	}
	result.m_axis = Math::Clamp(result.m_axis, -1.0f, 1.0f);



	// Temporary -------------
	float a = result.m_axis;
	float b = 1.0f;
	
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
	return result.m_axis;
	
	
}
float InputManager::GetAxisRaw(char * name)
{
	if (keyboardKeys[name].m_axis > 0.0f)
		return 1.0f;
	if (keyboardKeys[name].m_axis < 0.0f)
		return -1.0f;
	return 0.0f;
}
const Key& InputManager::GetKey(char* name)
{
	return keyboardKeys[name];
}
void InputManager::Initalise()
{
	
	keyboardKeys.insert(std::pair<char*, Key>("Horizontal", Key(GLFW_KEY_D, GLFW_KEY_A, GLFW_KEY_RIGHT, GLFW_KEY_LEFT, 5, 0.01f, true, 5)));
	keyboardKeys.insert(std::pair<char*, Key>("Vertical", Key(GLFW_KEY_W, GLFW_KEY_S, GLFW_KEY_UP, GLFW_KEY_DOWN, 3, 0.01f, true, 3)));
	keyboardKeys.insert(std::pair<char*, Key>("Fire", Key(GLFW_MOUSE_BUTTON_1, GLFW_KEY_UNKNOWN, GLFW_KEY_UNKNOWN, GLFW_KEY_UNKNOWN, 1000, 0.01f, true, 10.0f)));
	keyboardKeys.insert(std::pair<char*, Key>("A", Key(GLFW_KEY_W, GLFW_KEY_S, GLFW_KEY_UP, GLFW_KEY_DOWN, 1000, 0.01f, true, 10.0f)));
	
}



