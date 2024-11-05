#include "ModelManager.h"

#include <fstream>

PAG::ModelManager* PAG::ModelManager::instancia = nullptr;

namespace PAG
{
    ModelManager *ModelManager::GetInstancia()
    {
        if ( !instancia )
        {
            instancia = new ModelManager();
        }

        return instancia;
    }

    void ModelManager::CreaModelo(std::string rutaModelo)
    {
        if(rutaModelo == "")
        {
            return;
        }

        std::ifstream archivo(rutaModelo);
        if (!archivo.good())
        {
            throw std::runtime_error("Error: No se encontró el archivo del modelo en " + rutaModelo);
        }

        Model* newModel = new Model(rutaModelo.data());
        models.push_back(newModel);
    }

    void ModelManager::RefrescarVentana()
    {
        for(int i = 0; i < models.size(); i++)
        {
            models[i]->Draw();
        }
    }

    ModelManager::~ModelManager()
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
    }

}