// Progetto1.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <vector>
#include <glm/glm.hpp>
#include "ShaderMaker.h"

#include "OpenGL.h"
#include "Callbacks.h"
#include "Figures.h"

using namespace std;
using namespace glm;

float r = 0.0, g = 1.0, b = 0.0;


unsigned int programId;
Triangle triangolo;

OpenGLManager openGLManager;
GLFWwindow* window;


int main(void)
{

    if (!openGLManager.initOpenGL()) {
        return -1;
    }

    window = openGLManager.getWindow(640, 480, "Hello World");
    if (window == NULL) {
        std::cout << "Failed to create the window !" << std::endl;
        return -1;
    }

    if (!openGLManager.gladLoad())
    {
        std::cout << "Failed to load opengl function pointers !" << std::endl;
        return -1;
    }

    openGLManager.setCallbacks();
    openGLManager.initShaders();

   
    triangolo.initFigure();
   

    /* Loop until the user closes the window (Ripeti il ciclo finché l'utente non chiude la finestra) */
    while (!glfwWindowShouldClose(window))
    {

        glClearColor(r, g, b, 1.0f); // Set background color for the frame, colors must be in 0,1 range
        glClear(GL_COLOR_BUFFER_BIT); // Clear color buffer with set background color

        triangolo.renderFigure();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    openGLManager.initShaders();
    triangolo.deleteFigure();
    glfwTerminate();
    return 0;
}

