#include "lib.h"
#include "ShaderMaker.h"
#include "strutture.h" 
#include "inizializzazioni.h"
#include "init_geometrie.h"
#include "gestione_interazioni.h"

#define _USE_MATH_DEFINES
#include "math.h"


//Variabili globali -------------------------------------------------------------------
unsigned int programId;
unsigned int altezza = 1000;
unsigned int larghezza = 1000;
float r = 0.0, g = 1.0, b = 1.0;
double mouse_x;
double mouse_y;

double xpos, ypos;
Figura triangolo = {  };  //crea una nuova istanza della struttura Figura di nome  "triangolo".

float cx= 0.0;
float cy = 0.0;
float raggiox = 0.1f;
float raggioy = 0.1f;
Figura cerchio = { };
Figura cuore = {};

vector<Figura*> scena;
//----------------------------------------------------------------------------------------

static void mouse_position(GLFWwindow* windows, double posx, double posy) {
    mouse_x = posx;
    mouse_y = posy;
 }

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())   //se glfwInit() dà valore falso, return -1
        return -1;

    //Imposta le proprietà del contesto e del profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Abilita il double buffering

    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(altezza, larghezza, "Hello World", NULL, NULL);
    if (!window)
    {
        std::cout << "Failde to create the window !" << std::endl;
        glfwTerminate(); //Libera le risorse allcoata da glfwInit
        return -1;
    }

    glfwSetCursorPosCallback(window, mouse_position);

    /* Make the window's context current */
    glfwMakeContextCurrent(window); //crea il context corrente e lo associa a window. In opengl un rendering context è una macchina astati che memorizza tutte le informazioni necessarie e le risorse per il rendering grafico

    //verifica se la libreria GLAD è riuscita a caricare correttamente tutti i puntatori 
    // alle funzioni OpenGL necessarie.

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failde to load opengl function pointers !" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    INIT_SHADER();

    scena.push_back(&triangolo);
    //scena.push_back(&cerchio);
    scena.push_back(&cuore);

    //Costruisce i vertici del triangolo: attributo posizione e colore
    INIT_TRIANGLE(&triangolo);  // Viene passato l'indirizzo di memoria della struttura triangolo.
    //Genera il VAO della struttura  triangolo
 

 
    cuore.nTriangles = 300;
    INIT_HEART(&cuore, 0.01, cx,cy);
 

    for (Figura* fig : scena) {
        INIT_VAO(fig);
    }

    cerchio.nTriangles = 300;
    INIT_CIRCLE(&cerchio, cx, cy, raggiox, raggioy);
    INIT_VAO_DYNAMIC(&cerchio);
  





    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        /* Render here */
        glClearColor(r,g,b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);



        //Questa istruzione effettua il disegno vero e proprio utilizzando il program shader programId
        //GL_TRIANGLES: Indica che i vertici nel buffer devono essere interpretati come triangoli.
        //0 : Indica l'indice del primo vertice da utilizzare.
        //3 : Indica il numero di vertici da utilizzare.
        glDrawArrays(GL_TRIANGLES, 0, 3);
                
        //Questa istruzione "lega" o "attiva" il Vertex Array Object (VAO) di triangolo .
  

      
        float currentiTime = glfwGetTime();
        raggiox = sin(currentiTime * 2.0 * M_PI) * 0.25 + 0.75;
        raggioy = sin(currentiTime * 2.0 * M_PI) * 0.25 + 0.75;


        cx = (2.0 / larghezza) * mouse_x -1;
        cy = (2.0 / altezza) * (-mouse_y) +1;


        INIT_CIRCLE(&cerchio, cx, cy, raggiox, raggioy);
   
        glBindBuffer(GL_ARRAY_BUFFER, cerchio.VBO_vertices);
        glBufferSubData(GL_ARRAY_BUFFER,0,cerchio.vertices.size()*sizeof(vec3), cerchio.vertices.data());
        glBindVertexArray(cerchio.VAO);
        glDrawArrays(cerchio.render, 0, cerchio.nv);

        cerchio.vertices.clear();
        cerchio.colors.clear();


        for (Figura* fig : scena) {
            glBindVertexArray(fig->VAO);
            glDrawArrays(fig->render, 0, fig->nv);
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(programId);


    for (Figura* fig : scena) {
        glDeleteBuffers(1, &fig->VBO_vertices);
        glDeleteBuffers(1, &fig->VBO_colors);
        glDeleteVertexArrays(1, &fig->VAO);
    }
    glfwTerminate();


    return 0;
}

 


 
 