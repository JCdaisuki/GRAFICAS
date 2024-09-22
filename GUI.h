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

    public:
            // - Getter de instancia
            static GUI* GetInstancia ();

            void InicializarImGui(GLFWwindow* window);

            //- Esta función redibuja la interfaz cada vez que se refresque la imagen
            void RedibujarVentana();

            // - Esta función crea nuevas ventanas dentro de la ventana principal
            void CrearVentanaMensajes(int x, int y);
    };
}