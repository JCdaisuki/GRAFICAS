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
        glDepthFunc ( GL_LEQUAL );
        glEnable ( GL_MULTISAMPLE );

        InicializarLuces();
    }

    void Renderer::InicializarLuces()
    {
        glEnable(GL_BLEND);

        lights.push_back(new Light(Light::LightType::Ambiente, glm::vec3(0.2f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f)));
/*
        lights.push_back(new Light(Light::LightType::Puntual, glm::vec3(1.0f, 0.5f, 0.3f), glm::vec3(1.0f), glm::vec3(5.0f, 3.0f, 5.0f), glm::vec3(0.0f)));
        lights.push_back(new Light(Light::LightType::Direccional, glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f), glm::vec3(0.0f), glm::vec3(-1.0f, -1.0f, -1.0f)));
        lights.push_back(new Light(Light::LightType::Foco, glm::vec3(1.0f, 1.0f, 0.8f), glm::vec3(1.0f), glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
*/
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

        if(models.empty())
        {
            return;
        }

        for(int l = 0; l < lights.size(); l++)
        {
            if(l == 0)
            {
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            }
            else
            {
                glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            }

            for(int i = 0; i < models.size(); i++)
            {
                glPolygonMode(GL_FRONT_AND_BACK, models[i]->GetPolygonMode());

                if(shaderPrograms.size() > 0)
                {
                    ShaderProgram* shaderProgram = shaderPrograms[models[i]->GetIndexSP()];

                    GLuint idSP = shaderProgram->GetIdSP();
                    glUseProgram(idSP);

                    GLuint indices[] = {0, 0};
                    glm::vec4 color={0,0,0,1};

                    EstablecerColorModel(models[i], indices, color);
                    EstablecerLucesModel(models[i], lights[l]->GetType(), indices);

                    glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 2, indices);

                    if(color != glm::vec4(-1.0f))
                    {
                        GLint location = glGetUniformLocation(shaderPrograms[models[i]->GetIndexSP()]->GetIdSP(), "colorDifuso");

                        if (location == -1)
                        {
                            throw std::runtime_error("No se pudo encontrar 'colorDifuso' en el Shader " + shaderPrograms[models[i]->GetIndexSP()]->GetRuta());
                        }

                        glUniform4fv(location, 1, &color[0]);
                    }

                    shaderProgram->SetProjectionMatrix(Camera::GetInstancia()->GetProjectionMatrix());
                    shaderProgram->SetViewAndModelMatrix(Camera::GetInstancia()->GetViewMatrix(), models[i]->GetModelMatrix());
                    shaderProgram->SetNormalMatrix();

                    glBindVertexArray(models[i]->GetIdVAO());

                    glDrawElements(GL_TRIANGLES, models[i]->GetNumIndices(), GL_UNSIGNED_INT, nullptr);

                    glBindVertexArray(0);
                }
            }
        }
    }

    void Renderer::EstablecerColorModel(Model* model, GLuint* indices, glm::vec4& color)
    {
        std::string subrutina;

        if(model->GetModoVisualizacion() == Model::ModoVisualizacion::ModoAlambre)
        {
            subrutina = "colorNegro";
            color = glm::vec4(-1.0f);
        }
        else if(model->GetModoVisualizacion() == Model::ModoVisualizacion::ModoPlano) //ESTABLECEMOS EL COLOR DIFUSO DEL MATERIAL
        {
            subrutina = "colorDifusoMaterial";
            color = model->GetMaterial()->getColorDifuso();
        }

        GLuint indexImplementacion = glGetSubroutineIndex(shaderPrograms[model->GetIndexSP()]->GetIdSP(), GL_FRAGMENT_SHADER, subrutina.c_str());

        if (indexImplementacion == GL_INVALID_INDEX)
        {
            throw std::runtime_error("No se pudo encontrar la implementación "+ subrutina + " en el Shader " + shaderPrograms[model->GetIndexSP()]->GetRuta());
        }

        GLuint indexSubrutina = glGetSubroutineUniformLocation ( shaderPrograms[model->GetIndexSP()]->GetIdSP(), GL_FRAGMENT_SHADER, "metodoColorElegido" );

        indices[indexSubrutina] = indexImplementacion;
    }

    void Renderer::EstablecerLucesModel(Model *model, Light::LightType type, GLuint* indices)
    {
        GLuint indexSubrutinaLight;

        switch (type)
        {
            case Light::Ambiente:
                indexSubrutinaLight = glGetSubroutineIndex(shaderPrograms[model->GetIndexSP()]->GetIdSP(), GL_FRAGMENT_SHADER, "calculateAmbient");
                break;

            case Light::Puntual:
                indexSubrutinaLight = glGetSubroutineIndex(shaderPrograms[model->GetIndexSP()]->GetIdSP(), GL_FRAGMENT_SHADER, "calculatePointLight");
                break;

            case Light::Direccional:
                indexSubrutinaLight = glGetSubroutineIndex(shaderPrograms[model->GetIndexSP()]->GetIdSP(), GL_FRAGMENT_SHADER, "calculateDirectionalLight");
                break;

            case Light::Foco:
                indexSubrutinaLight = glGetSubroutineIndex(shaderPrograms[model->GetIndexSP()]->GetIdSP(), GL_FRAGMENT_SHADER, "calculateSpotLight");
                break;

            default:
                return;;
        }

        indices[indexSubrutinaLight] = indexSubrutinaLight;
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

        for(int i = 0; i < lights.size(); i++)
        {
            delete lights[i];
        }
        lights.clear();

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

        for(int i = 0; i < materials.size(); i++)
        {
            delete materials[i];
        }
        materials.clear();
    }
}