#include <iostream>
#include <fstream>
#include <sstream>

#include <glad/glad.h>

#include "Renderer.h"

#include <glm/gtc/type_ptr.inl>

#include "Camera.h"
#include "GUI.h"

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

        lights.push_back(new Light(Light::LightType::Ambiente, glm::vec3(0.502f, 0.0f, 0.502f), glm::vec3(1.0f), glm::vec3(0.0f), glm::vec3(0.0f)));
        lights.push_back(new Light(Light::LightType::Puntual, glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(5.0f, 3.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f)));
        lights.push_back(new Light(Light::LightType::Direccional, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
        lights.push_back(new Light(Light::LightType::Foco,glm::vec3(0.0, 0.0, 1.0),glm::vec3(1.0f, 0.0f, 0.0f),glm::vec3(0.0f, 1.0f, 0.0f),glm::vec3(0.0f, -1.0f, 0.0f)));
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

                    EstablecerColorModel(models[i], indices, idSP);
                    EstablecerLucesModel(models[i], lights[l], indices, idSP);

                    glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 2, indices);

                    shaderProgram->SetProjectionMatrix(Camera::GetInstancia()->GetProjectionMatrix());
                    shaderProgram->SetViewAndModelMatrix(Camera::GetInstancia()->GetViewMatrix(), models[i]->GetModelMatrix());
                    shaderProgram->SetNormalMatrix();

                    models[i]->DibujarTextura(idSP);

                    glBindVertexArray(models[i]->GetIdVAO());

                    glDrawElements(GL_TRIANGLES, models[i]->GetNumIndices(), GL_UNSIGNED_INT, nullptr);

                    glBindVertexArray(0);
                }
            }
        }
    }

    void Renderer::EstablecerColorModel(Model* model, GLuint* indices, GLuint idSP)
    {
        std::string subrutina;

        glUniform3fv(glGetUniformLocation(idSP, "Ka"), 1, glm::value_ptr(model->GetMaterial()->getColorAmbiente()));
        glUniform3fv(glGetUniformLocation(idSP, "Kd"), 1, glm::value_ptr(model->GetMaterial()->getColorDifuso()));
        glUniform3fv(glGetUniformLocation(idSP, "Ks"), 1, glm::value_ptr(model->GetMaterial()->getColorEspecular()));
        glUniform1f(glGetUniformLocation(idSP, "ns"), model->GetMaterial()->getBrillo());

        if(model->GetModoVisualizacion() == Model::ModoVisualizacion::ModoAlambre)
        {
            subrutina = "colorNegro";
        }
        else if(model->GetModoVisualizacion() == Model::ModoVisualizacion::ModoPlano) //ESTABLECEMOS EL COLOR DIFUSO DEL MATERIAL
        {
            subrutina = "colorDifusoMaterial";
        }
        else if(model->GetModoVisualizacion() == Model::ModoVisualizacion::ModoTextura)
        {
            subrutina = "colorTexturaMaterial";
        }

        GLuint indexImplementacion = glGetSubroutineIndex(idSP, GL_FRAGMENT_SHADER, subrutina.c_str());

        if (indexImplementacion == GL_INVALID_INDEX)
        {
            throw std::runtime_error("No se pudo encontrar la implementación "+ subrutina + " en el Shader " + shaderPrograms[model->GetIndexSP()]->GetRuta());
        }

        GLuint indexSubrutina = glGetSubroutineUniformLocation ( idSP, GL_FRAGMENT_SHADER, "metodoColorElegido" );

        indices[indexSubrutina] = indexImplementacion;
    }

    void Renderer::EstablecerLucesModel(Model *model, Light *light, GLuint* indices, GLuint idSP)
    {
        if(!light->GetIsOn())
        {
            if (light->GetType() == Light::Ambiente) //Eliminar información de la luz ambiente en el shader
            {
                glUniform3fv(glGetUniformLocation(idSP, "Ia"), 1, glm::value_ptr(glm::vec3(0.0f)));
            }

            return;
        }

        GLuint indexImplementacion;

        if(light->GetType() == Light::Ambiente)
        {
            glUniform3fv(glGetUniformLocation(idSP, "Ia"), 1, glm::value_ptr(light->GetColorDifuso()));
            indexImplementacion = glGetSubroutineIndex(idSP, GL_FRAGMENT_SHADER, "calculateAmbient");
        }
        else if(light->GetType() == Light::Puntual)
        {
            glm::vec3 posicionLuz = glm::vec3(Camera::GetInstancia()->GetViewMatrix() * glm::vec4(light->GetPosicion(), 0.0f));
            glUniform3fv(glGetUniformLocation(idSP, "lightPosition"), 1, glm::value_ptr(posicionLuz));
            glUniform3fv(glGetUniformLocation(idSP, "Id"), 1, glm::value_ptr(light->GetColorDifuso()));
            glUniform3fv(glGetUniformLocation(idSP, "Is"), 1, glm::value_ptr(light->GetColorEspecular()));
            indexImplementacion = glGetSubroutineIndex(idSP, GL_FRAGMENT_SHADER, "calculatePointLight");
        }
        else if(light->GetType() == Light::Direccional)
        {
            glm::vec3 direccionLuz = glm::vec3(Camera::GetInstancia()->GetViewMatrix() * glm::vec4(light->GetDireccion(), 0.0f));
            glUniform3fv(glGetUniformLocation(idSP, "lightDirection"), 1, glm::value_ptr(direccionLuz));
            glUniform3fv(glGetUniformLocation(idSP, "Id"), 1, glm::value_ptr(light->GetColorDifuso()));
            glUniform3fv(glGetUniformLocation(idSP, "Is"), 1, glm::value_ptr(light->GetColorEspecular()));
            indexImplementacion = glGetSubroutineIndex(idSP, GL_FRAGMENT_SHADER, "calculateDirectionalLight");
        }
        else if(light->GetType() == Light::Foco)
        {
            glm::vec3 posicionLuz = glm::vec3(Camera::GetInstancia()->GetViewMatrix() * glm::vec4(light->GetPosicion(), 0.0f));
            glm::vec3 direccionLuz = glm::vec3(Camera::GetInstancia()->GetViewMatrix() * glm::vec4(light->GetDireccion(), 0.0f));
            glUniform3fv(glGetUniformLocation(idSP, "Id"), 1, glm::value_ptr(light->GetColorDifuso()));
            glUniform3fv(glGetUniformLocation(idSP, "Is"), 1, glm::value_ptr(light->GetColorEspecular()));
            glUniform3fv(glGetUniformLocation(idSP, "spotPosition"), 1, glm::value_ptr(posicionLuz));
            glUniform3fv(glGetUniformLocation(idSP, "spotDirection"), 1, glm::value_ptr(direccionLuz));
            glUniform1f(glGetUniformLocation(idSP, "spotAngle"), light->GetSpotAngle());
            glUniform1f(glGetUniformLocation(idSP, "spotExponent"), light->GetSpotExponent());
            indexImplementacion = glGetSubroutineIndex(idSP, GL_FRAGMENT_SHADER, "calculateSpotLight");
        }
        else
        {
            throw std::runtime_error("El tipo de luz seleccionado no es válido.");
        }

        GLuint indexSubrutina = glGetSubroutineUniformLocation ( idSP, GL_FRAGMENT_SHADER, "metodoLuzElegido" );
        indices[indexSubrutina] = indexImplementacion;
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
                GetModelo(GUI::GetInstancia()->GetModeloActual())->SetIndexSP ( i );
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
            GetModelo(GUI::GetInstancia()->GetModeloActual())->SetIndexSP ( shaderPrograms.size() );
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

    void Renderer::CargaTextura(std::string rutaTextura)
    {
        if(models.size() > 0)
        {
            GetModelo(GUI::GetInstancia()->GetModeloActual())->CargarTextura(rutaTextura);
        }
        else
        {
            throw std::runtime_error("No hay ningún modelo cargado");
        }
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