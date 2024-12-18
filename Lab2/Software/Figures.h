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
    virtual void initFigure() = 0;  // Pure virtual function
    virtual void renderFigure() = 0;       // Pure virtual function for rendering
    void deleteFigure();
protected:
    GLuint VAO;                      // Identifier for the Vertex Array Object (VAO)
    GLuint VBO_vertices;             // Identifier for the Vertex Buffer Object (VBO) containing vertex coordinates
    GLuint VBO_colors;               // Identifier for a VBO containing vertex colors
    int nTriangles;                  // Number of triangles constituting the object
    vector<vec3> vertices;           // Vector containing the coordinates of the object's vertices (each element is a vec3)
    vector<vec4> colors;             // Vector containing the colors of the object's vertices (each element is a vec4)
    int nv;                          // Number of vertices in the geometric figure
    GLenum renderMode;               // Specifies how vertices should be interpreted during rendering
    void initVAO();                  // Function to initialize the VAO
};

class Triangle : public Figure
{
public:
    void initFigure() override;
    void renderFigure() override;
};


