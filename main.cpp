#include <iostream>
#include <cstdlib>
#include <ctime>

// IMPORTANTE: El include de GLAD debe estar siempre ANTES de el de GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"

int main()
{
    std::cout << "Starting Application PAG - Prueba 01" << std::endl;

    // Establecemos una semilla para la aleatoriedad de rand() basada en la hora actual
    std::srand(static_cast<unsigned int>(std::time(0)));

    // - Este callback hay que registrarlo ANTES de llamar a glfwInit
    glfwSetErrorCallback ( (GLFWerrorfun) PAG::Renderer::ErrorGLFW );

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

    // - Interrogamos a OpenGL para que nos informe de las propiedades del contexto 3D construido.
    std::cout << "Propiedades del Contexto 3d: " << std::endl
    <<" - Trajeta Grafica: " << glGetString ( GL_RENDERER ) << std::endl
    <<" - Fabricante de Trajeta Grafica: " << glGetString ( GL_VENDOR ) << std::endl
    <<" - Version de OpenGL: " << glGetString ( GL_VERSION ) << std::endl
    <<" - Version de GLSL: " << glGetString ( GL_SHADING_LANGUAGE_VERSION ) << std::endl << std::endl;

    // - Registramos los callbacks que responderán a los eventos principales
    glfwSetWindowRefreshCallback ( window, PAG::Renderer::RefrescarVentana );
    glfwSetFramebufferSizeCallback ( window, PAG::Renderer::ModificarTamaño );
    glfwSetKeyCallback ( window, PAG::Renderer::TeclaPulsada );
    glfwSetMouseButtonCallback ( window, PAG::Renderer::AccionRaton );
    glfwSetScrollCallback ( window, PAG::Renderer::RuedaRaton );

    // - Establecemos un gris medio como color con el que se borrará el frame buffer.
    // No tiene por qué ejecutarse en cada paso por el ciclo de eventos.
    glClearColor ( 0.6, 0.6, 0.6, 1.0 );

    // - Le decimos a OpenGL que tenga en cuenta la profundidad a la hora de dibujar.
    // No tiene por qué ejecutarse en cada paso por el ciclo de eventos.
    glEnable ( GL_DEPTH_TEST );

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