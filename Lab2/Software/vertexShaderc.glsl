#version 330 core

// Input: posizione del vertice e colore
layout (location = 0) in vec3 aPos;    // Posizione del vertice
layout(location = 1) in vec4 Color;    // Colore del vertice

out vec4 colore_frag;  // Variabile che passa il colore al fragment shader

void main()
{
    // Trasformo la posizione del vertice in coordinate omogenee, 1.0 indica che è un punto e non un vettore, sarebbe 0.0
    gl_Position = vec4(aPos, 1.0); 

    // Passo il colore al fragment shader
    colore_frag = Color;               
}


/* 

È l'output del vertex shader che definisce la posizione finale del vertice sullo schermo, dopo tutte le trasformazioni.
Non viene mai "perso", ma piuttosto viene usato internamente da OpenGL per tutte le operazioni successive al vertex shader, 
come il clipping, la rasterizzazione e il calcolo della posizione dei frammenti.


*/
