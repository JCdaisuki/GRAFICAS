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

            // - Esta función asigna los vertex y fragment shaders al programa a partir de su ruta
            void AsignarShaders(std::string rutaFuenteGLSL);

            // - Esat función configura e inicializa el shader program
            void CreaShaderProgram();

            // - Esta función prepara el contexto OpenGL para el dibujo a realizar
            void RefrescarVentana();

            // - Esta función crea el modelo de un triángulo a partir de los datos del shader program
            void CreaModelo();

            ~ShaderProgram();
    };
}

#endif

