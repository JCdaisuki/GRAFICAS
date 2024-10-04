/**
* @author Juan Carlos González Martínez
 */

namespace PAG
{
    class ShaderProgram
    {
        private:
            static ShaderProgram* instancia;

            GLuint idSP = 0; // Identificador del shader program
            GLuint idVAO = 0; // Identificador del vertex array object
            GLuint idVBO = 0; // Identificador del vertex buffer object
            GLuint idIBO = 0; // Identificador del index buffer object

            ShaderObject vertexShader;
            ShaderObject fragmentShader;

        public:
            void CreaShaderProgram();
            void CreaModelo();
            ~ShaderProgram();
    };
}

