#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include "../maths/vec3.h"
#include "../maths/vec2.h"
#include "../maths/Quaternion.h"
#include "../maths/maths.h"
typedef unsigned int uint;
typedef char EnumType;

#define WINDOW_BORDERLESS 0x01
#define WINDOW_FULLSCREEN 0x02

class Window
{
public:
	
	GLFWwindow* m_window;
	uint m_width, m_height;
	EnumType tag;
	const char* m_title;
	bool m_fullscreen;
	float deltaTime = 0.0f, currentTime = 0.0f , lastTime = 0.0f;
	// Window(uint width, uint height, const char* title, EnumType tags);
	Window(uint width, uint height, const char* title, bool fullscreen);
	
	Window& SetFullScreen(bool fullscreen);
	Window& SetWindowSize(uint width, uint height);
	Window& SetCursorVisible(bool visible);
	
	vec2 GetMousePos();
	void clear();
	void cleanUp();
	bool isClosed() const;
	void update() const;

private:

	// GLfloat lastX = 0.0f, lastY = 0.0f;
	// void default_mouse_callback(GLFWwindow* window, double xpos, double ypos);
	bool init();
	class Cursor
	{
		vec2 position;

	} cursor;
};

