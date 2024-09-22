#include <iostream>
#include <cstdlib>

#include <glad/glad.h>

#include "Renderer.h"

/**
 * @author Juan Carlos González Martínez
 */

PAG::Renderer* PAG::Renderer::instancia = nullptr;

namespace PAG
{
    float Renderer::RandomNumber01 ()
    {
        // Genera un valor aleatorio empleando rand()
        // Para asegurar que se encuentre en el rango [0,1] dividimos entre RAND_MAX
        return static_cast<float>(std::rand()) / RAND_MAX;
    }

    void Renderer::RandomColor()
    {
        r = RandomNumber01();
        g = RandomNumber01();
        b = RandomNumber01();
        a = RandomNumber01();
    }

    PAG::Renderer* PAG::Renderer::GetInstancia ()
    {
        if ( !instancia ) // Lazy initialization: si aún no existe, lo crea
        {
            instancia = new Renderer();
        }

        return instancia;
    }

    void Renderer::InicializarOpenGL()
    {
        // - Establecemos un gris medio como color con el que se borrará el frame buffer.
        glClearColor ( 0.6, 0.6, 0.6, 1.0 );
        glEnable(GL_DEPTH_TEST);
    }

    void Renderer::MostrarPropiedades()
    {
        std::cout << "Propiedades del Contexto 3d: " << std::endl
        <<" - Trajeta Grafica: " << glGetString ( GL_RENDERER ) << std::endl
        <<" - Fabricante de Trajeta Grafica: " << glGetString ( GL_VENDOR ) << std::endl
        <<" - Version de OpenGL: " << glGetString ( GL_VERSION ) << std::endl
        <<" - Version de GLSL: " << glGetString ( GL_SHADING_LANGUAGE_VERSION ) << std::endl << std::endl;
    }

    void Renderer::RefrescarVentana ()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::ModificarTamaño (int width, int height )
    {
        glViewport ( 0, 0, width, height );
    }

    void Renderer::RuedaRaton (double xoffset, double yoffset)
    {
        // Debemos emplear la instancia para poder acceder a las funciones y atributos no estáticos.
        Renderer* instancia = Renderer::GetInstancia();

        // Cambia el color de fondo a uno generado aleatoriamente
        instancia->RandomColor();
        glClearColor(instancia->r, instancia->g, instancia->b, instancia->a);

        // Limpia el buffer de color para aplicar el nuevo color de fondo
        glClear(GL_COLOR_BUFFER_BIT);
    }
}