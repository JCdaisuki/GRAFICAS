#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include <vector>

#include "Model.h"

namespace PAG
{
    class ModelManager
    {
        private:
            static ModelManager* instancia;

            std::vector<Model*> models;

        public:
            static ModelManager* GetInstancia ();

            void CreaModelo(std::string rutaModelo);
            void RefrescarVentana();

            ~ModelManager();
    };
}

#endif //MODELMANAGER_H