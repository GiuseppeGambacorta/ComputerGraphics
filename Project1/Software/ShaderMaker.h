#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class ShaderMaker
{
    public:
		ShaderMaker() {}
		static GLuint createProgram(const char* vertexfilename, const char *fragmentfilename);
		static GLuint compileShader(const char* shaderFile, GLenum shaderType);
	
    private:
		
};
