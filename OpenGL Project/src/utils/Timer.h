#pragma once
#include <GLFW\glfw3.h>


class Timer
{
private:
	static bool isPause;
	static double currentTime;
	static double lastTime;
	static double deltaTime;

public:
	static void restart();
	static double GetDeltaTime();
	static void setTime(double time);
	static double getTime();
	static bool isPaused();
	static void Update();
};