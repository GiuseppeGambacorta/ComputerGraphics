// Progetto1.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include "lib.h"
#include "ShaderMaker.h"

#include "OpenGL.h"
#include "Callbacks.h"
#include "Figures.h"
#define PI 3.14159265358979323846


float r = 0.0, g = 1.0, b = 0.0;
int height = 1200, width = 1200;
int numRows = 6, numCols = 8;
double mousex = 0.0f, mousey = 0.0f;

Butterfly butterfly(0.0, 0.0, 0.1, 0.1, 300,1.0);
Heart heart(0.0, 0.0, 0.1, 0.1, 300, 1.0);

vector<Figure*> staticFigures;

OpenGLManager openGLManager;
GLFWwindow* window;


GLuint MatProj, MatModel;

int main(void)
{
    
    if (!openGLManager.initOpenGL()) {
        return -1;
    }

    window = openGLManager.getWindow(width, height, "Hello World");
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
    openGLManager.enableColorBlending();

    staticFigures.push_back(&heart);
    staticFigures.push_back(&butterfly);  
    
  
    for (Figure* fig : staticFigures) {
        fig->initFigure(GL_STATIC_DRAW);
    }

    
    mat4 Projection = ortho(0.0f, float(width), 0.0f, float(height)); //xmin, xmax, ymin, ymax
    MatProj = glGetUniformLocation(openGLManager.getProgramID(), "Projection");
    glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));

    MatModel = glGetUniformLocation(openGLManager.getProgramID(), "Model");

    float stepr = ((float)width) / (numCols);   //Passo sulle  riga
    float stepc = ((float)height /2.0) / (numRows); //Passo sulla colonna
    float x, y, angolo = 0.0f;
    
    float updateInterval = 0.05f; // 50 ms in secondi
    float lastUpdateTime = glfwGetTime();
    /* Loop until the user closes the window (Ripeti il ciclo finché l'utente non chiude la finestra) */
    while (!glfwWindowShouldClose(window))
    {

        glClearColor(r, g, b, 1.0f); // Set background color for the frame, colors must be in 0,1 range
        glClear(GL_COLOR_BUFFER_BIT); // Clear color buffer with set background color
        

        float currentTime = glfwGetTime();

        if (currentTime - lastUpdateTime >= updateInterval) {
           

            lastUpdateTime = currentTime; // Aggiorna il tempo dell'ultimo aggiornamento
        }

        for (unsigned int i = 0; i < numRows; ++i) {  //Ciclando sulle righe cambio la y
            y = height - i * stepc - stepc / 2;

            for (unsigned int j = 0; j < numCols; ++j) {   //Ciclando sulle colonne cambio la x

                x = j * (stepr)+stepr / 2;


                if (i % 2 == 0)
                {
                    float currentTime = glfwGetTime(); //fornisce il tempo trascorso in secondi 
                    float raggiox = sin(currentTime * 2.0 * PI) * 0.25f + 0.75;
                    staticFigures.at(0)->Model  = mat4(1.0);
                    staticFigures.at(0)->Model = translate(staticFigures.at(0)->Model, vec3(x + mousex, y + mousey, 0.0));
                    staticFigures.at(0)->Model = scale(staticFigures.at(0)->Model, vec3(30.0 * raggiox, 30.0 * raggiox, 1.0));

                    glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(staticFigures.at(0)->Model));
               
                    //Questa istruzione "lega" o "attiva" il Vertex Array Object (VAO) di ogni struttura di tipo Figura memorizzata nel vector Scena .

                    staticFigures.at(0)->renderFigure();
                    
                }
                else
                {

                    angolo = angolo + 0.1;
                    staticFigures.at(1)->Model = mat4(1.0);
                    staticFigures.at(1)->Model = translate(staticFigures.at(1)->Model, vec3(x + mousex, y + mousey, 0.0));
                    staticFigures.at(1)->Model = scale(staticFigures.at(1)->Model, vec3(150.0, 150.0, 1.0));
                    staticFigures.at(1)->Model = rotate(staticFigures.at(1)->Model, glm::radians(angolo), vec3(0.0, 0.0, 1.0));

                 
                    glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(staticFigures.at(1)->Model));
                  
                    //Questa istruzione "lega" o "attiva" il Vertex Array Object (VAO) di ogni struttura di tipo Figura memorizzata nel vector Scena .

                    staticFigures.at(1)->renderFigure();
                }
            }


        }

    

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }


    openGLManager.initShaders();
    for (Figure* fig : staticFigures) {
        fig->deleteFigure();
    }
  
    glfwTerminate();
    return 0;
}

