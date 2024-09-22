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

            //Posicion x e y de la ventana Mensajes
            int mx = 10, my = 20;

            //Último mensaje escrito en la ventana Mensajes
            std::string lastMensaje = "Inicializada la Ventana Mensajes";

            // - Esta función crea nuevas ventanas dentro de la ventana principal
            void CrearVentanaMensajes(std::string mensaje);

    public:
        // - Getter de instancia
        static GUI* GetInstancia ();

        //Setters de las posiciones x e y de la ventana mensajes
        void SetMesajeX(int newMX){ mx = newMX;}
        void SetMesajeY(int newMY){ my = newMY;}

        void InicializarImGui(GLFWwindow* window);

        //- Esta función redibuja la interfaz cada vez que se refresque la imagen
        void RedibujarVentanas(std::string mensaje);
    };
}
