#include "Figures.h"


void Figure::initVAO() {

    //La funzione INIT_VAO  ha per input Figura* fig, che è un puntatore  che punta all'indirizzo ricevuto.
    //In questo modo è possibile modificare direttamente i dati della struttura originale, evitando la creazione di copie inutili.

    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);
    //Genero , rendo attivo, riempio il VBO della geometria dei vertices
    glGenBuffers(1, &this->VBO_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO_vertices);

    //fig->vertices.size() : Ottiene il numero di elementi nel vettore vertices della struttura Figura puntata da fig.
    // sizeof(vec3) : Ottiene la dimensione in byte di un singolo elemento di tipo vec3.
    //La moltiplicazione fig->vertices.size() * sizeof(vec3): calcola la dimensione totale in byte dei dati dei vertici. Calcola la dimensione totale in byte di tutti i dati dei vertici.

    //fig->vertices.data() : fornisce un puntatore all'inizio dei dati del vettore vertices. Questo puntatore indica la posizione esatta in memoria dove sono memorizzati i dati

    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(vec3), this->vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    //Genero , rendo attivo, riempio il VBO dei colori
    glGenBuffers(1, &this->VBO_colors);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO_colors);
    glBufferData(GL_ARRAY_BUFFER, this->colors.size() * sizeof(vec4), this->colors.data(), GL_STATIC_DRAW);
    //Adesso carico il VBO dei coloris nel layer 2
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);
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

    //Questa istruzione "lega" o "attiva" il Vertex Array Object (VAO) di triangolo .
    glBindVertexArray(this->VAO);

    //Questa istruzione effettua il disegno vero e proprio utilizzando il program shader programId
    //GL_TRIANGLES: Indica che i vertici nel buffer devono essere interpretati come triangoli.
    //0 : Indica l'indice del primo vertice da utilizzare.
    //3 : Indica il numero di vertici da utilizzare.

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDrawArrays(this->renderMode, 0, this->nv);

}

