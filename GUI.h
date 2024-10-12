#include <vector>
#include <GLFW/glfw3.h>

/**
* @author Juan Carlos González Martínez
 */

#ifndef Gui_h
#define Gui_h

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
            int sx = 10, sy = 370;
            int cax = 620, cay = 20;

            //Color de fondo y color seleccionado en la ventana "Fondo"
            float colorFondo[4] = {0.0, 0.0, 0.0, 0.0};
            float colorSeleccionado[4] = {0.0, 0.0, 0.0, 0.0};

            //Vector de mensajes
            std::pmr::vector<std::string> mensajes;

            //Nombre del archivo de shaders a cargar
            std::string shaderArchivo = "";
            char buffer[256];

            // - Estas funciones crean las ventanas auxiliares dentro de la ventana principal
            void CrearVentanaMensajes(std::string mensaje);
            void CrearVentanaColores();
            void CrearVentanaShaders();
            void CrearVentanaCamera();

        public:
            // - Getter de instancia
            static GUI* GetInstancia ();
            float* GetColorFondo();

            //Setters de las posiciones x e y de la ventana mensajes
            void SetMensajeX(int newMX){ mx = newMX;}
            void SetMensajeY(int newMY){ my = newMY;}

            void ResetShaderArchivo(){shaderArchivo = "";}

            void InicializarImGui(GLFWwindow* window);

            //- Esta función redibuja la interfaz cada vez que se refresque la imagen
            void RedibujarVentanas(std::string mensaje = "");

            // - Esta función comprueba si se ha seleccionado un nuevo color en la ventana "Fondo"
            bool CambioColor();

            void FinalizarImGui();

            ~GUI();
    };
}

#endif