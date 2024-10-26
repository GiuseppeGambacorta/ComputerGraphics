// Progetto1.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "openGL.h"
#include "callbacks.h"

float r = 0.0, g = 1.0, b = 0.0;  
const double PI = 3.14159265358979323846;

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
    float firstOffset = 2.0f * PI / 3.0f; // 120
    float secondOffset = 4.0f * PI / 3.0f; // 240

    /* Loop until the user closes the window (Ripeti il ciclo finché l'utente non chiude la finestra) */
    while (!glfwWindowShouldClose(window))
    {

        float currentTime = glfwGetTime(); 

      
        r = sin(currentTime) * 0.5f + 0.5f; // Range from -1,1 to -0.5,0.5, then to 0,1
        g = sin(currentTime + firstOffset) * 0.5f + 0.5f; 
        b = sin(currentTime + secondOffset) * 0.5f + 0.5f; 

        glClearColor(r, g, b, 1.0f); // Set background color for the frame, colors must be in 0,1 range
        glClear(GL_COLOR_BUFFER_BIT); // Clear color buffer with set background color

                 
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}


