#include "lib.h"
#include "OpenGL.h"
#include "Callbacks.h"
#include "Figures.h"

#define PI 3.14159265358979323846

float r = 0.0, g = 1.0, b = 0.0;
double mousex = 0.0f, mousey = 0.0f;
vector<Figure*> staticFigures;
OpenGLManager openGLManager;
WindowManager* windowManager;
float angolo = 90.0f;

float calculateFigureScale(float windowWidth, float windowHeight) {
    float minDimension = std::min(windowWidth, windowHeight);
    return minDimension / 30.0f;
}

int main(void)
{
    if (!openGLManager.initOpenGL()) {
        return -1;
    }

    windowManager = openGLManager.getWindowManager("GG-TAN");
    if (windowManager == NULL) {
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
   
    openGLManager.setProjectionMatrix(windowManager->getScreenWidth(), windowManager->getScreenHeight());

    Butterfly butterfly(300, openGLManager.getModelMatrix());
    Heart heart(300, openGLManager.getModelMatrix());
	Rettangle background(300, openGLManager.getModelMatrix());
	Rettangle player(300, openGLManager.getModelMatrix());
	Rettangle GameMap(300, openGLManager.getModelMatrix());
	Rettangle LeftWall(300, openGLManager.getModelMatrix());
	Rettangle RightWall(300, openGLManager.getModelMatrix());
	Rettangle TopWall(300, openGLManager.getModelMatrix());
	Rettangle BottomWall(300, openGLManager.getModelMatrix());

    Circle projectile(300, openGLManager.getModelMatrix());
    projectile.disableRendering();

    staticFigures.push_back(&heart);
    staticFigures.push_back(&butterfly);
	staticFigures.push_back(&background);
	staticFigures.push_back(&player);
	staticFigures.push_back(&projectile);

	staticFigures.push_back(&GameMap);
	staticFigures.push_back(&LeftWall);
	staticFigures.push_back(&RightWall);
	staticFigures.push_back(&TopWall);
	staticFigures.push_back(&BottomWall);



    for (Figure* fig : staticFigures) {
        fig->initFigure(GL_STATIC_DRAW, Colors::Blue);
    }

	GameMap.setColor(Colors::Black);
    
    LeftWall.disableRendering();
	RightWall.disableRendering();
	TopWall.disableRendering();
	BottomWall.disableRendering();
    

    float x, y= 0.0f;
    float lastUpdateTime = glfwGetTime();
    float updateInterval = 1.0f / 60.0f;
    float offsetx = 0;
	float offsety = 0;
    float  projectileAngle;

    while (!glfwWindowShouldClose(windowManager->getWindow()))
    {
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastUpdateTime;

        if (deltaTime >= updateInterval) {
            lastUpdateTime = currentTime;

			windowManager->updateWindowSize();
			int currentWidth = windowManager->getScreenWidth();
			int currentHeight = windowManager->getScreenHeight();
			float baseScale = windowManager->calculateFigureScale();


            openGLManager.useProgram(2);

            unsigned int vec_resS = glGetUniformLocation(openGLManager.getProgramID(2), "resolution");
            unsigned int loc_time = glGetUniformLocation(openGLManager.getProgramID(2), "time");
            vec2 resolution = vec2(float(currentWidth), float(currentHeight));
            glUniform2fv(vec_resS, 1, value_ptr(resolution));
            glUniform1f(loc_time, currentTime);
            
            Figure& Background = *staticFigures.at(2);
            Background.translateFigure(currentWidth / 2, currentHeight / 2, 0.0);
            Background.scaleFigure(currentWidth*0.5, currentHeight*0.5, 0.0);
			Background.updateFigure();
			
			openGLManager.useProgram(0);

            GameMap.translateFigure(currentWidth / 2, currentHeight / 2, 0.0);
            GameMap.scaleFigure(currentWidth * 0.4, currentHeight * 0.4, 0.0);
            GameMap.updateFigure();

			LeftWall.translateFigure(currentWidth*0.05, currentHeight / 2, 0.0);
			LeftWall.scaleFigure(currentWidth*0.05, currentHeight * 0.5, 0.0);

			RightWall.translateFigure(currentWidth*0.95, currentHeight / 2, 0.0);
			RightWall.scaleFigure(currentWidth * 0.05, currentHeight * 0.5, 0.0);

			TopWall.translateFigure(currentWidth / 2, currentHeight * 0.95, 0.0);
			TopWall.scaleFigure(currentWidth * 0.4, currentHeight * 0.05, 0.0);

			BottomWall.translateFigure(currentWidth / 2, currentHeight * 0.05, 0.0);
			BottomWall.scaleFigure(currentWidth * 0.4, currentHeight * 0.05, 0.0);
			
      
            Figure& heart = *staticFigures.at(0);
            heart.translateFigure(currentWidth / 2, currentHeight / 2, 0.0);
            heart.scaleFigure(baseScale, baseScale, 0.0);
            heart.setColor(Colors::Red);
            
            Figure& butterfly = *staticFigures.at(1);
			
         
            
            butterfly.translateFigure(currentWidth / 2 - 200, currentHeight / 2, 0.0);
            butterfly.scaleFigure(baseScale, baseScale, 0.0);
            //figure1->rotateFigure(angolo);


		

                // Controlla lo stato dei tasti
            if (glfwGetKey(windowManager->getWindow(), GLFW_KEY_R) == GLFW_PRESS) {
                angolo -= 1.0f;
            }
            if (glfwGetKey(windowManager->getWindow(), GLFW_KEY_E) == GLFW_PRESS) {
                angolo += 1.0f;
            }


            if (projectile.isRenderingEnabled()) {
                offsetx += cos(projectileAngle * (PI / 180.0f)) * 10.0f;
                offsety += sin(projectileAngle * (PI / 180.0f)) * 10.0f;
                cout << projectileAngle * (PI / 180.0f) << " " << offsetx << endl;
                projectile.translateFigure(currentWidth / 2 + offsetx, currentHeight / 10 + offsety, 0.0);
                projectile.scaleFigure(baseScale, baseScale, 1.0);

                // Controlla se il proiettile � fuori dalla scena
                if (currentWidth / 2 + offsetx < 0 || currentWidth / 2 + offsetx > currentWidth ||
                    currentHeight / 10 + offsety < 0 || currentHeight / 10 + offsety > currentHeight) {
                    projectile.disableRendering();
                    offsetx = 0;
                    offsety = 0;
                }
            }

			
            if (glfwGetKey(windowManager->getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS) {
                if (!projectile.isRenderingEnabled()) {
                    projectile.enableRendering();
                    projectile.translateFigure(currentWidth / 2, currentHeight / 10, 0.0);
                    projectile.scaleFigure(baseScale, baseScale, 1.0);
                    projectileAngle = angolo;
                }
              
				
            }

	
			Figure& player = *staticFigures.at(3);
			player.translateFigure(currentWidth / 2, currentHeight / 10, 0.0);
			player.scaleFigure(baseScale, baseScale, 1.0);
			player.rotateFigure(angolo);
		
  
			for (Figure* fig : staticFigures) {
					fig->updateFigure();
				
			}

            

            if (projectile.isColliding(&heart)) {
				projectile.disableRendering();
                heart.disableRendering();
				heart.disableCollisions();
                offsety = 0;
				offsetx = 0;
            }

			if (projectile.isColliding(&butterfly)) {
				projectile.disableRendering();
				butterfly.disableRendering();
				butterfly.disableCollisions();
				offsety = 0;
				offsetx = 0;
			}

            if (projectile.isColliding(&LeftWall)) {
                projectile.disableRendering();
                offsety = 0;
                offsetx = 0;
            }

			if (projectile.isColliding(&RightWall)) {
				projectile.disableRendering();
				offsety = 0;
				offsetx = 0;
			}

            if (projectile.isColliding(&TopWall)) {
                projectile.disableRendering();
                offsety = 0;
                offsetx = 0;
            }

			
         

			

		

            glfwSwapBuffers(windowManager->getWindow());
        }
        glfwPollEvents();
    }

    for (Figure* fig : staticFigures) {
        fig->deleteFigure();
    }

    glfwTerminate();
    return 0;
}