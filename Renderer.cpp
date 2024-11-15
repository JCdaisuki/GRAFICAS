#include <iostream>
#include <fstream>
#include <sstream>

#include <glad/glad.h>

#include "Renderer.h"
#include "Camera.h"

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
    {
        std::stringstream ss;
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

        for(int i = 0; i < models.size(); i++)
        {
            glPolygonMode(GL_FRONT_AND_BACK, models[i]->GetPolygonMode());

            if(shaderPrograms.size() > 0)
            {
                ShaderProgram* aux = shaderPrograms[models[i]->GetIndexSP()];
                GLuint idSP = aux->GetIdSP();
                glUseProgram(idSP);

                aux->SetViewMatrix(Camera::GetInstancia()->GetViewMatrix());
                aux->SetProjectionMatrix(Camera::GetInstancia()->GetProjectionMatrix());

                glBindVertexArray(models[i]->GetIdVAO());

                glDrawElements(GL_TRIANGLES, models[i]->GetNumIndices(), GL_UNSIGNED_INT, nullptr);

                glBindVertexArray(0);
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

            if(shaderPrograms[i]->GetRuta() == rutaFuenteGLSL)
            {
                models[models.size()-1]->SetIndexSP ( i );
                return;
            }
        }

        //No hay ningún ShaderProgram disponible, creamos uno nuevo y lo añadimos al vector
        ShaderProgram* newShaderProgram = new ShaderProgram();

        try
        {
            newShaderProgram->AsignarShaders(rutaFuenteGLSL);
        }
        catch (std::runtime_error error)
        {
            delete newShaderProgram;
            throw error;
        }

        if ( models.size() > 0 )
        {
            models[models.size()-1]->SetIndexSP ( shaderPrograms.size() );
        }
        else
        {
            delete newShaderProgram;
            throw std::runtime_error("No hay ningún modelo cargado");
        }

        shaderPrograms.push_back(newShaderProgram);
    }

    void Renderer::CreaModelo(std::string rutaModelo, std::string nombreModelo)
    {
        std::ifstream archivo(rutaModelo);
        if (!archivo.good())
        {
            throw std::runtime_error("Error: No se encontró el archivo del modelo en " + rutaModelo);
        }

        Model* newModel = new Model(rutaModelo.data(), nombreModelo);
        models.push_back(newModel);

        //ASIGNAR UN MATERIAL POR DEFECTO (POR AHORA)
        if(materials.size() == 0)
        {
            materials.push_back(new Material());
        }
        newModel->SetMaterial(materials[0]);
    }

    Model *Renderer::GetModelo(std::string nombreModelo)
    {
        for(int i = 0; i < models.size(); i++)
        {
            if(models[i]->GetNombreModelo() == nombreModelo)
            {
                return models[i];
            }
        }

        throw std::runtime_error("Modelo " + nombreModelo + " no encontrado");
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