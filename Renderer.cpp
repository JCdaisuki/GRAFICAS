#include <iostream>
#include <cstdlib>

#include <glad/glad.h>

#include "Renderer.h"
#include "GUI.h"

/**
 * @author Juan Carlos González Martínez
 */

PAG::Renderer* PAG::Renderer::instancia = nullptr;

namespace PAG
{
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

    std::string Renderer::MostrarPropiedades()
    {
        std::string propiedades =
            "Propiedades del Contexto 3D:\n" +
            std::string(" - Tarjeta Gráfica: ") + reinterpret_cast<const char*>(glGetString(GL_RENDERER)) + "\n" +
            std::string(" - Fabricante de Tarjeta Gráfica: ") + reinterpret_cast<const char*>(glGetString(GL_VENDOR)) + "\n" +
            std::string(" - Versión de OpenGL: ") + reinterpret_cast<const char*>(glGetString(GL_VERSION)) + "\n" +
            std::string(" - Versión de GLSL: ") + reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION)) + "\n\n";

        return propiedades;
    }

    void Renderer::RefrescarVentana ()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::ModificarTamaño (int width, int height )
    {
        glViewport ( 0, 0, width, height );
    }

    void Renderer::CambiarColorFondo (float* color)
    {
        //Cambia el color de fondo al recibido como parámetro
        glClearColor(color[0],color[1],color[2],color[3]);

        // Limpia el buffer de color para aplicar el nuevo color de fondo
        glClear(GL_COLOR_BUFFER_BIT);
    }

    PAG::Renderer::~Renderer()
    {
        if (instancia)
        {
            delete instancia;
            instancia = nullptr;
        }
    }
}