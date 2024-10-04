/**
* @author Juan Carlos González Martínez
 */

namespace PAG
{
    class ShaderObject
    {
        private:
            int id;
            GLenum type;

        public:
            void LoadShader(std::string rutaFuenteGLSL);
            ~ShaderObject();
    };
}
