/**
* @author Juan Carlos González Martínez
 */

#ifndef shaderProgram_h
#define shaderProgram_h

#include "ShaderObject.h"

namespace PAG
{
    class ShaderProgram
    {
        private:
            std::string ruta;
            GLuint idSP = 0; // Identificador del shader program

            ShaderObject *vertexShader;
            ShaderObject *fragmentShader;

            GLint viewLoc; // Ubicaciones de los uniformes
            GLint projLoc;

        public:
            ShaderProgram() = default;

            int GetIdSP(){ return idSP; };
            std::string GetRuta(){ return ruta; };

            // - Esta función asigna los vertex y fragment shaders al programa a partir de su ruta
            void AsignarShaders(std::string rutaFuenteGLSL);

            // - Esat función configura e inicializa el shader program
            void CreaShaderProgram();

            void SetViewMatrix(const glm::mat4& view);
            void SetProjectionMatrix(const glm::mat4& projection);

            ~ShaderProgram();
    };
}

#endif

