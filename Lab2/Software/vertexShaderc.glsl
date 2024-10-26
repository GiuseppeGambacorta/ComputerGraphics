#version 330 core

// Input: vertex position and color
layout (location = 0) in vec3 aPos;    // Vertex position
layout(location = 1) in vec4 Color;    // Vertex color

out vec4 colore_frag;  // Variable that passes the color to the fragment shader

void main()
{
    // Transform the vertex position to homogeneous coordinates; 1.0 indicates it is a point and not a vector (which would be 0.0)
    gl_Position = vec4(aPos, 1.0); 

    // Pass the color to the fragment shader
    colore_frag = Color;               
}

/* 

This is the output of the vertex shader that defines the final position of the vertex on the screen after all transformations.
It is never "lost" but rather used internally by OpenGL for all operations following the vertex shader, 
such as clipping, rasterization, and the computation of fragment positions.

*/
