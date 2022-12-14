#pragma once

#include <iostream>
#include <map>

#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include "../maths/vec3.h"
#include "../maths/vec2.h"
#include "../maths/Quaternion.h"
#include "../maths/maths.h"


using uint = unsigned int;
class Window
{
public:
	GLFWwindow* m_window;
	uint m_width, m_height;
	float deltaTime = 0.0f, currentTime = 0.0f , lastTime = 0.0f;
	// Window(uint width, uint height, const char* title, EnumType tags);
	Window(uint width, uint height, const std::string& title, bool fullscreen);
	Window(const Window& w)				= delete;
	Window& operator=(const Window&)	= delete;
	~Window();
	
	void SetWindowSize(uint width, uint height);
	void SetCursorVisible(bool visible);
	
	//void SetWindowCallback(CursorPosCallback callback);
	uint GetHeight() const;
	uint GetWidth() const;
	void SetCursorEnabled(bool enable);
	vec2 GetMousePos();
	vec2 GetDeltaPos();
	void ClearScreen();
	bool isClosed() const;
	void update();

	bool keys[GLFW_KEY_LAST + 1] = {};
private:

	// GLfloat lastX = 0.0f, lastY = 0.0f;
	// void default_mouse_callback(GLFWwindow* window, double xpos, double ypos);
	bool m_fullscreen = false;
	std::string m_title;
	bool init();
	bool m_enabled;
	vec2 cursor_pos = { 0, 0 };
	vec2 old_cursor_pos = { 0,0 };
	enum class WindowBorderType
	{
		WINDOW_BORDERLESS, WINDOW_FULLSCREEN
	} m_windowBorderType;
};

