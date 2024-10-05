#include "ShaderManager.h"

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
        //Buscamos si hay algún ShaderProgram en el vector que no esté siendo utilizado
        for(int i = 0; i < shaderPrograms.size(); i++)
        {
            if(shaderPrograms[i].GetIdSP() == 0)
            {
                shaderPrograms[i].AsignarShaders(rutaFuenteGLSL);
                return;
            }
        }

        //No hay ningún ShaderProgram disponible, creamos uno nuevo y lo añadimos al vector
        ShaderProgram newShaderProgram;
        newShaderProgram.AsignarShaders(rutaFuenteGLSL);
        shaderPrograms.push_back(newShaderProgram);
    }

    void ShaderManager::RefrescarVentana()
    {
        for(int i = 0; i < shaderPrograms.size(); i++)
        {
            if(shaderPrograms[i].GetIdSP() != 0)
            {
                shaderPrograms[i].Render();
            }
        }
    }

    ShaderManager::~ShaderManager()
    {
        shaderPrograms.clear();
    }

}