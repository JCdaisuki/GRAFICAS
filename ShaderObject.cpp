#include <iostream>
#include <fstream>
#include <sstream>

#include <glad/glad.h>

#include "ShaderObject.h"

namespace PAG
{
    ShaderObject::ShaderObject(GLenum t)
    {
        id = 0;
        type = t;
    }

    int ShaderObject::GetId()
    {
        return id;
    }

    GLenum ShaderObject::GetType()
    {
        return type;
    }

    void ShaderObject::LoadShader(std::string rutaFuenteGLSL)
    {
        //Creamos el objeto Shader
        id = glCreateShader(type);

        if(id == 0)
        {
            throw std::runtime_error ("Error al crear Shader");
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