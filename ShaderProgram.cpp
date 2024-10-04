#include <iostream>
#include <fstream>
#include <sstream>

#include <glad/glad.h>

#include "ShaderObject.h"
#include "ShaderProgram.h"

namespace PAG
{
    void ShaderProgram::CreaShaderProgram()
    {
        idSP = glCreateProgram ();

        if ( idSP == 0 )
        {
            throw std::runtime_error ("Error al crear el Shader Program");
        }

        glAttachShader ( idSP, idVS );
        glAttachShader ( idSP, idFS );
        glLinkProgram ( idSP );

        GLint resultadoCompilacion;
        glGetShaderiv ( idVS, GL_COMPILE_STATUS, &resultadoCompilacion );

        if ( resultadoCompilacion == GL_FALSE ) // Ha habido un error en la compilación.
        {
            GLint tamMsj = 0;
            std::string mensaje = "";
            glGetShaderiv ( idVS, GL_INFO_LOG_LENGTH, &tamMsj );

            if ( tamMsj > 0 )
            {
                GLchar* mensajeFormatoC = new GLchar[tamMsj];
                GLint datosEscritos = 0;
                glGetShaderInfoLog (idVS , tamMsj, &datosEscritos, mensajeFormatoC );
                mensaje.assign ( mensajeFormatoC );
                delete[] mensajeFormatoC;
                mensajeFormatoC = nullptr;

                throw std::runtime_error ( mensaje );
            }
        }
    }

    void ShaderProgram::CreaModelo()
    {
        //Vértices del triángulo con los colores intercalados (x, y, z, r, g, b)
        GLfloat verticesYColores[] =
        {
            //Posiciones        //Colores
            -.5f, -.5f, .0f,    1.0f, 0.0f, 0.0f,
             .5f, -.5f, .0f,    0.0f, 1.0f, 0.0f,
             .0f,  .5f, .0f,    0.0f, 0.0f, 1.0f
        };

        GLuint indices[] = { 0, 1, 2 };

        glGenVertexArrays(1, &idVAO);
        glBindVertexArray(idVAO);

        //VBO para las posiciones y los colores
        glGenBuffers(1, &idVBO);
        glBindBuffer(GL_ARRAY_BUFFER, idVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verticesYColores), verticesYColores, GL_STATIC_DRAW);

        //Atributo de posición (0) (Indicamos 3 componentes (x, y, z) y un salto de 6 (Los conjuntos de valores estan separados por 6 componentes))
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);

        //Atributo de color (1) (Indicamos que el desplazamiento del atributo color esta a 3 floats de su posición para empezar en el 4º atributo)
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        //IBO para los índices, común para ambas versiones de VBO
        glGenBuffers(1, &idIBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glBindVertexArray(0);
    }

    ShaderProgram::~ShaderProgram()
    {
        if ( idSP != 0 )
        {
            glDeleteProgram ( idSP );
        }

        if ( idVBO != 0 )
        {
            glDeleteBuffers ( 1, &idVBO );
        }

        if ( idIBO != 0 )
        {
            glDeleteBuffers ( 1, &idIBO );
        }

        if ( idVAO != 0 )
        {
            glDeleteVertexArrays ( 1, &idVAO );
        }
    }

}