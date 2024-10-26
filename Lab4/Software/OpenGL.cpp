#include "OpenGL.h"
#include "Callbacks.h"
#include "ShaderMaker.h"

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


void OpenGLManager::initShaders()
{
    GLenum ErrorCheckValue = glGetError();

    char* vertexShader = (char*)"vertexShaderc.glsl";
    char* fragmentShader = (char*)"fragmentShaderc.glsl";

    this->programId = ShaderMaker::createProgram(vertexShader, fragmentShader);
    glUseProgram(this->programId);

}



void OpenGLManager::deleteProgram() {
    glDeleteProgram(this->programId);
}

GLuint OpenGLManager::getProgramID()
{
    return this->programId;
}
