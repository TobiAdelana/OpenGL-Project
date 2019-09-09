
#include "src\graphics\Window.h"
#include "src\utils\fileUtils.h"
#include "src\shaders\shader.h"
#include "src\maths\mat4.h"
#include "src\utils\Timer.h"
#include "src\input\InputManager.h"
#include "src\shaders\Uniform.h"
#include "src\graphics\Material.h"
#include "src\graphics\Camera.h"
#include "src\maths\maths.h"
#include "src\graphics\Mesh.h"
#include "src\maths\Quaternion.h"
#include "src\graphics\lighting\Light.h"


#ifdef DEBUG
#define log(x) std::cout << x << std::endl
#else
#define log(x) (void)0
#endif

bool keys[1024];
bool firstMouse = true;
GLfloat lastX = 0.0f, lastY = 0.0f;
GLfloat pitch = -45.0f, yaw = -90.0f;
Camera cam{ {},{} };
bool isVisible = false;
vec3 up = vec3(0.0f, 1.0f, 0.0f);
vec3 position = vec3(1.2f, 1.0f, 1.2f);
vec3 direction = vec3::normalise(vec3(-1.2f, -1.2f, 0.0f));
vec3 cameraRight = vec3::cross(up, direction);
vec3 cameraUp = vec3::cross(direction, cameraRight);
Window window(640, 480, "The title", false);


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	
	if (firstMouse)
	{

		lastX = (GLfloat) xpos;
		lastY = (GLfloat) ypos;
		firstMouse = false;
	}
	double xoffset = xpos - lastX;
	double yoffset = lastY - ypos;
	lastX = (GLfloat) xpos;
	lastY = (GLfloat) ypos;
	// auto offset = ::window.GetDeltaPos();

	float sensitivity = 40.0f * ::window.deltaTime;
	xoffset *= sensitivity;
	yoffset *= sensitivity;
	// 40.0f * ::window.deltaTime * offset;
	yaw += (GLfloat) xoffset;
	pitch += (GLfloat) yoffset;
	// camera.angle += offset
	if (pitch < -89.0f)
		pitch = -89.0f;
	if (pitch > 89.0f)
		pitch = 89.0f;
	// Math.clamp(camera.angle.x, -89, 89);
	vec3 front;

	float radYaw = Math::toRadians(yaw);
	float radPitch = Math::toRadians(pitch);
	float cosPitch = cos(radPitch);
	front.x = cos(radYaw) * cosPitch;
	front.y = sin(radPitch);
	front.z = sin(radYaw) * cosPitch;
	// camera.rotate(camera.angle);
	direction = vec3::normalise(front);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (action)
	{
	case GLFW_PRESS:
		keys[key] = true;
		InputManager::keyboardButtons[key] = true;
		break;
	case GLFW_RELEASE:
		keys[key] = false;
		InputManager::keyboardButtons[key] = false;
		if (key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(window, true);
		if (key == GLFW_KEY_V)
		{
			glfwSetCursorPosCallback(window, isVisible ? mouse_callback : NULL);
			isVisible = !isVisible;
			firstMouse = true;
		}
		break;
	}

}

void do_movement(float deltaTime, vec3& position, vec3 direction, const vec3& up)
{

	float movementSpeed = 2.0f * deltaTime;
	direction.y = 0.0f;

	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
		position += direction * movementSpeed;
	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
		position -= direction * movementSpeed;
	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
		position -= vec3::normalise(vec3::cross(direction, up)) * movementSpeed;
	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
		position += vec3::normalise(vec3::cross(direction, up)) * movementSpeed;

}

int main()
{

	glfwSetCursorPosCallback(window.m_window, mouse_callback);
	glfwSetKeyCallback(window.m_window, key_callback);

	window.SetCursorVisible(isVisible);

	std::vector<Vertex> vertices = {
		Vertex(vec3(-0.5f, 0.0f, 0.5f),		vec3(0.0f, 1.0f, 0.0f)), // Top-left
		Vertex(vec3(0.5f,  0.0f,   0.5f),	vec3(0.0f,  1.0f,  0.0f)),// Top-right
		Vertex(vec3(0.5f,  0.0f,  -0.5f),	vec3(0.0f,  1.0f,  0.0f)),// Bottom-right
		Vertex(vec3(-0.5f,  0.0f,  -0.5f),	vec3(0.0f,  1.0f,  0.0f))// Bottom-left
	};
	std::vector<GLuint> indices = {
		0, 1, 2, 2, 3, 0
	};
	Mesh m(vertices, indices);
	Mesh chess;
	if (!chess.LoadObj("chess.obj"))
		log("Not working");
	// Normal Data

	// Position Data

	const std::string vertex = FileUtils::LoadTextFile("src/shaders/default.vs");
	const std::string fragment = FileUtils::LoadTextFile("src/shaders/default.fs");
	Shader defaultShader(vertex, fragment);

	mat4 projection = mat4::perspective(45.0f, 640.0f / 480.0f, 0.3f, 10.0f);
	mat4 view = mat4::lookAt(position, position + direction, vec3(0.0f, 1.0f, 0.0f));
	mat4 model = mat4::scale(4.0f);
	defaultShader.UniformMatrix4f("projection", 1, GL_FALSE, projection);
	defaultShader.UniformMatrix4f("view", 1, GL_FALSE, view);
	defaultShader.UniformMatrix4f("model", 1, GL_FALSE, model);

	Light light;
	light.m_position	=	vec3( 0.0f, 1.0f, 0.0f);
	light.m_colour		=	vec3(0.5f, 0.5f, 0.5f );
	defaultShader.UniformLight("light", light);
	defaultShader.Uniform3f("material.ambientColour", vec3(0.25f, 0.25f, 0.25f));
	defaultShader.Uniform3f("material.diffuseColour", vec3(0.4f, 0.4f, 0.4f));
	defaultShader.Uniform3f("material.specColour", vec3(0.774597f, 0.774597f, 0.774597f));
	defaultShader.Uniform1f("material.shininess", 0.6f * 128.0f);
	InputManager::Initalise();
	
	while (!window.isClosed())
	{
		glClearColor(0.3f, 0.3f, 0.8f, 1.0f);
		window.ClearScreen();
		Timer::Update();

		log("FPS: " << int(1.0f / Timer::GetDeltaTime()));
		do_movement(window.deltaTime, position, direction, vec3(0.0f, 1.0f, 0.0f));
		view = mat4::lookAt(position, position + direction, vec3(0.0f, 1.0f, 0.0f));
		defaultShader.UniformMatrix4f("view", 1, GL_FALSE, view);
		defaultShader.Uniform3f("cameraPos", position);
		m.Draw(defaultShader);
		chess.Draw(defaultShader);

		window.update();
	}

	return 0;

}