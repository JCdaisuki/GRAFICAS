#include "Camera.h"

#include <iostream>
#include <ostream>


PAG::Camera* PAG::Camera::instancia = nullptr;

namespace PAG
{
    Camera::Camera()
    {
        n = glm::normalize(posicion - target);
        u = glm::normalize(glm::cross(up, n));
        v = glm::cross(n, u);

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
        projectionMatrix = glm::perspective(glm::radians(angVision + angulo), ((float)ancho / (float)alto), zNear, zFar);
    }

    void Camera::Pan(float angulo)
    {
        glm::mat4 moverAlOrigen = glm::translate(glm::mat4(1.0f), -posicion);
        glm::mat4 rotacion = glm::rotate(glm::mat4(1.0f), glm::radians(angulo), v);
        glm::mat4 moverAOriginal = glm::translate(glm::mat4(1.0f), posicion);

        //Combinar las transformaciones: mover al origen, rotar y luego mover de vuelta a la posición inicial
        glm::mat4 transformacion = moverAOriginal * rotacion * moverAlOrigen;

        //Aplicar la transformación al punto lookAt para actualizar el target
        target = glm::vec3(transformacion * glm::vec4(target, 1.0f));

        //Recalcular los valores del sistema de coordenadas
        n = glm::normalize(target - posicion);
        u = glm::normalize(glm::cross(up, n));
        v = glm::normalize(glm::cross(n, u));

        viewMatrix = glm::lookAt(posicion, target, up);
    }

    void Camera::Tilt(float angulo)
    {
        //Mismo funcionamiento que Pan() excepto que la rotación es sobre el eje u
        glm::mat4 moverAlOrigen = glm::translate(glm::mat4(1.0f), -posicion);
        glm::mat4 rotacion = glm::rotate(glm::mat4(1.0f), glm::radians(angulo), u);
        glm::mat4 moverAOriginal = glm::translate(glm::mat4(1.0f), posicion);

        glm::mat4 transformacion = moverAOriginal * rotacion * moverAlOrigen;

        target = glm::vec3(transformacion * glm::vec4(target, 1.0f));

        n = glm::normalize(target - posicion);
        u = glm::normalize(glm::cross(up, n));
        v = glm::normalize(glm::cross(n, u));

        viewMatrix = glm::lookAt(posicion, target, up);
    }
}