#include <iostream>
#include <fstream>
#include <sstream>

#include <glad/glad.h>

#include "ShaderObject.h"

namespace PAG
{
    void ShaderObject::LoadShader(std::string rutaFuenteGLSL , GLenum type)
    {
        //Creamos el objeto Shader
        int id = glCreateShader(type);

        if(id == 0)
        {
            throw std::runtime_error ("Error al crear Shader");
        }

        //Asignamos el id del shader a su atributo correspondiente
        if(type == GL_VERTEX_SHADER)
        {
            idVS = id;
        }
        else if (type == GL_FRAGMENT_SHADER)
        {
            idFS = id;
        }

        //Tratamos de abrir el archivo que contiene el Shader
        std::ifstream archivoShader;
        archivoShader.open(rutaFuenteGLSL);

        if ( !archivoShader.is_open () )
        {
            throw std::runtime_error ("Error al abrir el archivo " + rutaFuenteGLSL);
        }

        //Obtenemos el código fuente del Shader a partir del archivo
        std::stringstream streamShader;
        streamShader << archivoShader.rdbuf ();
        std::string codigoFuenteShader = streamShader.str ();

        //Cerramos el archivo
        archivoShader.close ();

        const GLchar* fuenteVS = codigoFuenteShader.c_str ();
        glShaderSource ( id, 1, &fuenteVS, nullptr );
        glCompileShader ( id );
    }

    ShaderObject::~ShaderObject()
    {
        if ( id != 0 )
        {
            glDeleteShader ( id );
        }
    }

}