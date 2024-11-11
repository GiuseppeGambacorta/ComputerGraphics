#include "OpenGL.h"
#include "Callbacks.h"
#include "ShaderMaker.h"
#include "lib.h"
#include <fstream>
#include <sstream>
#include <iostream>

int OpenGLManager::initOpenGL()
{
    /* Initialize the GLFW library */
    if (!glfwInit())   
        return 0;

    // Set OpenGL version and core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Enable double buffering
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    return 1;
}

GLFWwindow* OpenGLManager::getWindow(int width, int height, const char* title)
{
    /* Create a window on the screen and initialize the OpenGL context
    needed for rendering graphics within that window */

    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window)
    {
        glfwTerminate(); // Free resources allocated by glfwInit
        return NULL;
    }
    this->window = window;

    // Make the current context and associate it with the window.
    // In OpenGL, a rendering context is a state machine that stores 
    // all information and resources required for graphical rendering
    glfwMakeContextCurrent(window);

    return window;
}

// Verify if the GLAD library successfully loaded all OpenGL function pointers
int OpenGLManager::gladLoad()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        return 0;
    }
    return 1;
}

void OpenGLManager::setCallbacks()
{
    // Key press
    glfwSetKeyCallback(this->window, key_callback);

    // Mouse movement within the window
    glfwSetCursorPosCallback(this->window, cursor_position_callback);

    // Screen click with the left button
    glfwSetMouseButtonCallback(this->window, mouse_button_callback);

    // Window resize
    glfwSetFramebufferSizeCallback(this->window, framebuffer_size_callback);
}

void OpenGLManager::enableColorBlending()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


GLuint OpenGLManager::compileShader(const char* shaderPath, GLenum shaderType)
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



void OpenGLManager::initShaders()
{
    GLenum ErrorCheckValue = glGetError();

    // Compila il vertex shader una volta
    GLuint vertexShaderID = compileShader("vertexShaderc.glsl", GL_VERTEX_SHADER);

    // Crea il primo programma shader
    GLuint fragmentShaderID1 = compileShader("fragmentShaderc.glsl", GL_FRAGMENT_SHADER);
    GLuint programID1 = glCreateProgram();
    glAttachShader(programID1, vertexShaderID);
    glAttachShader(programID1, fragmentShaderID1);
    glLinkProgram(programID1);
    this->programs.push_back(programID1);

    // Crea il secondo programma shader
    GLuint fragmentShaderID2 = compileShader("fragmentShaderSf.glsl", GL_FRAGMENT_SHADER);
    GLuint programID2 = glCreateProgram();
    glAttachShader(programID2, vertexShaderID);
    glAttachShader(programID2, fragmentShaderID2);
    glLinkProgram(programID2);
    this->programs.push_back(programID2);


	GLuint fragmentShaderID3 = compileShader("fragmentShaderSky_ok.glsl", GL_FRAGMENT_SHADER);
	GLuint programID3 = glCreateProgram();
	glAttachShader(programID3, vertexShaderID);
	glAttachShader(programID3, fragmentShaderID3);
	glLinkProgram(programID3);
	this->programs.push_back(programID3);


    // Elimina gli shader dopo averli collegati ai programmi
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID1);
    glDeleteShader(fragmentShaderID2);
	glDeleteShader(fragmentShaderID3);
}

void OpenGLManager::setProjectionMatrix(float width, float height)
{
    this->Projection = ortho(0.0f, width, 0.0f, height); //xmin, xmax, ymin, ymax

	for (unsigned int i = 0; i < this->programs.size(); i++) {
		glUseProgram(this->programs[i]);
		this->MatProj = glGetUniformLocation(this->getProgramID(i), "Projection");
		glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(this->Projection));
	}

   
}

mat4 OpenGLManager::getProjectionMatrix()
{
	return this->Projection;
}


GLuint OpenGLManager::getModelMatrix()
{   
    if (this->modelMatrix == 0) {
        this->modelMatrix = glGetUniformLocation(this->getProgramID(0), "Model");
    }

    return  modelMatrix;
}



void OpenGLManager::deletePrograms() {
	for (unsigned int i = 0; i < this->programs.size(); i++) {
		glDeleteProgram(this->programs[i]);
	}
}

GLuint OpenGLManager::getProgramID(unsigned int id)
{
	if (id >= this->programs.size()) {
		return 0;
	}
	return this->programs[id];
    
}

void OpenGLManager::useProgram(unsigned int index)
{
	if (index >= this->programs.size()) {
		return;
	}
	glUseProgram(this->programs[index]);
}
