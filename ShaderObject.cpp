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
        //Tratamos de abrir el archivo que contiene el Shader
        std::ifstream archivoShader;
        archivoShader.open(rutaFuenteGLSL);

        if ( !archivoShader.is_open() )
        {
            throw std::runtime_error ("Error al abrir el archivo " + rutaFuenteGLSL);
        }

        //Creamos el objeto Shader
        id = glCreateShader(type); //CREADO DESPUES DE TRATAR DE ABRIR EL ARCHIVO(?)

        if(id == 0)
        {
            throw std::runtime_error ("Error al crear Shader");
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

        GLint resultadoCompilacion;
        glGetShaderiv ( id, GL_COMPILE_STATUS, &resultadoCompilacion );

        if ( resultadoCompilacion == GL_FALSE )
        {
            GLint tamMsj = 0;
            std::string mensaje = "";
            glGetShaderiv ( id, GL_INFO_LOG_LENGTH, &tamMsj );
            if ( tamMsj > 0 )
            {
                GLchar* mensajeFormatoC = new GLchar[tamMsj];
                GLint datosEscritos = 0;
                glGetShaderInfoLog ( id, tamMsj, &datosEscritos, mensajeFormatoC );
                mensaje.assign ( mensajeFormatoC );
                delete[] mensajeFormatoC;
                mensajeFormatoC = nullptr;

                throw std::runtime_error("Error al compilar el Shader " + rutaFuenteGLSL + ": " + mensaje);
            }
        }
    }

    ShaderObject::~ShaderObject()
    {
        if ( id != 0 )
        {
            glDeleteShader ( id );
        }
    }

}