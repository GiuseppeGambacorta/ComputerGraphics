#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "lib.h"
#include "Window.h"




class OpenGLManager
{
public:
	 int initOpenGL();
	 WindowManager* getWindowManager(const char* title);
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
  
	WindowManager* window;
	vector<GLuint> programs;
	mat4 Projection;
	GLuint MatProj;
	GLuint modelMatrix;
	ShaderMaker shaderMaker;
	
};