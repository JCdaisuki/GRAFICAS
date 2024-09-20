#include <iostream>
#include <cstdlib>
#include <ctime>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"

namespace PAG
{
    float Renderer::RandomNumber01 ()
    {
        // Genera un valor aleatorio empleando rand()
        // Para asegurar que se encuentre en el rango [0,1] dividimos entre RAND_MAX
        return static_cast<float>(std::rand()) / RAND_MAX;
    }

    // - Esta función callback será llamada cuando GLFW produzca algún error
    void Renderer::ErrorGLFW ( int errno, const char* desc )
    {
        std::string aux (desc);
        std::cout << "Error de GLFW número " << errno << ": " << aux << std::endl;
    }

    // - Esta función callback será llamada cada vez que el área de dibujo OpenGL deba ser redibujada.
    void Renderer::RefrescarVentana ( GLFWwindow *window )
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // - GLFW usa un doble buffer para que no haya parpadeo.
        // Esta orden intercambia el buffer back (que se ha estado dibujando) por el que se mostraba hasta ahora front. Debe ser la última orden de este callback
        glfwSwapBuffers ( window );
        std::cout << "Refresh callback called" << std::endl;
    }

    // - Esta función callback será llamada cada vez que se cambie el tamaño del área de dibujo OpenGL.
    void Renderer::ModificarTamaño ( GLFWwindow *window, int width, int height )
    {
        glViewport ( 0, 0, width, height );
        std::cout << "Resize callback called" << std::endl;
    }

    // - Esta función callback será llamada cada vez que se pulse una tecla dirigida al área de dibujo OpenGL.
    void Renderer::TeclaPulsada ( GLFWwindow *window, int key, int scancode, int action, int mods )
    {
        if ( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
        {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
        std::cout << "Key callback called" << std::endl;
    }

    // - Esta función callback será llamada cada vez que se pulse algún botón del ratón sobre el área de dibujo OpenGL.
    void Renderer::AccionRaton ( GLFWwindow *window, int button, int action, int mods )
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

    // - Esta función callback será llamada cada vez que se mueva la rueda del ratón sobre el área de dibujo OpenGL.
    void Renderer::RuedaRaton ( GLFWwindow *window, double xoffset, double yoffset )
    {
        std::cout << "Movida la rueda del raton " << xoffset
        << " Unidades en horizontal y " << yoffset
        << " unidades en vertical" << std::endl;

        float r = RandomNumber01();
        float g = RandomNumber01();
        float b = RandomNumber01();

        std::cout << " - Cambiado el color a (" << r << ", " << g << ", " << b << ", 1.0)" << std::endl;

        // Cambia el color del fondo a uno generado aleatoriamente
        glClearColor ( r, g, b, 1.0 );

        // Limpia el buffer de color para aplicar el nuevo color de fondo
        glClear(GL_COLOR_BUFFER_BIT);

        // Intercambia el buffer en el que se estaba dibujando por el que se muestra
        glfwSwapBuffers ( window );
    }
}