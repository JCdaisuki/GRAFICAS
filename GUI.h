#include <GLFW/glfw3.h>

/**
* @author Juan Carlos González Martínez
 */

namespace PAG
{
    class GUI
    {
        private:
            // Puntero al único objeto
            static GUI* instancia;

            //Posicion x e y de las ventanas
            int mx = 10, my = 20;
            int cx = 10, cy = 130;

            //Color de fondo y color seleccionado en la ventana "Fondo"
            float colorFondo[4] = {0.0, 0.0, 0.0, 0.0};
            float colorSeleccionado[4] = {0.0, 0.0, 0.0, 0.0};

            //Último mensaje escrito en la ventana Mensajes
            std::string lastMensaje = "Inicializada la Ventana Mensajes";

            // - Estas funciones crean las ventanas auxiliares dentro de la ventana principal
            void CrearVentanaMensajes(std::string mensaje);
            void CrearVentanaColores();

        public:
            // - Getter de instancia
            static GUI* GetInstancia ();
            float* GetColorFondo();

            //Setters de las posiciones x e y de la ventana mensajes
            void SetMensajeX(int newMX){ mx = newMX;}
            void SetMensajeY(int newMY){ my = newMY;}

            void InicializarImGui(GLFWwindow* window);

            //- Esta función redibuja la interfaz cada vez que se refresque la imagen
            void RedibujarVentanas(std::string mensaje = "");

            // - Esta función comprueba si se ha seleccionado un nuevo color en la ventana "Fondo"
            bool CambioColor();
    };
}
