
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
#define log(x) std::cout << x << std::endl
bool keys[1024];
bool firstMouse = true;
GLfloat lastX = 0.0f, lastY = 0.0f;
GLfloat pitch = -45.0f, yaw = -90.0f;
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

	float sensitivity = 75.0f * ::window.deltaTime;
	xoffset *= sensitivity;
	yoffset *= sensitivity;
	yaw += (GLfloat) xoffset;
	pitch += (GLfloat) yoffset;

	if (pitch < -89.0f)
		pitch = -89.0f;
	if (pitch > 89.0f)
		pitch = 89.0f;

	vec3 front;

	float radYaw = Math::toRadians(yaw);
	float radPitch = Math::toRadians(pitch);
	float cosPitch = cos(radPitch);
	front.x = cos(radYaw) * cosPitch;
	front.y = sin(radPitch);
	front.z = sin(radYaw) * cosPitch;
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

void do_movement(float deltaTime, vec3& position, vec3 direction, const vec3 up)
{

	float cameraSpeed = 3.0f * deltaTime;
	direction.y = 0.0f;

	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
		position += direction * cameraSpeed;
	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
		position -= direction * cameraSpeed;
	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
		position -= vec3::normalise(vec3::cross(direction, up)) * cameraSpeed;
	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
		position += vec3::normalise(vec3::cross(direction, up)) * cameraSpeed;

}

int main()
{
	
	glfwSetCursorPosCallback(window.m_window, mouse_callback);
	glfwSetKeyCallback(window.m_window, key_callback);

	window.SetCursorVisible(isVisible);
	/*GLuint VAO;
	GLuint buffer, ebo;
	float vertices[] = {
		// (x, y, z, nx, ny, nz)
		-0.5f,  0.0f,   0.5f,   0.0f,  1.0f,  0.0f, // Top-left
		0.5f,  0.0f,   0.5f,   0.0f,  1.0f,  0.0f, // Top-right
		0.5f,  0.0f,  -0.5f,   0.0f,  1.0f,  0.0f, // Bottom-right
		-0.5f,  0.0f,  -0.5f,   0.0f,  1.0f,  0.0f // Bottom-left
	};
	GLuint elements[] = { 0, 1, 2, 2, 3, 0 };
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &ebo);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
	// colour   0.129f, 0.149f, 0.286f
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Vertex Position data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (6 * sizeof(float)), 0);
	glEnableVertexAttribArray(0);
	// Vertex Normal Data
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (6 * sizeof(float)), (GLvoid *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
	*/
	std::vector<Vertex> vertices = {
		Vertex(vec3(-0.5f, 0.0f, 0.5f), vec3(0.0f, 1.0f, 0.0f)), // Top-left
		Vertex(vec3(0.5f,  0.0f,   0.5f), vec3(0.0f,  1.0f,  0.0f)),// Top-right
		Vertex(vec3(0.5f,  0.0f,  -0.5f), vec3(0.0f,  1.0f,  0.0f)),// Bottom-right
		Vertex(vec3(-0.5f,  0.0f,  -0.5f), vec3(0.0f,  1.0f,  0.0f))// Bottom-left
	};
	std::vector<GLuint> indices = {
		0, 1, 2, 2, 3, 0
	};
	Mesh m(vertices, indices);
	// Normal Data

	// Position Data

	const char* vertex = FileUtils::LoadTextFile("src/shaders/default.vs");
	const char* fragment = FileUtils::LoadTextFile("src/shaders/default.fs");
	Shader defaultShader(vertex, fragment);
	/* Quaternion Tests
	Quaternion a = Quaternion::RotateAroundAxis(Math::toRadians(90), vec3(1, 1, 0));

	vec3 b = vec3(0, 0, 1);
	Quaternion res = Quaternion::TransformVector(a,b);
	std::cout << "w: " << res.w << " "<< res.v << std::endl;



	Quaternion rot = Quaternion::Identity();
	float xOff, yOff;

	rot = Quaternion::RotateAroundAxis(Math::toRadians(xOff), vec3(0, 1, 0)) * Quaternion::RotateAroundAxis(Math::toRadians(yOff), vec3(1, 0, 0));
	vec3 dir = Quaternion::TransformVector(rot, b).v;
	b = vec3::normalise(dir);

	*/
	mat4 projection = mat4::perspective(45.0f, 640.0f / 480.0f, 0.3f, 10.0f);
	mat4 view = mat4::lookAt(position, position + direction, vec3(0.0f, 1.0f, 0.0f));
	mat4 model = mat4::scale(4.0f);
	vec3 lightPos(0.0f, 1.0f, 0.0f);
	defaultShader.UniformMatrix4f("projection", 1, GL_FALSE, projection);
	defaultShader.UniformMatrix4f("view", 1, GL_FALSE, view);
	defaultShader.UniformMatrix4f("model", 1, GL_FALSE, model);
	defaultShader.Uniform3f( "light.position", lightPos);

	defaultShader.Uniform3f("light.colour", vec3(0.5f, 0.5f, 0.5f));
	defaultShader.Uniform3f("material.ambientColour", vec3(0.25f, 0.25f, 0.25f));
	defaultShader.Uniform3f("material.diffuseColour", vec3(0.4f, 0.4f, 0.4f));
	defaultShader.Uniform3f("material.specColour", vec3(0.774597f, 0.774597f, 0.774597f));
	defaultShader.Uniform1f("material.shininess", 0.6f * 128.0f);
	InputManager::Initalise();
	//test
	float axes = 0.0f;
	bool begin = true;
	//
	while (!window.isClosed())
	{
		glClearColor(0.3f, 0.3f, 0.8f, 1.0f);
		window.clear();
		Timer::Update();
		// window.SetCursorVisible(isVisible);

		// Horizontal -------------------
		std::cout << "FPS: " << int(1.0f / Timer::GetDeltaTime()) << std::endl;
		// std::cout << InputManager::GetAxis("Horizontal") << std::endl;
		InputManager::GetAxis("Horizontal");

		//Joystick

		// ------------------------------

		// Movement
		do_movement(window.deltaTime, position, direction, vec3(0.0f, 1.0f, 0.0f));
		view = mat4::lookAt(position, position + direction, vec3(0.0f, 1.0f, 0.0f));
		defaultShader.UniformMatrix4f("view", 1, GL_FALSE, view);
		defaultShader.Uniform3f("cameraPos", position);
		// Uniform::Uniform1f(defaultShader, "mixColour", 0.5 + sin(glfwGetTime()) * 0.5);
		//----------------
		m.Draw(defaultShader);
		/*glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		*/

		window.update();
	}
	/*
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDeleteBuffers(1, &ebo);

	glDeleteBuffers(1, &buffer);
	*/
	defaultShader.cleanUp();
	window.cleanUp();

	return 0;

}