#include "Camera.h"

#include <iostream>
#include <ostream>


PAG::Camera* PAG::Camera::instancia = nullptr;

namespace PAG
{
    Camera::Camera()
    {
        n = glm::normalize(posicion - target); // Forward
        u = glm::normalize(glm::cross(up, n)); // Right
        v = glm::cross(n, u); // True Up

        viewMatrix = glm::lookAt(posicion, target, up);
        projectionMatrix = glm::perspective(glm::radians(angVision), (float)(ancho/alto), zNear, zFar);
    }

    Camera* Camera::GetInstancia()
    {
        if ( !instancia )
        {
            instancia = new Camera();
        }

        return instancia;
    }

    glm::mat4 Camera::GetViewMatrix()
    {
        return viewMatrix;
    }

    glm::mat4 Camera::GetProjectionMatrix()
    {
        return projectionMatrix;
    }

    void Camera::Zoom(float angulo)
    {
        projectionMatrix = glm::perspective(glm::radians(angVision + angulo), (float)(ancho / alto), zNear, zFar);
    }
}