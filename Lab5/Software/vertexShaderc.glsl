#version 330 core

// Vertex position and color as input
layout (location = 0) in vec3 aPos;    // Vertex position
layout(location = 1) in vec4 Color;    // Vertex color

// Output color passed to the fragment shader
out vec4 ourColor;

// Transformation matrices
uniform mat4 Projection; // Projection matrix
uniform mat4 Model;      // Model matrix

void main()
{
    // Trasformo la posizione del vertice in coordinate omogenee, 1.0 indica che è un punto e non un vettore, sarebbe 0.0
     gl_Position = Projection*Model*vec4(aPos, 1.0); 

    // Passo il colore al fragment shader
    ourColor = Color;               
}


/* 

transforms the position of each vertex from model coordinates (the coordinates in the model's local space) to clip space, a 3D space in which vertices are ready for rasterization and final screen projection. Here’s how each matrix contributes to the transformation:

    Model Matrix:
        The Model matrix is used to transform vertices from the object’s local coordinate system to the world coordinate system.
        This transformation can involve translation, rotation, and scaling of the object in the 3D world.

    Projection Matrix:
        The Projection matrix takes vertices from the world space to the clip space.
        Clip space is a normalized coordinate space where all visible vertices are within a standard cube: x, y, and z range from -1 to 1.
        Commonly, the projection can be either orthographic (where objects retain their size regardless of depth) or perspective (where objects appear smaller as they get farther from the camera).

Why Projection * Model?

    Combined Transformation: By multiplying Projection * Model, each vertex’s position is moved from its model space through the world space (via the Model matrix) and then into clip space (via the Projection matrix), setting it up for display on the screen.

Summary

In the shader:

    vec4(aPos, 1.0): Converts the vertex position from 3D to 4D homogeneous coordinates, allowing for transformations.
    Model * vec4(aPos, 1.0): Places the vertex in the world space.
    Projection * Model * vec4(aPos, 1.0): Projects the vertex to clip space, ready for display.

*/
