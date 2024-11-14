#include "Window.h"

WindowManager::WindowManager( const char* title)
{
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    this->screenHeight = mode->width / 2 - (mode->width * 0.1);
    this->screenWidth = mode->height / 2;
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    this->window = glfwCreateWindow(screenWidth, screenHeight, title, NULL, NULL);
    if (!window)
    {
        glfwTerminate(); 
    }

    glfwMakeContextCurrent(window);
  
}

float WindowManager::getScreenWidth()
{
	return this->screenWidth;
}

float WindowManager::getScreenHeight()
{
	return this->screenHeight;
}

GLFWwindow* WindowManager::getWindow() const
{
    return window;
}

void WindowManager::updateWindowSize()
{
	int width = (int)this->screenWidth;
	int height = (int)this->screenHeight;
    glfwGetWindowSize(this->window, &width, &height);
	this->screenWidth = width;
	this->screenHeight = height;
}

float WindowManager::calculateFigureScale()
{
    float minDimension = std::min(screenWidth, screenHeight);
    return minDimension / 30.0f;
}

