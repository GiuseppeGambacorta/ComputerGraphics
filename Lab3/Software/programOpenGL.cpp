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
Triangle triangle;
Circle circle(0.0, 0.0, 0.1, 0.1, 300);
Butterfly butterfly(0.3, 0.5, 0.1, 0.1, 300,1.0);
Heart heart(0.5, 0.5, 0.1, 0.1, 300, 0.1);
vector<Figure*> figures;

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

    figures.push_back(&triangle);
    figures.push_back(&circle);
    figures.push_back(&butterfly);
    figures.push_back(&heart);

  
    for (Figure* fig : figures) {
        fig->initFigure();
    }


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   

    /* Loop until the user closes the window (Ripeti il ciclo finch� l'utente non chiude la finestra) */
    while (!glfwWindowShouldClose(window))
    {

        glClearColor(r, g, b, 1.0f); // Set background color for the frame, colors must be in 0,1 range
        glClear(GL_COLOR_BUFFER_BIT); // Clear color buffer with set background color
        
        for (Figure* fig : figures) {
            fig->renderFigure();
        }
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    openGLManager.initShaders();
    for (Figure* fig : figures) {
        fig->deleteFigure();
    }
    glfwTerminate();
    return 0;
}
