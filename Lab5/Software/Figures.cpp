#include "Figures.h"
#include "lib.h"



Figure::Figure(unsigned int numberOfTriangles, GLuint matModel) : NumberOfTriangles(numberOfTriangles), MatModel(matModel) {

    this->Model = mat4(1.0);
    this->min = vec4(0.0, 0.0, 0.0, 0.0);
    this->max = vec4(0.0, 0.0, 0.0, 0.0);
}

#define M_PI 3.14159265358979323846
void Figure::initVAO() {
    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);

    glGenBuffers(1, &this->VBO_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO_vertices);

    int areaSize = this->vertices.size() * sizeof(vec3);
    vec3* startAreaPointer = this->vertices.data();

    glBufferData(GL_ARRAY_BUFFER, areaSize, startAreaPointer, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &this->VBO_colors);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO_colors);

    areaSize = this->colors.size() * sizeof(vec4);
    vec4* startAreaPointerColors = this->colors.data();

    glBufferData(GL_ARRAY_BUFFER, areaSize, startAreaPointerColors, GL_STATIC_DRAW);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);
}

void Figure::initDynamicVAO() {
    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);

    glGenBuffers(1, &this->VBO_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO_vertices);

    int areaSize = this->vertices.size() * sizeof(vec3);
    vec3* startAreaPointer = this->vertices.data();

    glBufferData(GL_ARRAY_BUFFER, areaSize, startAreaPointer, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &this->VBO_colors);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO_colors);

    areaSize = this->colors.size() * sizeof(vec4);
    vec4* startAreaPointerColors = this->colors.data();

    glBufferData(GL_ARRAY_BUFFER, areaSize, startAreaPointerColors, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);
}

void Figure::initFigure(int TypeOfDraw) {
    normalizeVertices();
	findBoundingBox();
    if (TypeOfDraw == GL_DYNAMIC_DRAW) {
        this->initDynamicVAO();
    }
    else if (TypeOfDraw == GL_STATIC_DRAW) {
        this->initVAO();
    }
}

void Figure::deleteFigure() {
    glDeleteBuffers(1, &this->VBO_vertices);
    glDeleteBuffers(1, &this->VBO_colors);
    glDeleteVertexArrays(1, &this->VAO);
}

void Figure::renderFigure() {
    updateBoundingBox();
	glUniformMatrix4fv(this->MatModel, 1, GL_FALSE, value_ptr(this->Model)); // charge the model matrix into the shader
    glBindVertexArray(this->VAO);
    glDrawArrays(this->renderMode, 0, this->numberOfVertices);
    this->Model = mat4(1.0);

}

void Figure::updateFigure() {
    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO_vertices);
    glBufferSubData(GL_ARRAY_BUFFER, 0, this->vertices.size() * sizeof(vec3), this->vertices.data());

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO_colors);
    glBufferSubData(GL_ARRAY_BUFFER, 0, this->colors.size() * sizeof(vec4), this->colors.data());

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    renderFigure();
}


void Figure::normalizeVertices() {
    if (vertices.empty()) return;

    // Trova il min e max per x e y
    float minX = std::numeric_limits<float>::max();
    float maxX = std::numeric_limits<float>::lowest();
    float minY = std::numeric_limits<float>::max();
    float maxY = std::numeric_limits<float>::lowest();

    // Salta il primo vertice (centro) nella ricerca min/max
    for (size_t i = 1; i < vertices.size(); i++) {
        minX = std::min(minX, vertices[i].x);
        maxX = std::max(maxX, vertices[i].x);
        minY = std::min(minY, vertices[i].y);
        maxY = std::max(maxY, vertices[i].y);
    }

    // Calcola il fattore di scala per normalizzare a [-1, 1]
    float scaleX = (maxX - minX) / 2.0f;
    float scaleY = (maxY - minY) / 2.0f;
    float scale = std::max(scaleX, scaleY);

    if (scale > 0) {
        // Normalizza tutti i vertici tranne il centro
        for (size_t i = 1; i < vertices.size(); i++) {
            vertices[i].x /= scale;
            vertices[i].y /= scale;
        }
    }

}

void Figure::translateFigure(float x, float y, float z) {
    this->Model = translate(this->Model, vec3(x, y, z));


}

void Figure::scaleFigure(float x, float y, float z) {
    this->Model = scale(this->Model, vec3(x, y, z));

}

void Figure::rotateFigure(float angle) {
    this->Model = rotate(this->Model, glm::radians(angle), vec3(0.0, 0.0, 1.0));


}


void Figure::updateBoundingBox() {
	this->tempMin = this->Model * this->min;
	this->tempMax = this->Model * this->max;
 
    
}

void Figure::findBoundingBox() {

    float minX = std::numeric_limits<float>::max();
    float maxX = std::numeric_limits<float>::lowest();
    float minY = std::numeric_limits<float>::max();
    float maxY = std::numeric_limits<float>::lowest();

    for (size_t i = 1; i < this->vertices.size(); i++) {
        minX = std::min(minX, this->vertices[i].x);
        maxX = std::max(maxX, this->vertices[i].x);
        minY = std::min(minY, this->vertices[i].y);
        maxY = std::max(maxY, this->vertices[i].y);
    }


	this->min = vec4(minX, minY, 0.0, 1.0);
	this->max = vec4(maxX, maxY, 0.0, 1.0);


}


bool Figure::isColliding(Figure* otherFigure) {
    // Ottieni la bounding box trasformata di entrambe le figure
    vector<vec4> thisBoundingBox = this->getBoundingBox();
    vector<vec4> otherBoundingBox = otherFigure->getBoundingBox();

    vec4 thisMin = thisBoundingBox[0];
    vec4 thisMax = thisBoundingBox[1];
    vec4 otherMin = otherBoundingBox[0];
    vec4 otherMax = otherBoundingBox[1];

    // Controlla la collisione sugli assi X e Y
    bool collisionX = thisMin.x <= otherMax.x && thisMax.x >= otherMin.x;
    bool collisionY = thisMin.y <= otherMax.y && thisMax.y >= otherMin.y;

    return collisionX && collisionY;
}

vector<vec4> Figure::getBoundingBox() {
	vector<vec4> boundingBox;
	boundingBox.push_back(this->tempMin);
	boundingBox.push_back(this->tempMax);
    return boundingBox;
}

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


