#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

class Figure
{
public:
    virtual void initFigure(int TypeOfDraw) = 0;  // Pure virtual function
    void renderFigure();
    void deleteFigure();
    void updateFigure();
protected:
    GLuint VAO;                      // Identifier for the Vertex Array Object (VAO)
    GLuint VBO_vertices;             // Identifier for the Vertex Buffer Object (VBO) containing vertex coordinates
    GLuint VBO_colors;               // Identifier for a VBO containing vertex colors
    int nTriangles;                  // Number of triangles constituting the object
    vector<vec3> vertices;           // Vector containing the coordinates of the object's vertices (each element is a vec3)
    vector<vec4> colors;             // Vector containing the colors of the object's vertices (each element is a vec4)
    int numberOfVertices;            // Number of vertices in the geometric figure
    GLenum renderMode;               // Specifies how vertices should be interpreted during rendering
    void initVAO();                  // Function to initialize the VAO
    void initDynamicVAO();
};

class Triangle : public Figure
{
public:
    Triangle();
    void initFigure(int TypeOfDraw) override;
};


class Circle : public Figure
{
private:
    float centerX, centerY;
    float radiusX, radiusY;
    float scaleSize;
public:
    Circle(float cx, float cy, float rx, float ry, unsigned int numberOfTriangles, float scaleSize=1.0f);
    void initFigure(int TypeOfDraw) override;
};

class Butterfly : public Figure
{
private:
    float centerX, centerY;
    float radiusX, radiusY;
    float scaleSize;
public:
    Butterfly(float cx, float cy, float rx, float ry, unsigned int numberOfTriangles, float scaleSize=1.0f);
    void initFigure(int TypeOfDraw) override;
};


class Heart : public Figure
{
private:
    float centerX, centerY;
    float radiusX, radiusY;
    float scaleSize;
public:
    Heart(float cx, float cy, float rx, float ry, unsigned int numberOfTriangles, float scaleSize= 1.0f);
    void initFigure(int TypeOfDraw) override;
    void updateHeart(float newScaleSize);
};


