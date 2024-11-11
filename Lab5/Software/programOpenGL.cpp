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

    Butterfly butterfly(300, openGLManager.getModelMatrix(), openGLManager.getProjectionMatrix());
    Heart heart(300, openGLManager.getModelMatrix(), openGLManager.getProjectionMatrix());
    staticFigures.push_back(&heart);
    staticFigures.push_back(&butterfly);

    for (Figure* fig : staticFigures) {
        fig->initFigure(GL_STATIC_DRAW);
    }

    float x, y, angolo = 0.0f;
    float lastUpdateTime = glfwGetTime();
    float updateInterval = 1.0f / 20.0f;
    float offsetx = 0;

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

            glClearColor(r, g, b, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            Figure* figure0 = staticFigures.at(0);
            figure0->translateFigure(width / 2, height / 2, 0.0);
            figure0->scaleFigure(baseScale, baseScale, 1.0);
     
            

            Figure* figure1 = staticFigures.at(1);
            angolo += 0.1;
            offsetx += 1.0;
            figure1->translateFigure(width / 2 - 200 + offsetx, height / 2, 0.0);
            figure1->scaleFigure(baseScale, baseScale, 1.0);
            //figure1->rotateFigure(angolo);
        
			figure0->updateBoundingBox();
			figure1->updateBoundingBox();
       
			//std::cout << "Figure 0: " << figure1->getBoundingBox().at(0).x << " " << figure1->getBoundingBox().at(0).y << " " << figure1->getBoundingBox().at(1).x << " " << figure1->getBoundingBox().at(1).y << std::endl;
          

            if (figure0->isColliding(figure1)) {
                std::cout << "Collision detected!" << std::endl;
            }

            figure0->renderFigure();
            figure1->renderFigure();

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