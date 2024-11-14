#pragma once

#include "lib.h"

using namespace std;
using namespace glm;

class Figure
{
public:
    Figure(unsigned int numberOfTriangles, GLuint matModel);

    virtual void initFigure(int TypeOfDraw, vec4 color) = 0;  // Pure virtual function
 
    void deleteFigure();
    void updateFigure();

    void enableRendering();
    void disableRendering();
    bool isRenderingEnabled();

    void translateFigure(float x, float y, float z);
    void scaleFigure(float x, float y, float z);
    void rotateFigure(float angle);

    bool isColliding(Figure* otherFigure);
	void disableCollisions();
	void enableCollisions();
	bool isCollisionsEnabled();
    vec4 getCurrentPosition();
    vector<vec4> getBoundingBox();
	void setColor(vec4 color);



protected:
    GLuint VAO;                      // Identifier for the Vertex Array Object (VAO)
    GLuint VBO_vertices;             // Identifier for the Vertex Buffer Object (VBO) containing vertex coordinates
    GLuint VBO_colors;               // Identifier for a VBO containing vertex colors
    unsigned int NumberOfTriangles;                  // Number of triangles constituting the object
    vector<vec3> vertices;           // Vector containing the coordinates of the object's vertices (each element is a vec3)
    vector<vec4> colors;             // Vector containing the colors of the object's vertices (each element is a vec4)
    int numberOfVertices;            // Number of vertices in the geometric figure
    GLenum renderMode;               // Specifies how vertices should be interpreted during rendering

    GLuint MatModel;
    mat4 Model;

    vec4 center;
    vec4 min, max;
    vec4 tempMin, tempMax;

    bool renderEnabled;
    bool collisionsEnabled;

    void initVAO();                  // Function to initialize the VAO
    void initDynamicVAO();
    void normalizeVertices();
    void findBoundingBox();
    void updateBoundingBox();
    void updatePosition();
    void renderFigure();

};

