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

    void Camera::Pan(float angulo) //NO FUNCIONA!!!!
    {
        //ROTAR LA CAMARA LOS ANGULOS EN V
        glm::mat4 rotacion = glm::rotate(glm::mat4(1.0f), glm::radians(angulo), v);

        //Rotar el vector n y actualizar el punto al que mira la cámara
        n = glm::normalize(glm::vec3(rotacion * glm::vec4(n, 0.0f)));
        target += n;

        //A LO MEJOR EL ERROR ES QUE SE TOQUETEAN LOS OTROS??
        u = glm::normalize(glm::cross(up, n));
        v = glm::normalize(glm::cross(n, u));

        //Actualizar la matriz de vista
        viewMatrix = glm::lookAt(posicion, target, up);
    }

    void Camera::Tilt(float angulo)
    {
        //MISMO CODIGO QUE PAN PERO ROTANDO EL EJE U
        glm::mat4 rotacion = glm::rotate(glm::mat4(1.0f), glm::radians(angulo), u);

        n = glm::normalize(glm::vec3(rotacion * glm::vec4(n, 0.0f)));
        target += n;

        u = glm::normalize(glm::cross(up, n));
        v = glm::normalize(glm::cross(n, u));

        viewMatrix = glm::lookAt(posicion, target, up);
    }
}