#include "figure.h"
#include "lib.h"



Figure::Figure(unsigned int numberOfTriangles, GLuint matModel) : NumberOfTriangles(numberOfTriangles), MatModel(matModel) {

    this->Model = mat4(1.0);
    this->center = vec4(0.0, 0.0, 0.0, 0.0);
    this->min = vec4(0.0, 0.0, 0.0, 0.0);
    this->max = vec4(0.0, 0.0, 0.0, 0.0);
    this->renderEnabled = true;
}


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

void Figure::initFigure(int TypeOfDraw, vec4 Color) {
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
    updatePosition();
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

void Figure::enableRendering()
{
    this->renderEnabled = true;
}

void Figure::disableRendering()
{
    this->renderEnabled = false;
}

bool Figure::isRenderingEnabled()
{
    return this->renderEnabled;
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

void Figure::updatePosition() {
    this->center = this->Model * vec4(0.0, 0.0, 0.0, 1.0);
}

vec4 Figure::getCurrentPosition() {
    return this->center;
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

    if (!otherFigure->isRenderingEnabled() || !this->isRenderingEnabled()) {
        return false;
    }

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

void Figure::setColor(vec4 color)
{
	for (size_t i = 0; i < this->colors.size(); i++) {
		this->colors[i] = color;
	}

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO_colors);
    glBufferSubData(GL_ARRAY_BUFFER, 0, this->colors.size() * sizeof(vec4), this->colors.data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
