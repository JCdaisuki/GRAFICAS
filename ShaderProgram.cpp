#include "ShaderProgram.h"
#include <stdexcept>
#include <iostream>
#include <glm/glm.hpp>

#include "Camera.h"

namespace PAG {
    void ShaderProgram::AsignarShaders(std::string rutaFuenteGLSL)
    {
        vertexShader = new ShaderObject(GL_VERTEX_SHADER);
        fragmentShader = new ShaderObject(GL_FRAGMENT_SHADER);

        vertexShader->LoadShader(rutaFuenteGLSL + "-vs.glsl");
        fragmentShader->LoadShader(rutaFuenteGLSL + "-fs.glsl");

        CreaShaderProgram();
        CreaModelo();
    }

    void ShaderProgram::CreaShaderProgram()
    {
        idSP = glCreateProgram();

        if (idSP == 0)
        {
            throw std::runtime_error("Error al crear el Shader Program");
        }

        glAttachShader(idSP, vertexShader->GetId());
        glAttachShader(idSP, fragmentShader->GetId());
        glLinkProgram(idSP);

        // Verificar el enlace del programa
        GLint linkStatus;
        glGetProgramiv(idSP, GL_LINK_STATUS, &linkStatus);
        if (linkStatus == GL_FALSE)
        {
            GLint logLength = 0;
            glGetProgramiv(idSP, GL_INFO_LOG_LENGTH, &logLength);
            if (logLength > 0)
            {
                GLchar* logMessage = new GLchar[logLength];
                glGetProgramInfoLog(idSP, logLength, nullptr, logMessage);
                std::string mensaje = logMessage;
                delete[] logMessage;
                throw std::runtime_error("Error enlazando el Shader Program: " + mensaje);
            }
            else
            {
                throw std::runtime_error("Error enlazando el Shader Program sin mensaje de error.");
            }
        }

        viewLoc = glGetUniformLocation(idSP, "view");

        if (viewLoc == -1)
        {
            throw std::runtime_error("Uniform 'view' no encontrado en el shader " + idSP);
        }

        projLoc = glGetUniformLocation(idSP, "projection");

        if (projLoc == -1)
        {
            throw std::runtime_error("Uniform 'projection' no encontrado en el shader " + idSP);
        }
    }

    void ShaderProgram::CreaModelo()
    {
        // Vértices del triángulo con los colores intercalados (x, y, z, r, g, b)
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

        // VBO para las posiciones y los colores
        glGenBuffers(1, &idVBO);
        glBindBuffer(GL_ARRAY_BUFFER, idVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verticesYColores), verticesYColores, GL_STATIC_DRAW);

        // Atributo de posición (0)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);

        // Atributo de color (1)
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        // IBO para los índices
        glGenBuffers(1, &idIBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glBindVertexArray(0);
    }

    void ShaderProgram::Render()
    {
        if(idVAO == 0 || idVBO == 0 || idIBO == 0)
        {
            return;
        }

        glUseProgram(idSP);

        SetViewMatrix(Camera::GetInstancia()->GetViewMatrix());
        SetProjectionMatrix(Camera::GetInstancia()->GetProjectionMatrix());

        glBindVertexArray(idVAO);

        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

        glBindVertexArray(0);
    }

    void ShaderProgram::SetViewMatrix(const glm::mat4& view)
    {
        if (viewLoc != -1)
        {
            glUseProgram(idSP);
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        }
    }

    void ShaderProgram::SetProjectionMatrix(const glm::mat4& projection)
    {
        if (projLoc != -1)
        {
            glUseProgram(idSP);
            glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projection[0][0]);
        }
    }

    ShaderProgram::~ShaderProgram()
    {
        if (idSP != 0)
        {
            glDeleteProgram(idSP);
        }

        if (idVBO != 0)
        {
            glDeleteBuffers(1, &idVBO);
        }

        if (idIBO != 0)
        {
            glDeleteBuffers(1, &idIBO);
        }

        if (idVAO != 0)
        {
            glDeleteVertexArrays(1, &idVAO);
        }

        if (vertexShader)
        {
            delete vertexShader;
        }

        if (fragmentShader)
        {
            delete fragmentShader;
        }
    }
}
