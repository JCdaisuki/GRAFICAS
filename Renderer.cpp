#include <iostream>
#include <fstream>
#include <sstream>

#include <glad/glad.h>

#include "Renderer.h"


/**
 * @author Juan Carlos González Martínez
 */

PAG::Renderer* PAG::Renderer::instancia = nullptr;

namespace PAG
{
    Renderer* Renderer::GetInstancia ()
    {
        if ( !instancia ) // Lazy initialization: si aún no existe, lo crea
        {
            instancia = new Renderer();
        }

        return instancia;
    }

    void Renderer::InicializarOpenGL()
    {
        glClearColor ( 0.6, 0.6, 0.6, 1.0 ); // - Establecemos un gris medio como color con el que se borrará el frame buffer.
        glEnable(GL_DEPTH_TEST);
        glEnable ( GL_MULTISAMPLE );
    }

    std::string Renderer::MostrarPropiedades()
    {   std::stringstream ss;
        ss << "Propiedades del Contexto 3D:\n"
           << " - Tarjeta Gráfica: " << glGetString(GL_RENDERER) << "\n"
           << " - Fabricante de Tarjeta Gráfica: " << glGetString(GL_VENDOR) << "\n"
           << " - Versión de OpenGL: " << glGetString(GL_VERSION) << "\n"
           << " - Versión de GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n\n";

        return ss.str();
    }

    void Renderer::RefrescarVentana ()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );

        for(int i = 0; i < shaderPrograms.size(); i++)
        {
            if(shaderPrograms[i]->GetIdSP() != 0)
            {
                shaderPrograms[i]->Render();
            }
        }
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

    void Renderer::CreaShaderProgram ( std::string rutaFuenteGLSL )
    {
        for(int i = 0; i < shaderPrograms.size(); i++)
        {
            if(shaderPrograms[i]->GetIdSP() == 0)
            {
                shaderPrograms[i]->AsignarShaders(rutaFuenteGLSL);
                return;
            }
        }

        //No hay ningún ShaderProgram disponible, creamos uno nuevo y lo añadimos al vector
        ShaderProgram* newShaderProgram = new ShaderProgram();
        newShaderProgram->AsignarShaders(rutaFuenteGLSL);
        shaderPrograms.push_back(newShaderProgram);
    }

    void Renderer::CreaModelo(std::string rutaModelo)
    {
        std::ifstream archivo(rutaModelo);
        if (!archivo.good())
        {
            throw std::runtime_error("Error: No se encontró el archivo del modelo en " + rutaModelo);
        }

        Model* newModel = new Model(rutaModelo.data());
        models.push_back(newModel);
    }

    Renderer::~Renderer()
    {
        if (instancia)
        {
            delete instancia;
            instancia = nullptr;
        }

        for(int i = 0; i < models.size(); i++)
        {
            delete models[i];
        }
        models.clear();

        for(int i = 0; i < shaderPrograms.size(); i++)
        {
            delete shaderPrograms[i];
        }
        shaderPrograms.clear();
    }
}