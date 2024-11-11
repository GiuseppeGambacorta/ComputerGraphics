#include "lib.h"
#include "OpenGL.h"
#include "Callbacks.h"
#include "Figures.h"
#define PI 3.14159265358979323846

float r = 0.0, g = 1.0, b = 0.0;
int height = 800, width = 800;
double mousex = 0.0f, mousey = 0.0f;
vector<Figure*> staticFigures;
OpenGLManager openGLManager;
GLFWwindow* window;

float calculateFigureScale(float windowWidth, float windowHeight) {
    float minDimension = std::min(windowWidth, windowHeight);
    return minDimension / 30.0f;
}

int main(void)
{
    if (!openGLManager.initOpenGL()) {
        return -1;
    }

    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    int screenWidth = mode->width;
    int screenHeight = mode->height;
    width = screenHeight / 2;
	height = screenWidth / 2;
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);


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
    openGLManager.useProgram(0);

    openGLManager.setProjectionMatrix((float)width, (float)height);

    Butterfly butterfly(300, openGLManager.getModelMatrix());
    Heart heart(300, openGLManager.getModelMatrix());
	Rettangle background(300, openGLManager.getModelMatrix());
	Rettangle player(300, openGLManager.getModelMatrix());
    staticFigures.push_back(&heart);
    staticFigures.push_back(&butterfly);
	staticFigures.push_back(&background);
	staticFigures.push_back(&player);

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
            int currentWidth, currentHeight;
            glfwGetWindowSize(window, &currentWidth, &currentHeight);
            float baseScale = calculateFigureScale(currentWidth, currentHeight);


            openGLManager.useProgram(2);

            unsigned int vec_resS = glGetUniformLocation(openGLManager.getProgramID(2), "resolution");
            unsigned int loc_time = glGetUniformLocation(openGLManager.getProgramID(2), "time");
            vec2 resolution = vec2(float(currentWidth), float(currentHeight));
            glUniform2fv(vec_resS, 1, value_ptr(resolution));
            glUniform1f(loc_time, currentTime);
            
            Figure& Background = *staticFigures.at(2);
            Background.translateFigure(currentWidth / 2, currentHeight / 2, 0.0);
            Background.scaleFigure(currentWidth, currentHeight, 1.0);
            Background.renderFigure();
			
			openGLManager.useProgram(0);
			
      
            Figure& heart = *staticFigures.at(0);
            heart.translateFigure(currentWidth / 2, currentHeight / 2, 0.0);
            heart.scaleFigure(baseScale, baseScale, 1.0);
     
            
            Figure& butterfly = *staticFigures.at(1);
            angolo += 0.1;
            offsetx += 1.0;
            butterfly.translateFigure(currentWidth / 2 - 200 + offsetx, currentHeight / 2, 0.0);
            butterfly.scaleFigure(baseScale, baseScale, 1.0);
            //figure1->rotateFigure(angolo);


			Figure& player = *staticFigures.at(3);
			player.translateFigure(currentWidth / 2, currentHeight / 10, 0.0);
			player.scaleFigure(baseScale, baseScale, 1.0);
  
            heart.renderFigure();
            butterfly.renderFigure();
			player.renderFigure();


            if (heart.isColliding(&butterfly)) {
                std::cout << "Collision detected!" << std::endl;
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