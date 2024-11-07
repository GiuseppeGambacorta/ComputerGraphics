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
	 void enableColorBlending();
	 void setProjectionMatrix(float width, float height);
	 GLuint getModelMatrix();
	 void deleteProgram();
	 GLuint getProgramID();
private:
	GLFWwindow* window;
	GLuint programId;
	GLuint modelMatrix;
};