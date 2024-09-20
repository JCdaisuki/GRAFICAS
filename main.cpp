#include <iostream>
#include <cstdlib>
#include <ctime>

// IMPORTANTE: El include de GLAD debe estar siempre ANTES de el de GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"

/**
 * @author Juan Carlos González Martínez
 */

// - Esta función callback será llamada cuando GLFW produzca algún error
void callbackErrorGLFW ( int errno, const char* desc )
{
    std::string aux (desc);
    std::cout << "Error de GLFW número " << errno << ": " << aux << std::endl;
}

// - Esta función callback será llamada cada vez que el área de dibujo OpenGL deba ser redibujada.
void callbackRefrescoVentana ( GLFWwindow* window )
{
    PAG::Renderer::getInstancia()->RefrescarVentana();

    // - GLFW usa un doble buffer para que no haya parpadeo.
    // Esta orden intercambia el buffer back (que se ha estado dibujando) por el que se mostraba hasta ahora front. Debe ser la última orden de este callback
    // glfwSwapBuffers ( window );
    // std::cout << "Refresh callback called" << std::endl;
    glfwSwapBuffers (window);

    std::cout << "Finaliza el callback de refresco" << std::endl;
}

// - Esta función callback será llamada cada vez que se pulse una tecla dirigida al área de dibujo OpenGL.
void callbackTeclaPulsada ( GLFWwindow *window, int key, int scancode, int action, int mods )
{
    if ( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    std::cout << "Key callback called" << std::endl;
}

// - Esta función callback será llamada cada vez que se pulse algún botón del ratón sobre el área de dibujo OpenGL.
void callbackAccionRaton ( GLFWwindow *window, int button, int action, int mods )
{
    if ( action == GLFW_PRESS )
    {
        std::cout << "Pulsado el boton: " << button << std::endl;
    }
    else if ( action == GLFW_RELEASE )
    {
        std::cout << "Soltado el boton: " << button << std::endl;
    }
}

void callbackModificarTamaño(GLFWwindow *window, int width, int height )
{
    PAG::Renderer::ModificarTamaño(width, height);

    std::cout << "Resize callback called" << std::endl;
}

void callbackRuedaRaton ( GLFWwindow *window, double xoffset, double yoffset )
{
    std::cout << "Movida la rueda del raton " << xoffset
    << " Unidades en horizontal y " << yoffset
    << " unidades en vertical" << std::endl;

    PAG::Renderer::RuedaRaton(xoffset, yoffset);

    // Intercambia el buffer en el que se estaba dibujando por el que se muestra
    glfwSwapBuffers ( window );
}

int main()
{
    std::cout << "Starting Application PAG - Prueba 01" << std::endl;

    // Establecemos una semilla para la aleatoriedad de rand() basada en la hora actual
    std::srand(static_cast<unsigned int>(std::time(0)));

    // - Este callback hay que registrarlo ANTES de llamar a glfwInit
    glfwSetErrorCallback ( (GLFWerrorfun) callbackErrorGLFW );

    // - Inicializa GLFW. Es un proceso que sólo debe realizarse una vez en la aplicación
    if ( glfwInit () != GLFW_TRUE )
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // - Definimos las características que queremos que tenga el contexto gráfico
    // OpenGL de la ventana que vamos a crear. Por ejemplo, el número de muestras o el modo Core Profile.
    glfwWindowHint ( GLFW_SAMPLES, 4 ); // - Activa antialiasing con 4 muestras.
    glfwWindowHint ( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE ); // - Esta y las 2
    glfwWindowHint ( GLFW_CONTEXT_VERSION_MAJOR, 4 ); // siguientes activan un contexto
    glfwWindowHint ( GLFW_CONTEXT_VERSION_MINOR, 1 ); // OpenGL Core Profile 4.1.

    // - Definimos el puntero para guardar la dirección de la ventana de la aplicación y la creamos
    GLFWwindow *window;

    // - Tamaño, título de la ventana, en ventana y no en pantalla completa, sin compartir recursos con otras ventanas.
    window = glfwCreateWindow ( 1024, 576, "PAG Introduction", nullptr, nullptr );

    // - Comprobamos si la creación de la ventana ha tenido éxito.
    if ( window == nullptr )
    {
        std::cout << "Failed to open GLFW window" << std::endl;
        glfwTerminate (); // - Liberamos los recursos que ocupaba GLFW.
        return -2;
    }

    // - Hace que el contexto OpenGL asociado a la ventana que acabamos de crear pase a ser el contexto actual de OpenGL para las siguientes llamadas a la biblioteca
    glfwMakeContextCurrent ( window );

    // - Ahora inicializamos GLAD.
    if ( !gladLoadGLLoader ( (GLADloadproc) glfwGetProcAddress ) )
    {
        std::cout << "GLAD initialization failed" << std::endl;
        glfwDestroyWindow ( window ); // - Liberamos los recursos que ocupaba GLFW.
        window = nullptr;
        glfwTerminate ();
        return -3;
    }

    PAG::Renderer::MostrarPropiedades();

    // - Registramos los callbacks que responderán a los eventos principales
    glfwSetWindowRefreshCallback ( window, callbackRefrescoVentana );
    glfwSetFramebufferSizeCallback ( window, callbackModificarTamaño);
    glfwSetKeyCallback ( window, callbackTeclaPulsada );
    glfwSetMouseButtonCallback ( window, callbackAccionRaton );
    glfwSetScrollCallback ( window, callbackRuedaRaton );

    PAG::Renderer::InicializarOpenGL();

    // - Ciclo de eventos de la aplicación. La condición de parada es que la ventana principal deba cerrarse, por ejemplo, si el usuario pulsa el  botón de cerrar la ventana (X).
    while ( !glfwWindowShouldClose ( window ) )
    {
        // - Obtiene y organiza los eventos pendientes, tales como pulsaciones de teclas o de ratón, etc.
        // Siempre al final de cada iteración del ciclo de eventos y después de glfwSwapBuffers ( window );
        glfwPollEvents ();
    }

    // - Una vez terminado el ciclo de eventos, liberar recursos, etc.
    std::cout << "Finishing application pag prueba" << std::endl;

    glfwDestroyWindow ( window ); // - Cerramos y destruimos la ventana de la aplicación.
    window = nullptr;
    glfwTerminate (); // - Liberamos los recursos que ocupaba GLFW.
}