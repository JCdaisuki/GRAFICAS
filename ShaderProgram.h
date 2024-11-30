/**
* @author Juan Carlos González Martínez
 */

#ifndef shaderProgram_h
#define shaderProgram_h

#include <glm/glm.hpp>

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

            GLint projLoc;
            GLint viewprojLoc;
            GLint normalLoc;

            glm::mat4 viewXprojectionMatrix;

        public:
            ShaderProgram() = default;

            int GetIdSP(){ return idSP; };
            std::string GetRuta(){ return ruta; };

            // - Esta función asigna los vertex y fragment shaders al programa a partir de su ruta
            void AsignarShaders(std::string rutaFuenteGLSL);

            // - Esat función configura e inicializa el shader program
            void CreaShaderProgram();

            void SetProjectionMatrix(const glm::mat4& projection);
            void SetViewAndModelMatrix(const glm::mat4& view, const glm::mat4& model);
            void SetNormalMatrix();

            ~ShaderProgram();
    };
}

#endif

