#include "lib.h"
#include "ShaderMaker.h"
#include "strutture.h" 
#include "inizializzazioni.h"
#include "geometria.h"
#include "gestione_interazioni.h"
 

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "Gui.h"
#define PI 3.14159265358979323
//Variabili globali -------------------------------------------------------------------
unsigned int programId;
float clear_color[3] = { 0.0,1.0,0.0 };
float alpha;
double mousex, mousey;
int height = 800, width = 800;

ViewSetup SetupTelecamera;
PerspectiveSetup SetupProspettiva;
Mesh cubo = {};
mat4 Projection, View;
unsigned MatProj, MatModel, MatView;

float angolo=0.0;
float w_up, h_up;

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
    window = glfwCreateWindow(height, width, "Hello World", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create the window !" << std::endl;
        glfwTerminate(); //Libera le risorse allcoata da glfwInit
        return -1;
    }

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
    INIT_CAMERA_PROJECTION();
    crea_cubo(&cubo);
    INIT_VAO(&cubo);

         


    

    //Registrazione delle funzioni di callback che verranno chiamate quando si verificano
    //  determinati eventi

    //Implementa la chiusura dell'applicazione premendo il tasto Esc  e la modifica del colore dello sfondo con il tasto F2..
    //glfwSetKeyCallback(window, key_callback);

    //Per visualizzare le coordinate del mouse che si muove sulla finestra grafica
    //glfwSetCursorPosCallback(window, cursor_position_callback);

    //Per visualizzare le coordinate individuate dal tasto sinistro premuto
    //glfwSetMouseButtonCallback(window, mouse_button_callback);

    //per visualizzare le dimensioni della finestra ridimensionata

     glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Projection = ortho(0.0f, float(width), 0.0f, float(height));
    MatProj = glGetUniformLocation(programId, "Projection");
    MatModel = glGetUniformLocation(programId, "Model");
    MatView= glGetUniformLocation(programId, "View");

	glEnable(GL_DEPTH_TEST); //abilita il depth buffer, che è un buffer che memorizza la distanza di ciascun pixel dal piano di clipping vicino.


    /* Loop until the user closes the window */

    // Imposta la posizione iniziale del mouse
    int oX = int(float(width) / 2.0);
    int oY = int(float(height) / 2.0);

    // Imposta il cursore in posizione (0,0) e disabilita il movimento naturale
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPos(window, oX, oY);
    //Riabilita il movimento naturale
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    //Per visualizzare le coordinate del mouse che si muove sulla finestra grafica
    // glfwSetCursorPosCallback(window, cursor_position_callback);

    
    Initialize_IMGUI(window);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
         
        /* Render here */
        my_interface();
        
        glClearColor(clear_color[0],clear_color[1],clear_color[2], 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // abilito anche il depth buffer

        angolo = angolo + 0.1;

        //Imposto la matrice di proiezione per la scena da disegnare
        Projection = perspective(radians(SetupProspettiva.fovY), SetupProspettiva.aspect, SetupProspettiva.near_plane, SetupProspettiva.far_plane);


        //Costruisco la matrice di Vista che applicata ai vertici in coordinate del mondo li trasforma nel sistema di riferimento della camera.
        View = lookAt(vec3(SetupTelecamera.position), vec3(SetupTelecamera.target), vec3(SetupTelecamera.upVector));

        //Passo al Vertex Shader il puntatore alla matrice View, che sarà associata alla variabile Uniform mat4 Projection
       //all'interno del Vertex shader. Uso l'identificatio MatView
        glUniformMatrix4fv(MatView, 1, GL_FALSE, value_ptr(View));
        //La matrice di proiezione che mappa il volume di vista in coordinate NDC
        glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
        //Definisco la matrice di modellazione del cubo.
        cubo.Model = mat4(1.0);
        cubo.Model = translate(cubo.Model, vec3(3.5, 0.5, 2.5));
        cubo.Model = scale(cubo.Model, vec3(2.0f, 2.0f, 2.0f));
       cubo.Model = rotate(cubo.Model, radians(angolo), vec3(0.0, 1.0, 0.0));

        glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(cubo.Model));
        glBindVertexArray(cubo.VAO);
        
        ///La funzione glDrawElements è uno strumento fondamentale in OpenGL per rendere primitive grafiche (come triangoli, linee o punti) 
        // utilizzando dati di vertici memorizzati in buffer di vertici (VBO) e indicizzati da un buffer di elementi (EBO).
        //Utilizzando gli indici, possiamo ottimizzare il processo di rendering e creare geometrie complesse con meno dati di vertici.
        //GL_TRIANGLES: Questo parametro specifica il tipo di primitiva da rendere.In questo caso, stiamo rendendo dei triangoli.
        //(cubo.indices.size() - 1) * sizeof(GLuint) : Questo calcola il numero di indici da disegnare.Il termine cubo.indices.size() indica il numero totale di indici, ma sottraiamo 1 perché gli indici sono spesso memorizzati a coppie o triple per definire i triangoli.Moltiplicando per sizeof(GLuint) otteniamo la dimensione in byte.
        //GL_UNSIGNED_INT : Questo specifica il tipo di dato degli indici nel buffer di elementi.In questo caso, sono interi senza segno.
        //0 : Questo è l'offset in byte all'interno del buffer di elementi.In questo caso, iniziamo dall'inizio.
        //Utilizzando gli indici, possiamo ottimizzare il processo di rendering e creare geometrie complesse con meno dati di vertici
        
        glDrawElements(GL_TRIANGLES, (cubo.indices.size() - 1) * sizeof(GLuint), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);




        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); // Renderizza i dati di disegno di ImGui

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

     close_GUI();

  

    glfwTerminate();


    return 0;
}





