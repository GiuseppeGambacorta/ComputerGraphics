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
    Figure(unsigned int numberOfTriangles, GLuint matModel, mat4 Projection);

    virtual void initFigure(int TypeOfDraw) = 0;  // Pure virtual function
    void renderFigure();
    void deleteFigure();
    void updateFigure();

    void translateFigure(float x, float y, float z);
    void scaleFigure(float x, float y, float z);
    void rotateFigure(float angle);

	bool isColliding(Figure* otherFigure);
    vector<vec4> getBoundingBox();
    void updateBoundingBox();


protected:
    GLuint VAO;                      // Identifier for the Vertex Array Object (VAO)
    GLuint VBO_vertices;             // Identifier for the Vertex Buffer Object (VBO) containing vertex coordinates
    GLuint VBO_colors;               // Identifier for a VBO containing vertex colors
    unsigned int NumberOfTriangles;                  // Number of triangles constituting the object
    vector<vec3> vertices;           // Vector containing the coordinates of the object's vertices (each element is a vec3)
    vector<vec4> colors;             // Vector containing the colors of the object's vertices (each element is a vec4)
    int numberOfVertices;            // Number of vertices in the geometric figure
    GLenum renderMode;               // Specifies how vertices should be interpreted during rendering

	mat4 Projection;
    GLuint MatModel;
    mat4 Model;
    
    vec4 min, max;
	vec4 tempMin, tempMax;

    void initVAO();                  // Function to initialize the VAO
    void initDynamicVAO();
    void normalizeVertices();
	void findBoundingBox();

};

class Triangle : public Figure
{
public:
    Triangle(unsigned int numberOfTriangles, GLuint MatModel, mat4 projection);       // Add MatModel to the constructor
    void initFigure(int TypeOfDraw) override;
};

class Circle : public Figure
{
public:
    Circle(unsigned int numberOfTriangles, GLuint MatModel, mat4 projection); // Add MatModel to the constructor
    void initFigure(int TypeOfDraw) override;
};

class Butterfly : public Figure
{
public:
    Butterfly(unsigned int numberOfTriangles, GLuint MatModel, mat4 projection); // Add MatModel to the constructor
    void initFigure(int TypeOfDraw) override;
};

class Heart : public Figure
{
public:
    Heart(unsigned int numberOfTriangles, GLuint MatModel, mat4 projection); // Add MatModel to the constructor
    void initFigure(int TypeOfDraw) override;
};