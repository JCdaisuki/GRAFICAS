/**
* @author Juan Carlos González Martínez
 */

#ifndef shaderProgram_h
#define shaderProgram_h

#include <glm/fwd.hpp>

#include "ShaderObject.h"

namespace PAG
{
    class ShaderProgram
    {
        private:
            GLuint idSP = 0; // Identificador del shader program
            GLuint idVAO = 0; // Identificador del vertex array object
            GLuint idVBO = 0; // Identificador del vertex buffer object
            GLuint idIBO = 0; // Identificador del index buffer object

            ShaderObject *vertexShader;
            ShaderObject *fragmentShader;

            GLint viewLoc; // Ubicaciones de los uniformes
            GLint projLoc;

            void SetViewMatrix(const glm::mat4& view);
            void SetProjectionMatrix(const glm::mat4& projection);
        public:
            ShaderProgram() = default;

            int GetIdSP(){ return idSP; };

            // - Esta función asigna los vertex y fragment shaders al programa a partir de su ruta
            void AsignarShaders(std::string rutaFuenteGLSL);

            // - Esat función configura e inicializa el shader program
            void CreaShaderProgram();

            // - Esta función crea el modelo de un triángulo a partir de los datos del shader program
            void CreaModelo();

            // - Esta función dibuja el modelo utilizando el shader program y los datos de los buffers configurados
            void Render();

            ~ShaderProgram();
    };
}

#endif

