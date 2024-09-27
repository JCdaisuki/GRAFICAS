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

    void PAG::Renderer::creaShaderProgram( )
    {
        std::string miVertexShader =
            "#version 410\n"
            "layout (location = 0) in vec3 posicion;\n"
            "void main ()\n"
            "{ gl_Position = vec4 ( posicion, 1 );\n"
            "}\n";

        std::string miFragmentShader =
            "#version 410\n"
            "out vec4 colorFragmento;\n"
            "void main ()\n"
            "{ colorFragmento = vec4 ( 1.0, .4, .2, 1.0 );\n"
            "}\n";

        idVS = glCreateShader ( GL_VERTEX_SHADER );
        const GLchar* fuenteVS = miVertexShader.c_str ();
        glShaderSource ( idVS, 1, &fuenteVS, nullptr );
        glCompileShader ( idVS );

        idFS = glCreateShader ( GL_FRAGMENT_SHADER );
        const GLchar* fuenteFS = miFragmentShader.c_str ();
        glShaderSource ( idFS, 1, &fuenteFS, nullptr );
        glCompileShader ( idFS );

        idSP = glCreateProgram ();
        glAttachShader ( idSP, idVS );
        glAttachShader ( idSP, idFS );
        glLinkProgram ( idSP );
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