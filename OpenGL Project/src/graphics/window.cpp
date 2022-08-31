#include "Window.h"
#include <iostream>
#include <functional>

#ifdef DEBUG
#define log(x) std::cout << x << std::endl
#else
#define log(x) (void)0
#endif


Window::Window(uint width, uint height, const std::string& title, bool fullscreen) 
	: m_width(width), m_height(height), m_title(title), m_fullscreen(fullscreen)
{
	if (!init())
	{
		glfwTerminate();
		throw std::exception("Window could not be initialised");
	}
	glfwSetWindowUserPointer(m_window, this);
}

Window::~Window()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}




bool Window::init()
{
	currentTime = 0.0f;
	deltaTime = 0.0f;
	lastTime = 0.0f;
	if (!glfwInit())
	{
		std::cout << "GLFW could not be initalised" << std::endl;
		return false;
	}
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	glfwWindowHint(GLFW_DECORATED, GL_TRUE);
	m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), m_fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
	log(mode->width << ", " << mode -> height);
	glfwSetWindowPos(m_window, (mode->width - m_width) /2 , (mode->height - m_height) /2);
	if (!m_window)
	{
		std::cout << "Could not create GLFW window" << std::endl;
		return false;
	}

	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(1);
	std::cout << "OpenGL: " << glGetString(GL_VERSION) << std::endl;

	if (glewInit() != GLEW_OK) 
	{
		std::cout << "Could not initialise GLEW " << std::endl;
		return false;
	}
	return true;
}

bool Window::isClosed() const
{
	return glfwWindowShouldClose(m_window);
}

void Window::ClearScreen()
{	
	int width, height;
	glfwGetFramebufferSize(m_window, &width, &height);
	m_width = width;
	m_height = height;

	glViewport(0, 0, m_width, m_height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	currentTime = glfwGetTime();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;
}
void Window::update() 
{
	old_cursor_pos = cursor_pos;
	glfwSwapBuffers(m_window);
	glfwPollEvents();
	double x, y;
	glfwGetCursorPos(m_window, &x,&y);
	cursor_pos.x = x;
	cursor_pos.y = y;
}



void Window::SetWindowSize(uint width, uint height) 
{
	
	glfwSetWindowSize(m_window, width, height);
	m_width = width;

	m_height = height;

}

void Window::SetCursorVisible(bool visible)
{
	glfwSetInputMode(m_window, GLFW_CURSOR, visible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
}
void default_callback(GLFWwindow* gWindow, int key, int scancode, int action, int mods)
{
	Window& win = *static_cast<Window*>(glfwGetWindowUserPointer(gWindow));
	win.keys[key] = (action != GLFW_RELEASE);
}

uint Window::GetHeight() const
{
	return m_height;
}

uint Window::GetWidth() const
{
	return m_width;
}

void Window::SetCursorEnabled(bool enable)
{
	m_enabled = enable;
	glfwSetInputMode(m_window, GLFW_CURSOR, enable ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
}
vec2 Window::GetMousePos()
{
	return cursor_pos;
}

vec2 Window::GetDeltaPos()
{
	return cursor_pos - old_cursor_pos;
}

/*
void default_mouse_callback(GLFWwindow* window, double xpos, double ypos)
{

	double lastX = 0.0,  lastY = 0.0;
	vec3 UP(0.0f, 0.0f, 1.0f);
	vec3 direction(0.0, 1.0f, 0.0f);
	bool firstMouse = true;

	if (firstMouse)
	{

		lastX = (GLfloat)xpos;
		lastY = (GLfloat)ypos;
		firstMouse = false;
	}
	
	double xOffset = xpos - lastX;
	double yOffset = ypos - lastY;

	float sensitivity = 78.0f * deltaTime;

	Quaternion result = Quaternion::RotateAroundAxis(Math::toRadians(xOffset) * sensitivity, direction) * Quaternion::RotateAroundAxis(Math::toRadians(yOffset), direction);
	lastX = xpos;
	lastY = ypos;

	vec3 newDirection = vec3::normalise(Quaternion::TransformVector(result, direction).v);
	direction = newDirection;
}

*/