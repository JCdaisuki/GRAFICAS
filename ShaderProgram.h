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
            GLuint idSP = 0; // Identificador del shader program
            GLuint idVAO = 0; // Identificador del vertex array object
            GLuint idVBO = 0; // Identificador del vertex buffer object
            GLuint idIBO = 0; // Identificador del index buffer object

            ShaderObject *vertexShader;
            ShaderObject *fragmentShader;

        public:
            ShaderProgram() = default;
            void AsignarShaders(std::string rutaFuenteGLSL);
            void CreaShaderProgram();
            void RefrescarVentana();
            void CreaModelo();
            ~ShaderProgram();
    };
}

#endif

