#include <iostream>
#include <fstream>
#include <sstream>

#include <glad/glad.h>

#include "Renderer.h"


/**
 * @author Juan Carlos González Martínez
 */

PAG::Renderer* PAG::Renderer::instancia = nullptr;

namespace PAG
{
    PAG::Renderer* PAG::Renderer::GetInstancia ()
    {
        if ( !instancia ) // Lazy initialization: si aún no existe, lo crea
        {
            instancia = new Renderer();
        }

        return instancia;
    }

    void Renderer::InicializarOpenGL()
    {
        glClearColor ( 0.6, 0.6, 0.6, 1.0 ); // - Establecemos un gris medio como color con el que se borrará el frame buffer.
        glEnable(GL_DEPTH_TEST);
        glEnable ( GL_MULTISAMPLE );
    }

    std::string Renderer::MostrarPropiedades()
    {
        std::string propiedades =
            "Propiedades del Contexto 3D:\n" +
            std::string(" - Tarjeta Gráfica: ") + reinterpret_cast<const char*>(glGetString(GL_RENDERER)) + "\n" +
            std::string(" - Fabricante de Tarjeta Gráfica: ") + reinterpret_cast<const char*>(glGetString(GL_VENDOR)) + "\n" +
            std::string(" - Versión de OpenGL: ") + reinterpret_cast<const char*>(glGetString(GL_VERSION)) + "\n" +
            std::string(" - Versión de GLSL: ") + reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION)) + "\n\n";

        return propiedades;
    }

    void Renderer::RefrescarVentana ()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );
        glUseProgram ( idSP );
        glBindVertexArray ( idVAO );
        glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, idIBO );
        glDrawElements ( GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr );
    }

    void Renderer::ModificarTamaño (int width, int height )
    {
        glViewport ( 0, 0, width, height );
    }

    void Renderer::CambiarColorFondo (float* color)
    {
        //Cambia el color de fondo al recibido como parámetro
        glClearColor(color[0],color[1],color[2],color[3]);

        // Limpia el buffer de color para aplicar el nuevo color de fondo
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer::LoadShader(std::string rutaFuenteGLSL , GLenum type)
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

    void Renderer::CreaShaderProgram()
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

    void Renderer::CreaModelo()
    {
        GLfloat vertices[] = { -.5, -.5, 0,
                                .5, -.5, 0,
                                .0, .5, 0 };
        GLuint indices[] = { 0, 1, 2 };

        glGenVertexArrays ( 1, &idVAO );
        glBindVertexArray ( idVAO );glGenBuffers ( 1, &idVBO );
        glBindBuffer ( GL_ARRAY_BUFFER, idVBO );
        glBufferData ( GL_ARRAY_BUFFER, 9*sizeof(GLfloat), vertices,
        GL_STATIC_DRAW );
        glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat),nullptr );
        glEnableVertexAttribArray ( 0 );
        glGenBuffers ( 1, &idIBO );
        glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, idIBO );
        glBufferData ( GL_ELEMENT_ARRAY_BUFFER, 3*sizeof(GLuint), indices, GL_STATIC_DRAW );
    }

    Renderer::~Renderer()
    {
        if (instancia)
        {
            delete instancia;
            instancia = nullptr;
        }

        if ( idVS != 0 )
        {
            glDeleteShader ( idVS );
        }

        if ( idFS != 0 )
        {
            glDeleteShader ( idFS );
        }

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