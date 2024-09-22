/**
* @author Juan Carlos González Martínez
 */

namespace PAG
{
    class GUI
    {

        public:
            void InicializarImGui(GLFWwindow* window);

            //- Esta función redibuja la interfaz cada vez que se refresque la imagen
            void RedibujarVentana();
    };
}