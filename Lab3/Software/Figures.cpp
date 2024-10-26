#include "Figures.h"


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


void Figure::deleteFigure() {
    glDeleteBuffers(1, &this->VBO_vertices);
    glDeleteBuffers(1, &this->VBO_colors);
    glDeleteVertexArrays(1, &this->VAO);
}


void Triangle::initFigure() {
    this->vertices.push_back(vec3(-0.5f, -0.5f, 0.0f));
    this->vertices.push_back(vec3(0.5f, -0.5f, 0.0f));
    this->vertices.push_back(vec3(0.0f, 0.5f, 0.0f));
    
    this->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    this->colors.push_back(vec4(0.0, 1.0, 0.0, 1.0));
    this->colors.push_back(vec4(0.0, 0.0, 1.0, 1.0));
    this->nv = 3;
    this->renderMode = GL_TRIANGLES;
    this->initVAO();
}

void Triangle::renderFigure() {

    // This instruction "binds" or "activates" the Vertex Array Object (VAO) of the triangle.
    glBindVertexArray(this->VAO);

    // This instruction performs the actual drawing using the shader program.
    // GL_TRIANGLES: Indicates that the vertices in the buffer should be interpreted as triangles.
    // 0: Indicates the index of the first vertex to use.
    // 3: Indicates the number of vertices to use.

    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Draw the triangles using the specified render mode and number of vertices.
    glDrawArrays(this->renderMode, 0, this->nv);
}


