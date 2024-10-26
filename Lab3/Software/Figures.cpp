#include "Figures.h"

#define M_PI 3.14159265358979323846
void Figure::initVAO() {

    // The INIT_VAO function initializes the Vertex Array Object (VAO) for the Figure class.
    // By using the 'this' pointer, it directly modifies the data of the original structure, avoiding unnecessary copies.

    glGenVertexArrays(1, &this->VAO);               // Generate one Vertex Array Object and store its ID in VAO
    glBindVertexArray(this->VAO);                   // Bind the VAO, making it the current VAO for subsequent operations

    // Generate, activate, and fill the VBO for the vertex geometry
    glGenBuffers(1, &this->VBO_vertices);          // Generate one Vertex Buffer Object (VBO) for vertices
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO_vertices); // Bind the VBO for vertex data

 
    int areaSize = this->vertices.size() * sizeof(vec3);
    vec3* startAreaPointer = this->vertices.data(); 


    // Allocate and initialize buffer data
// - GL_ARRAY_BUFFER: target buffer type (for vertex attributes)
// - areaSize: size in bytes of the data store to allocate
// - startAreaPointer: pointer to the data to initialize the buffer with (can be nullptr if no initial data is needed)
// - GL_STATIC_DRAW: hint that the data will not change often and is used for drawing operations
    glBufferData(GL_ARRAY_BUFFER, areaSize, startAreaPointer, GL_STATIC_DRAW); 

// Specify layout for vertex attributes
// - 0: index of the vertex attribute (matches the layout(location = 0) in the vertex shader)
// - 3: number of components per vertex attribute (for vec3: x, y, z)
// - GL_FLOAT: data type of each component
// - GL_FALSE: specifies that the data is not normalized
// - 0: stride, indicating the byte offset between consecutive vertex attributes (0 means tightly packed)
// - (void*)0: offset of the first component of the first vertex attribute in the array
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
glEnableVertexAttribArray(0); // Enable the vertex attribute array at index 0

// Generate, activate, and fill the VBO for colors
glGenBuffers(1, &this->VBO_colors); // Generate one VBO for colors
glBindBuffer(GL_ARRAY_BUFFER, this->VBO_colors); // Bind the VBO for color data


areaSize = this->colors.size() * sizeof(vec4);
vec4* startAreaPointerColors = this->colors.data();

// Allocate and initialize buffer data for colors
glBufferData(GL_ARRAY_BUFFER, areaSize, startAreaPointerColors, GL_STATIC_DRAW);

// Load the color VBO into layout index 1
glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0); // Specify layout for color attributes
glEnableVertexAttribArray(1); // Enable the vertex attribute array at index 1
}

void Figure::initFigure() {
    this->initVAO();
}

void Figure::deleteFigure() {
    glDeleteBuffers(1, &this->VBO_vertices);
    glDeleteBuffers(1, &this->VBO_colors);
    glDeleteVertexArrays(1, &this->VAO);
}

void Figure::renderFigure() {

    // This instruction "binds" or "activates" the Vertex Array Object (VAO) of the triangle.
    glBindVertexArray(this->VAO);
    // Draw the triangles using the specified render mode and number of vertices.
    glDrawArrays(this->renderMode, 0, this->numberOfVertices);
}



Triangle::Triangle() : Figure() {}

void Triangle::initFigure() {
    this->vertices.push_back(vec3(-0.5f, -0.5f, 0.0f));
    this->vertices.push_back(vec3(0.5f, -0.5f, 0.0f));
    this->vertices.push_back(vec3(0.0f, 0.5f, 0.0f));

    this->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    this->colors.push_back(vec4(0.0, 1.0, 0.0, 1.0));
    this->colors.push_back(vec4(0.0, 0.0, 1.0, 1.0));
    this->numberOfVertices = 3;
    this->renderMode = GL_TRIANGLES;

    Figure::initFigure();
}


Circle::Circle(float cx, float cy, float rx, float ry, unsigned int numberOfTriangles, float scaleSize)
    : Figure()
    , centerX(cx)
    , centerY(cy)
    , radiusX(rx)
    , radiusY(ry)
    , scaleSize(scaleSize)
{
    this->nTriangles = numberOfTriangles;
}

void Circle::initFigure() {
    
    float t, xx, yy;
    float stepA = (2 * M_PI) / this->nTriangles; // Utilizza this->nTriangles per accedere al numero di triangoli
    this->vertices.push_back(vec3(this->centerX, this->centerY, 0.0)); // Aggiungi il centro del cerchio
    this->colors.push_back(vec4(0.0, 1.0, 1.0, 1.0)); // Colore del centro

    for (unsigned int i = 0; i <= this->nTriangles; i++)
    {
        t = (float)i * stepA;
        xx = this->centerX +( this->radiusX * cos(t)) * this->scaleSize;
        yy = this->centerY +( this->radiusY * sin(t)) * this->scaleSize;
        this->vertices.push_back(vec3(xx, yy, 0.0)); // Aggiungi il vertice calcolato
        this->colors.push_back(vec4(0.0, 0.0, 1.0, 1.0)); // Colore dei vertici
    }

    this->numberOfVertices = this->vertices.size(); // Aggiorna il numero di vertici
    this->renderMode = GL_TRIANGLE_FAN; // Imposta il modo di rendering
    Figure::initFigure(); // Chiama il metodo della classe base
}



Butterfly::Butterfly(float cx, float cy, float rx, float ry, unsigned int numberOfTriangles, float scaleSize)
    : Figure()
    , centerX(cx)
    , centerY(cy)
    , radiusX(rx)
    , radiusY(ry)
    , scaleSize(scaleSize)
{
    this->nTriangles = numberOfTriangles;
}


void Butterfly::initFigure() {
   
    float t, xx, yy;
    float stepA = (2 * M_PI) / this->nTriangles;
    this->vertices.push_back(vec3(this->centerX, this->centerY, 0.0));


    this->colors.push_back(vec4(1.0, 1.0, 1.0, 1.0));

    for (unsigned int i = 0; i <= this->nTriangles; i++)
    {
        t = (float)i * stepA;
        xx = this->centerX + (this->radiusX * (sin(t) * (exp(cos(t)) - 2 * cos(4 * t)) + pow(sin(t / 12), 5))) * this->scaleSize;
        yy = this->centerY + (this->radiusY * (cos(t) * (exp(cos(t)) - 2 * cos(4 * t)) + pow(sin(t / 12), 5)))* this->scaleSize;
        this->vertices.push_back(vec3(xx, yy, 0.0));
        this->colors.push_back(vec4(1.0, 0.5, 0.0, 1.0));
    }
    this->numberOfVertices = this->vertices.size();
    this->renderMode = GL_TRIANGLE_FAN;
    Figure::initFigure();
}


Heart::Heart(float cx, float cy, float rx, float ry, unsigned int numberOfTriangles, float scaleSize)
    : Figure()
    , centerX(cx)
    , centerY(cy)
    , radiusX(rx)
    , radiusY(ry)
    , scaleSize(scaleSize)
{
    this->nTriangles = numberOfTriangles;
}


void Heart::initFigure() {
    
    float t, xx, yy;
    float stepA = (2 * M_PI) / this->nTriangles;
    this->vertices.push_back(vec3(this->centerX, this->centerY, 0.0));


    this->colors.push_back(vec4(1.0, 1.0, 1.0, 1.0));

    for (unsigned int i = 0; i <= this->nTriangles; i++)
    {
        t = (float)i * stepA;
        xx = this->centerX + (this->radiusX * (16 * pow(sin(t), 3))) * this->scaleSize;
        yy = this->centerY + (this->radiusY * ((13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t)))) * this->scaleSize;
        this->vertices.push_back(vec3(xx, yy, 0.0));
        this->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    }
    this->numberOfVertices = this->vertices.size();
    this->renderMode = GL_TRIANGLE_FAN;
    Figure::initFigure();

}



