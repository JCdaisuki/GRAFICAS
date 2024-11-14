#ifndef ShaderObject_h
#define ShaderObject_h

#include <glad/glad.h>
#include <string>

namespace PAG
{
    class ShaderObject
    {
        private:
            int id = 0;
            GLenum type = GL_VERTEX_SHADER; //ERROR AQUI, DICE QUE REQUIERE GLAD PERO SI LO INCLUYO DICE QUE YA ESTA INCLUIDO

        public:
            ShaderObject() = default;
            ShaderObject(GLenum t);

            int GetId();
            GLenum GetType();

            // - Esta función carga un shader a partir de la ruta especificada
            void LoadShader(std::string rutaFuenteGLSL);

            ~ShaderObject();
    };
}

#endif