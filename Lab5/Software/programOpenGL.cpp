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

float calculateFigureScale(float windowWidth, float windowHeight) {
    float minDimension = std::min(windowWidth, windowHeight);
    return minDimension / 40.0f;
}
// ciao
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
    if (!openGLManager.gladLoad()) {
        std::cout << "Failed to load opengl function pointers !" << std::endl;
        return -1;
    }

    openGLManager.setCallbacks();
    openGLManager.initShaders();
    openGLManager.enableColorBlending();
    openGLManager.setProjectionMatrix((float)width, (float)height);

    Butterfly butterfly(300, openGLManager.getModelMatrix());
    Heart heart(300, openGLManager.getModelMatrix());
    staticFigures.push_back(&heart);
    staticFigures.push_back(&butterfly);

    for (Figure* fig : staticFigures) {
        fig->initFigure(GL_STATIC_DRAW);
    }

    float stepr = ((float)width) / (numCols);
    float stepc = ((float)height / 2.0) / (numRows);
    float x, y, angolo = 0.0f;
    float lastUpdateTime = glfwGetTime();
    float updateInterval = 1.0f / 60.0f;

    while (!glfwWindowShouldClose(window))
    {
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastUpdateTime;

        if (deltaTime >= updateInterval) {
            lastUpdateTime = currentTime;

            // Ottieni le dimensioni correnti della finestra
            int currentWidth, currentHeight;
            glfwGetWindowSize(window, &currentWidth, &currentHeight);

            // Calcola la scala basata sulla finestra
            float baseScale = calculateFigureScale(currentWidth, currentHeight);
			std::cout << "Base scale: " << baseScale << std::endl;

            glClearColor(r, g, b, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            stepr = ((float)currentWidth) / (numCols);
            stepc = ((float)currentHeight / 2.0) / (numRows);

            for (unsigned int i = 0; i < numRows; ++i) {
                y = currentHeight - i * stepc - stepc / 2;
                for (unsigned int j = 0; j < numCols; ++j) {
                    x = j * stepr + stepr / 2;
                    float finalX = x + mousex - (stepr * numCols) / 2.0f;
                    float finalY = y + mousey + (stepc * numRows) / 2.0f;

                    if (i % 2 == 0) {
                        float raggiox = sin(currentTime * 2.0 * PI) * 0.25f + 0.75f;
                        Figure* figure = staticFigures.at(0);
                        figure->translateFigure(finalX, finalY, 0.0);
                        figure->scaleFigure(baseScale * raggiox, baseScale * raggiox, 1.0);
                        figure->renderFigure();
                    }
                    else {
                        angolo += 0.1;
                        Figure* figure = staticFigures.at(1);
                        figure->translateFigure(finalX, finalY, 0.0);
                        figure->scaleFigure(baseScale, baseScale, 1.0);
                        figure->rotateFigure(angolo);
                        figure->renderFigure();
                    }
                }
            }

            glfwSwapBuffers(window);
        }
        glfwPollEvents();
    }

    for (Figure* fig : staticFigures) {
        fig->deleteFigure();
    }

    glfwTerminate();
    return 0;
}