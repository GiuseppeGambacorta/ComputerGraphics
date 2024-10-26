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
#define M_PI 3.14159265358979323846
using namespace std;
using namespace glm;

float r = 0.0, g = 1.0, b = 0.0;


Triangle triangle;
Circle circle(0.0, 0.0, 0.1, 0.1, 300);
Butterfly butterfly(0.3, 0.5, 0.1, 0.1, 300,1.0);
Heart heart(0.5, 0.5, 0.1, 0.1, 300, 0.1);

vector<Figure*> staticFigures;
vector<Figure*> dynamicFigures;

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

    staticFigures.push_back(&triangle);
    staticFigures.push_back(&circle);
    staticFigures.push_back(&butterfly);
    
    dynamicFigures.push_back(&heart);
  
    for (Figure* fig : staticFigures) {
        fig->initFigure(GL_STATIC_DRAW);
    }

    for (Figure* fig : dynamicFigures) {
        fig->initFigure(GL_DYNAMIC_DRAW);
    }




    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   

    /* Loop until the user closes the window (Ripeti il ciclo finché l'utente non chiude la finestra) */
    while (!glfwWindowShouldClose(window))
    {

        glClearColor(r, g, b, 1.0f); // Set background color for the frame, colors must be in 0,1 range
        glClear(GL_COLOR_BUFFER_BIT); // Clear color buffer with set background color
        
        for (Figure* fig : staticFigures) {
            fig->renderFigure();
        }

        float currentTime = glfwGetTime(); //fornisce il tempo trascorso in secondi 
        float DistanzaDaAmal = sin(currentTime * 2.0f * M_PI) * 0.25f + 0.75; //l valore di raggiox varia sinusoidalmente nel tempo tra 0.5 ed 1
        heart.updateHeart(DistanzaDaAmal);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }


    openGLManager.initShaders();
    for (Figure* fig : staticFigures) {
        fig->deleteFigure();
    }
    for (Figure* fig : dynamicFigures) {
        fig->renderFigure();
    }
    glfwTerminate();
    return 0;
}

