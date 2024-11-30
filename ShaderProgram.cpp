#include "ShaderProgram.h"
#include <stdexcept>
#include <iostream>
#include <glm/glm.hpp>

#include "Camera.h"
#include "imgui/imgui_impl_opengl3_loader.h"

namespace PAG
{
    void ShaderProgram::AsignarShaders(std::string rutaFuenteGLSL)
    {
        vertexShader = new ShaderObject(GL_VERTEX_SHADER);
        fragmentShader = new ShaderObject(GL_FRAGMENT_SHADER);

        vertexShader->LoadShader(rutaFuenteGLSL + "-vs.glsl");
        fragmentShader->LoadShader(rutaFuenteGLSL + "-fs.glsl");

        CreaShaderProgram();
        ruta = rutaFuenteGLSL;
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
    }

    void ShaderProgram::SetProjectionMatrix(const glm::mat4& projection)
    {
        projLoc = glGetUniformLocation(idSP, "projection");

        if (projLoc == -1)
        {
            throw std::runtime_error("Uniform 'projection' no encontrado en el shader " + idSP);
        }

        glUniformMatrix4fv(viewprojLoc, 1, GL_FALSE, &projection[0][0]);
    }

    void ShaderProgram::SetViewAndModelMatrix(const glm::mat4& view, const glm::mat4& model)
    {
        normalLoc = glGetUniformLocation(idSP, "viewXmodelMatrix");

        if (viewprojLoc == -1)
        {
            throw std::runtime_error("Uniform 'viewXmodelMatrix' no encontrado en el shader " + idSP);
        }

        viewXprojectionMatrix = view * model;
        glUniformMatrix4fv(viewprojLoc, 1, GL_FALSE, &viewXprojectionMatrix[0][0]);
    }

    void ShaderProgram::SetNormalMatrix()
    {
        normalLoc = glGetUniformLocation(idSP, "normalMatrix");

        if (normalLoc == -1)
        {
            throw std::runtime_error("Uniform 'normalMatrix' no encontrado en el shader " + idSP);
        }

        glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(viewXprojectionMatrix)));
        glUniformMatrix4fv(viewprojLoc, 1, GL_FALSE, &normalMatrix[0][0]);
    }

    ShaderProgram::~ShaderProgram()
    {
        if (idSP != 0)
        {
            glDeleteProgram(idSP);
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
