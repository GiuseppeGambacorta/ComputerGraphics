
#include "lib.h"
#include <iostream>
#include <fstream>
#include <sstream>

 

GLuint ShaderMaker::compileShader(const char* shaderPath, GLenum shaderType)
{
	// Leggi il codice dello shader dal file
	std::string shaderCode;
	std::ifstream shaderFile(shaderPath, std::ios::in);
	if (shaderFile.is_open()) {
		std::stringstream sstr;
		sstr << shaderFile.rdbuf();
		shaderCode = sstr.str();
		shaderFile.close();
	}
	else {
		std::cerr << "Impossibile aprire il file shader: " << shaderPath << std::endl;
		return 0;
	}

	// Compila lo shader
	GLuint shaderID = glCreateShader(shaderType);
	const char* shaderSource = shaderCode.c_str();
	glShaderSource(shaderID, 1, &shaderSource, NULL);
	glCompileShader(shaderID);

	// Controlla gli errori di compilazione
	GLint result = GL_FALSE;
	int infoLogLength;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		std::vector<char> shaderErrorMessage(infoLogLength + 1);
		glGetShaderInfoLog(shaderID, infoLogLength, NULL, &shaderErrorMessage[0]);
		std::cerr << &shaderErrorMessage[0] << std::endl;
	}

	return shaderID;
}

GLuint ShaderMaker::createProgram(const char* vertexfilename, const char *fragmentfilename)
{
 
	// Compila il vertex shader una volta
	GLuint vertexShaderID = compileShader(vertexfilename, GL_VERTEX_SHADER);

	// Crea il primo programma shader
	GLuint fragmentShaderID1 = compileShader(fragmentfilename, GL_FRAGMENT_SHADER);
	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID1);
	glLinkProgram(programID);
	
	return programID;
}
