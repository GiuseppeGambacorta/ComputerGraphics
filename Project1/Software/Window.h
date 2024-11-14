#pragma once
#include "lib.h"


class WindowManager
{
public:
	WindowManager(const char* title);
	float getScreenWidth();
	float getScreenHeight();
	GLFWwindow* getWindow() const;
	void updateWindowSize();
	float calculateFigureScale();

private:
	GLFWwindow* window;
	
	float screenWidth;
	float screenHeight;

};