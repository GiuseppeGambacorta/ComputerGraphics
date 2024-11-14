#include "figures.h"
#include "lib.h"
#define M_PI 3.14159265358979323846


Triangle::Triangle(unsigned int numberOfTriangles, GLuint matModel) : Figure(numberOfTriangles,matModel) {}

void Triangle::initFigure(int typeOfDraw) {
    this->vertices.push_back(vec3(-0.5f, -0.5f, 0.0f));
    this->vertices.push_back(vec3(0.5f, -0.5f, 0.0f));
    this->vertices.push_back(vec3(0.0f, 0.5f, 0.0f));

    this->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    this->colors.push_back(vec4(0.0, 1.0, 0.0, 1.0));
    this->colors.push_back(vec4(0.0, 0.0, 1.0, 1.0));
    this->numberOfVertices = 3;
    this->renderMode = GL_TRIANGLES;

    Figure::initFigure(typeOfDraw);
}

Circle::Circle(unsigned int numberOfTriangles, GLuint matModel) : Figure(numberOfTriangles, matModel) {}

void Circle::initFigure(int typeOfDraw) {
    float t, xx, yy;
    float stepA = (2 * M_PI) / this->NumberOfTriangles;

    this->vertices.push_back(vec3(0.0f, 0.0f, 0.0f)); // Centro del cerchio
    this->colors.push_back(vec4(0.0, 1.0, 1.0, 1.0)); // Colore del centro

    for (unsigned int i = 0; i <= this->NumberOfTriangles; i++) {
        t = (float)i * stepA;
        xx = cos(t);
        yy = sin(t);
        this->vertices.push_back(vec3(xx, yy, 0.0)); // Aggiungi il vertice calcolato
        this->colors.push_back(vec4(0.0, 0.0, 1.0, 1.0)); // Colore dei vertici
    }

    this->numberOfVertices = this->vertices.size(); // Aggiorna il numero di vertici
    this->renderMode = GL_TRIANGLE_FAN; // Imposta il modo di rendering
    Figure::initFigure(typeOfDraw); // Chiama il metodo della classe base
}

Butterfly::Butterfly(unsigned int numberOfTriangles, GLuint matModel) : Figure(numberOfTriangles, matModel) {}

void Butterfly::initFigure(int typeOfDraw) {
    float t, xx, yy;
    float stepA = (2 * M_PI) / this->NumberOfTriangles;
    this->vertices.push_back(vec3(0.0f, 0.0f, 0.0f)); 
    this->colors.push_back(vec4(1.0, 1.0, 1.0, 1.0));

    for (unsigned int i = 0; i <= this->NumberOfTriangles; i++) {
        t = (float)i * stepA;
        xx =  (sin(t) * (exp(cos(t)) - 2 * cos(4 * t)) + pow(sin(t / 12), 5));
        yy =  (cos(t) * (exp(cos(t)) - 2 * cos(4 * t)) + pow(sin(t / 12), 5));
        this->vertices.push_back(vec3(xx, yy, 0.0));
        this->colors.push_back(vec4(1.0, 0.5, 0.0, 1.0));
    }

    this->numberOfVertices = this->vertices.size();
    this->renderMode = GL_TRIANGLE_FAN;
    Figure::initFigure(typeOfDraw);
}

Heart::Heart(unsigned int numberOfTriangles, GLuint matModel) : Figure(numberOfTriangles, matModel) {}


void Heart::initFigure(int typeOfDraw) {
    float t, xx, yy;
    float stepA = (2 * M_PI) / this->NumberOfTriangles;
    this->vertices.push_back(vec3(0.0f, 0.0f, 0.0f)); // Centro del cuore
    this->colors.push_back(vec4(1.0, 1.0, 1.0, 1.0));

    for (unsigned int i = 0; i <= this->NumberOfTriangles; i++) {
        t = (float)i * stepA;
        xx =  (16 * pow(sin(t), 3));
        yy =  (13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t));
        this->vertices.push_back(vec3(xx, yy, 0.0));
        this->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    }

    this->numberOfVertices = this->vertices.size();
    this->renderMode = GL_TRIANGLE_FAN;
    Figure::initFigure(typeOfDraw);
}


Rettangle::Rettangle(unsigned int numberOfTriangles, GLuint matModel) : Figure(numberOfTriangles, matModel) {}

void Rettangle::initFigure(int typeOfDraw) {
 
 


    this->vertices.push_back(vec3(-1.0f, -1.0f, 0.0f));  // Vertice in basso a sinistra
    this->vertices.push_back(vec3(0.5f, -0.5f, 0.0f));   // Vertice in basso a destra
    this->vertices.push_back(vec3(-0.5f, 0.5f, 0.0f));    // Vertice in alto a destra
    // Secondo triangolo
    this->vertices.push_back(vec3(-0.5f, 0.5f, 0.0f));  // Vertice in basso a sinistra
    this->vertices.push_back(vec3(0.5f, -0.5f, 0.0f));   // Vertice in alto a sinistra
    this->vertices.push_back(vec3(0.5f, 0.5f, 0.0f));    // Vertice in alto a destra
  



    // Colori per tutti i 6 vertici
    this->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    this->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    this->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    this->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    this->colors.push_back(vec4(0.0, 0.0, 1.0, 1.0));
    this->colors.push_back(vec4(1.0, 1.0, 0.0, 1.0));

    this->numberOfVertices = this->vertices.size();
    this->renderMode = GL_TRIANGLES;

    Figure::initFigure(typeOfDraw);
}


