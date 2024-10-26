#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>




class OpenGLManager
{
public:
	 int initOpenGL();
	 GLFWwindow* getWindow(int width, int height,const char* title);
	 int gladLoad();
	 void setCallbacks();
	 void initShaders();
	 void deleteProgram();
private:
	GLFWwindow* window;
	GLuint programId;
};