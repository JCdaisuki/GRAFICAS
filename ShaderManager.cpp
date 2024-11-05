#include "ShaderManager.h"

#include <fstream>
#include <iostream>

PAG::ShaderManager* PAG::ShaderManager::instancia = nullptr;

namespace PAG
{
    ShaderManager* ShaderManager::GetInstancia ()
    {
        if ( !instancia ) // Lazy initialization: si aún no existe, lo crea
        {
            instancia = new ShaderManager();
        }

        return instancia;
    }

    void ShaderManager::CreaShaderProgram(std::string rutaFuenteGLSL)
    {
        if(rutaFuenteGLSL == "")
        {
            return;
        }

        //Buscamos si hay algún ShaderProgram en el vector que no esté siendo utilizado
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

    void ShaderManager::RefrescarVentana()
    {
        for(int i = 0; i < shaderPrograms.size(); i++)
        {
            if(shaderPrograms[i]->GetIdSP() != 0)
            {
                shaderPrograms[i]->Render();
            }
        }
    }

    ShaderProgram &ShaderManager::GetShaderProgram(int index)
    {
        return *shaderPrograms[index];
    }

    ShaderManager::~ShaderManager()
    {
        if (instancia)
        {
            delete instancia;
            instancia = nullptr;
        }

        for(int i = 0; i < shaderPrograms.size(); i++)
        {
            delete shaderPrograms[i];
        }

        shaderPrograms.clear();
    }
}