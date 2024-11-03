#include "lib.h"
#include "OpenGL.h"
#include "Callbacks.h"
#include "Figures.h"
#define PI 3.14159265358979323846

float r = 0.0, g = 1.0, b = 0.0;
int height = 1200, width = 1200;
int numRows = 6, numCols = 8;
double mousex = 0.0f, mousey = 0.0f;


vector<Figure*> staticFigures;
OpenGLManager openGLManager;
GLFWwindow* window;



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
	openGLManager.setProjectionMatrix((float) width, (float) height);

    Butterfly butterfly(300, openGLManager.getModelMatrix());
    Heart heart(300, openGLManager.getModelMatrix());

    staticFigures.push_back(&heart);
    staticFigures.push_back(&butterfly);

    for (Figure* fig : staticFigures) {
        fig->initFigure(GL_STATIC_DRAW);
    }

    

  

    float stepr = ((float)width) / (numCols);   // Passo sulle righe
    float stepc = ((float)height / 2.0) / (numRows); // Passo sulla colonna
    float x, y, angolo = 0.0f;

    float lastUpdateTime = glfwGetTime();
    float updateInterval = 1.0f / 60.0f; // 60 FPS

    while (!glfwWindowShouldClose(window))
    {
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastUpdateTime;

        if (deltaTime >= updateInterval) {
            lastUpdateTime = currentTime; // Aggiorna il tempo dell'ultimo aggiornamento

            glClearColor(r, g, b, 1.0f); // Set background color for the frame
            glClear(GL_COLOR_BUFFER_BIT); // Clear color buffer with set background color

            for (unsigned int i = 0; i < numRows; ++i) {
                y = height - i * stepc - stepc / 2;

                for (unsigned int j = 0; j < numCols; ++j) {
                    x = j * stepr + stepr / 2;

                    // Calcola la posizione finale centrando la griglia sul mouse
                    float finalX = x + mousex - (stepr * numCols) / 2.0f; // Sottrai l'offset della larghezza della griglia
                    float finalY = y + mousey + (stepc * numRows) / 2.0f; // Sottrai l'offset dell'altezza della griglia

                    if (i % 2 == 0) {
                        float raggiox = sin(currentTime * 2.0 * PI) * 0.25f + 0.75;
                        staticFigures.at(0)->Model = mat4(1.0);
                        staticFigures.at(0)->Model = translate(staticFigures.at(0)->Model, vec3(finalX, finalY, 0.0));
                        staticFigures.at(0)->Model = scale(staticFigures.at(0)->Model, vec3(30.0*raggiox, 30.0*raggiox, 1.0));

                        glUniformMatrix4fv(openGLManager.getModelMatrix(), 1, GL_FALSE, value_ptr(staticFigures.at(0)->Model));
                        staticFigures.at(0)->renderFigure();
                    }
                    else {
                        angolo += 0.1;
                        staticFigures.at(1)->Model = mat4(1.0);
                        staticFigures.at(1)->Model = translate(staticFigures.at(1)->Model, vec3(finalX, finalY, 0.0));
                        staticFigures.at(1)->Model = scale(staticFigures.at(1)->Model, vec3(30.0, 30.0, 1.0));
                        staticFigures.at(1)->Model = rotate(staticFigures.at(1)->Model, glm::radians(angolo), vec3(0.0, 0.0, 1.0));

                        glUniformMatrix4fv(openGLManager.getModelMatrix(), 1, GL_FALSE, value_ptr(staticFigures.at(1)->Model));
                        staticFigures.at(1)->renderFigure();
                    }
                }
            }
            glfwSwapBuffers(window); // Swap front and back buffers
        }

        glfwPollEvents(); // Poll for and process events
    }

    for (Figure* fig : staticFigures) {
        fig->deleteFigure();
    }

    glfwTerminate();
    return 0;
}
