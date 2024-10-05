/**
* @author Juan Carlos González Martínez
 */

#ifndef ShaderObject_h
#define ShaderObject_h

namespace PAG
{
    class ShaderObject
    {
        private:
            int id = 0;
            GLenum type = GL_VERTEX_SHADER;

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