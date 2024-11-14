#include "OpenGL.h"
#include "Callbacks.h"
#include "ShaderMaker.h"
#include "lib.h"


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

WindowManager* OpenGLManager::getWindowManager(const char* title)
{
	if (this->window == NULL)
		this->window = new WindowManager(title);

    return this->window;
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
    glfwSetKeyCallback(this->window->getWindow(), key_callback);

    // Mouse movement within the window
    glfwSetCursorPosCallback(this->window->getWindow(), cursor_position_callback);

    // Screen click with the left button
    glfwSetMouseButtonCallback(this->window->getWindow(), mouse_button_callback);

    // Window resize
    glfwSetFramebufferSizeCallback(this->window->getWindow(), framebuffer_size_callback);
}

void OpenGLManager::enableColorBlending()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}






void OpenGLManager::initShaders()
{
    this->programs.push_back(shaderMaker.createProgram("vertexShaderc.glsl", "fragmentShaderc.glsl"));
    this->programs.push_back(shaderMaker.createProgram("vertexShaderc.glsl", "fragmentShaderSf.glsl"));
    this->programs.push_back(shaderMaker.createProgram("vertexShaderc.glsl", "fragmentShaderSky_ok.glsl"));
   
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
