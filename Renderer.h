/**
 * @author Juan Carlos González Martínez
 */

namespace PAG
{
    class Renderer
    {
        private:
            // Puntero al único objeto
            static Renderer* instancia;

            // - Función auxiliar que devuelve un número aleatorio en el rango [0, 1]
            static float RandomNumber01 ();

        public:
            // - Getter de instancia
            static Renderer* getInstancia ();
        
            // - Esta función callback será llamada cuando GLFW produzca algún error
            static void ErrorGLFW ( int errno, const char* desc );

            // - Esta función callback será llamada cada vez que el área de dibujo OpenGL deba ser redibujada.
            static void RefrescarVentana ( GLFWwindow *window );

            // - Esta función callback será llamada cada vez que se cambie el tamaño del área de dibujo OpenGL.
            static void ModificarTamaño ( GLFWwindow *window, int width, int height );

            // - Esta función callback será llamada cada vez que se pulse una tecla dirigida al área de dibujo OpenGL.
            static void TeclaPulsada ( GLFWwindow *window, int key, int scancode, int action, int mods );

            // - Esta función callback será llamada cada vez que se pulse algún botón del ratón sobre el área de dibujo OpenGL.
            static void AccionRaton ( GLFWwindow *window, int button, int action, int mods );

            // - Esta función callback será llamada cada vez que se mueva la rueda del ratón sobre el área de dibujo OpenGL.
            static void RuedaRaton ( GLFWwindow *window, double xoffset, double yoffset );
    };
}