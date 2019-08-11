#include "Window.h"
#include <iostream>
#define log(x) std::cout << x << std::endl

Window::Window(uint width, uint height, const char* title, bool fullscreen) 
	: m_width(width), m_height(height), m_title(title), m_fullscreen(fullscreen)
{
	if (!init())
	{
		glfwTerminate();
	}
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
	m_window = glfwCreateWindow(m_width, m_height, m_title, m_fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
	log(mode->width << ", " << mode -> height);
	glfwSetWindowPos(m_window, (mode->width - m_width) * 0.5f, (mode->height - m_height) * 0.5f);
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

void Window::clear()
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
void Window::cleanUp()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}
void Window::update() const 
{
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}


Window& Window::SetFullScreen(bool fullscreen)
{
	if (fullscreen == m_fullscreen)
		return *this;
	glfwDestroyWindow(m_window);
	Window(m_width, m_height, m_title, fullscreen);
	m_fullscreen = fullscreen;

	return *this;
}

Window& Window::SetWindowSize(uint width, uint height) 
{
	
	glfwSetWindowSize(m_window, width, height);
	m_width = width;
	m_height = height;

	return *this;
}

Window& Window::SetCursorVisible(bool visible)
{
	glfwSetInputMode(m_window, GLFW_CURSOR, visible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
	return *this;
}
vec2 Window::GetMousePos() 
{
	double xpos, ypos;
	glfwGetCursorPos(m_window, &xpos, &ypos);
	return vec2((float)xpos, (float)ypos);
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