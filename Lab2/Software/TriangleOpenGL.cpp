
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp> // matematica per grafica
#include "ShaderMaker.h"

using namespace std;
using namespace glm;


typedef struct Figure
{
    GLuint VAO;
    GLuint VBO_vertices;
    GLuint VBO_colors;
    vector<vec3> vertices;
    vector<vec4> colors;
    int numberVertices;
    int render; // GL_POINTS, GL_LINES, GL_LINES_STRIP, GL_TRIANGLE,....
} Figure;


Figure triangle = {};



//Prototipi funzioni 
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, int button, int action, int mods);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void INIT_SHADER(void);
void INIT_VAO(Figure* figure);

//Variabili globali

static unsigned int programId;
bool isMouseDown = false;
float r = 0, g = 0, b = 0;


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()) {
        return -1;
    }
      

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        std::cout << "Failde to create the window !" << std::endl;

        glfwTerminate(); //LIbera le risorse allcoata da glfwInit
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window); //creal il context corrente e lo associa a wundow. In opengl un rendering context è una macchina astati che memorizza tutte le informazioni necessarie e le risorse per il rendering grafico


    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_callback);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failde to load opengl function pointers !" << std::endl;
        glfwTerminate();
        return -1;
    }

   
    triangle.vertices.push_back(vec3(-0.5,-0.5,0.0));
    triangle.vertices.push_back(vec3(0.5, -0.5, 0.0));
    triangle.vertices.push_back(vec3(0.0, 0.5, 0.0));

    triangle.colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    triangle.colors.push_back(vec4(0.0, 1.0, 0.0, 1.0));
    triangle.colors.push_back(vec4(0.0, 0.0, 1.0, 1.0));

    triangle.numberVertices = triangle.vertices.size();
    triangle.render = GL_TRIANGLES;

    INIT_SHADER();
    INIT_VAO(&triangle);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        /* Render here */
        glClearColor(r, g, b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(triangle.VAO);   
        // indica come verranno collegati i vertici, a partire da quale vertice devo iniziare, e quanti sono i vertici
        glDrawArrays(GL_TRIANGLES, 0, 3); 

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(programId);
    glDeleteBuffers(1, &triangle.VBO_colors);
    glDeleteBuffers(1, &triangle.VBO_vertices);
    glDeleteVertexArrays(1, &triangle.VAO);
    glfwTerminate();


    return 0;
}



void INIT_SHADER(void)
{
    GLenum ErrorCheckValue = glGetError();

    char* vertexShader = (char*)"vertex_shader_C.glsl";
    char* fragmentShader = (char*)"fragment_shader_C.glsl";

    programId = ShaderMaker::createProgram(vertexShader, fragmentShader);
    glUseProgram(programId);

    /*
    Il vertex shader(vertex_shader_C.glsl) è un programma eseguito su ciascun vertice.Esso si occupa, per esempio, di trasformare la posizione di un vertice da uno spazio 3D a uno spazio 2D(come la trasformazione tra spazio oggetto e spazio schermo).
        Il fragment shader(fragment_shader_C.glsl) viene eseguito su ogni fragment(una rappresentazione di un potenziale pixel) e si occupa di calcolare il colore e altre proprietà visive per ciascun pixel disegnato.

        programId = ShaderMaker::createProgram(vertexShader, fragmentShader); è il punto in cui vengono creati e collegati gli shader :

    La funzione ShaderMaker::createProgram() presumibilmente compila i due shader e li collega in un unico program object che verrà usato dalla GPU per disegnare ciò che sarà specificato nei successivi comandi OpenGL.

        glUseProgram(programId); :

        Questa chiamata attiva il programma shader, il che significa che da questo momento in poi, tutte le operazioni di rendering useranno questo specifico programma shader(quindi il vertex shader e il fragment shader che hai specificato).

        buffer -> vertex -> fragment
    */
}

void INIT_VAO(Figure* fig)
{
    // Genero un Vertex Array Object (VAO) e lo attivo
    glGenVertexArrays(1, &fig->VAO); // Genera 1 VAO e salva il suo identificatore in fig->VAO
    glBindVertexArray(fig->VAO);

    // Creo e configuro il VBO per i vertici
    glGenBuffers(1, &fig->VBO_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_vertices);
    glBufferData(GL_ARRAY_BUFFER, fig->vertices.size() * sizeof(vec3), fig->vertices.data(), GL_STATIC_DRAW);

    // Configuro l'attributo 0: posizione dei vertici
    // Parametri di glVertexAttribPointer:
    // 1. Indice dell'attributo (0 per la posizione)
    // 2. Numero di componenti per vertice (3 per x, y, z)
    // 3. Tipo di dato (GL_FLOAT)
    // 4. Se i dati devono essere normalizzati (GL_FALSE)
    // 5. Stride (0 = i dati sono impaccati sequenzialmente) -> se non 0, quanti byte saltare per leggere la prossima informazione
    // 6. Offset del primo elemento nell'array (0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0); // Abilita l'attributo 0 (posizione)

    // Creo e configuro il VBO per i colori
    glGenBuffers(1, &fig->VBO_colors);
    glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_colors);
    glBufferData(GL_ARRAY_BUFFER, fig->colors.size() * sizeof(vec4), fig->colors.data(), GL_STATIC_DRAW);

    // Configuro l'attributo 1: colore dei vertici
    // Parametri simili a sopra, ma per il colore (4 componenti invece di 3)
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1); // Abilita l'attributo 1 (colore)


    // IN glVertexAttribPointer, ho messo 0 e 1, a piacere...sono per gli shared
}

#pragma region  Roba superflua

void mouse_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        isMouseDown = true;
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        isMouseDown = false;
    }

    std::cout << "isMouseDown " << isMouseDown << std::endl;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    std::cout << "window size is " << width << "x" << height << std::endl;
    glViewport(0.0, 0.0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_F2 && action == GLFW_PRESS) {
        // Cambia il colore dello sfondo
        r = 0.0;
        g = 0.0;
        b = 1.0;
    }
    else {
        // Cambia il colore dello sfondo
        r = 0.0;
        g = 0.0;
        b = 0.0;
    }

}
#pragma endregion