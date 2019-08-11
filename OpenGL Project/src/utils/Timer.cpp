#include "Timer.h"
#include "../input/InputManager.h"

bool Timer::isPause = false;
double Timer::lastTime = 0.0;
double Timer::deltaTime = 0.0;
double Timer::currentTime = 0.0;


double Timer::GetDeltaTime()
{
	return deltaTime;
}

/*
	* @param[in] time
	*/
void Timer::setTime(double time)
{
	currentTime = time;
	//glfwSetTime(time);
	

}
double Timer::getTime()
{
	return glfwGetTime();

}
bool Timer::isPaused()
{
	return isPause;
}
void Timer::Update()
{
	currentTime = glfwGetTime();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;
}
