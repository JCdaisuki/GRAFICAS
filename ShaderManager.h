/**
* @author Juan Carlos González Martínez
 */

#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <vector>
#include <string>

#include "ShaderProgram.h"

namespace PAG
{
    class ShaderManager
    {
        private:
            static ShaderManager* instancia;

            std::vector<ShaderProgram*> shaderPrograms;

        public:
            static ShaderManager* GetInstancia ();

            // - Esta función asigna los shaders de una ruta a un ShaderProgram disponible (o nuevo)
            void CreaShaderProgram(std::string rutaFuenteGLSL);

            // - Esta función renderizará los ShaderPrograms disponibles
            void RefrescarVentana();

            ShaderProgram &GetShaderProgram(int index);

            ~ShaderManager();
    };
}



#endif //SHADERMANAGER_H
