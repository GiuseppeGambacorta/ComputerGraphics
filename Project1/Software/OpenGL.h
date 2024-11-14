#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "lib.h"




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
	 mat4 getProjectionMatrix();
	 GLuint getModelMatrix();

	 void deletePrograms();
	 GLuint getProgramID(unsigned int index);
	 void useProgram(unsigned int index);
private:
  
	GLFWwindow* window;
	vector<GLuint> programs;
	mat4 Projection;
	GLuint MatProj;
	GLuint modelMatrix;
	ShaderMaker shaderMaker;
	
};