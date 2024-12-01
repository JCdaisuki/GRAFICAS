/**
* @author Juan Carlos González Martínez
 */

#ifndef Gui_h
#define Gui_h

#include <string>
#include <vector>
#include <GLFW/glfw3.h>

namespace PAG
{
    class GUI
    {
        private:
            // Puntero al único objeto
            static GUI* instancia;

            //Posicion x e y de las ventanas
            int mx = 10, my = 20;
            int cx = 10, cy = 140;
            int sx = 830, sy = 20;
            int cax = 620, cay = 20;

            //Color de fondo y color seleccionado en la ventana "Fondo"
            float colorFondo[4] = {0.0, 0.0, 0.0, 0.0};
            float colorSeleccionado[4] = {0.0, 0.0, 0.0, 0.0};

            //Vector de mensajes
            std::vector<std::string> mensajes;

            char bufferModel[256];
            std::string modelArchivo = ""; //Nombre del archivo del modelo a cargar
            std::string nombreModelo = "";

            int modeloSeleccionado = 0;
            std::vector<std::string> modelosCargados;

            char bufferShader[256];
            std::string shaderArchivo = ""; //Nombre del archivo de shaders a cargar

            bool isShader; //Este booleano permitirá saber si el archivo lanzado es de un shader o un modelo

            // - Estas funciones crean las ventanas auxiliares dentro de la ventana principal
            void CrearVentanaMensajes();
            void CrearVentanaColores();
            void CrearVentanaModelShaders();
            void CrearVentanaCamera();
            void CrearVentanaModelTrans();

            //Auxiliares del Menu de Cámara
            std::string menuSeleccionado = "";
            std::string movementText = "";
            int zoom = 0;

            //Auxiliares del Menu de Transformaciones
            std::string transformacionSeleccionada = "";
            std::string ejeSeleccionado = "";

        public:
            // - Getter de instancia
            static GUI* GetInstancia ();
            float* GetColorFondo();

            bool GetIsShader(){return isShader;}

            //Setters de las posiciones x e y de la ventana mensajes
            void SetMensajeX(int newMX){ mx = newMX;}
            void SetMensajeY(int newMY){ my = newMY;}

            void ResetShaderArchivo(){shaderArchivo = "";}
            void ResetModelArchivo(){modelArchivo = "";}

            void InicializarImGui(GLFWwindow* window);

            //- Esta función redibuja la interfaz cada vez que se refresque la imagen
            std::string RedibujarVentanas();
            void finalizaRedibujarVentanas ();

            // - Esta función comprueba si se ha seleccionado un nuevo color en la ventana "Fondo"
            bool CambioColor();

            void modeloCreadoCorrectamente();

            void LimpiarRutas();

            void FinalizarImGui();

            void addMensaje ( std::string mensaje );

            ~GUI();
    };
}

#endif