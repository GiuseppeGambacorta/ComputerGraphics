#include "Window.h"

WindowManager::WindowManager( const char* title)
{
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    this->screenHeight = mode->width / 2;
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

