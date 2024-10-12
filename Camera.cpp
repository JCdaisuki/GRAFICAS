#include "Camera.h"


PAG::Camera* PAG::Camera::instancia = nullptr;

namespace PAG
{
    Camera* Camera::GetInstancia()
    {
        if ( !instancia )
        {
            instancia = new Camera();
        }

        return instancia;
    }

    void Camera::Zoom(float angulo)
    {
        matrizProyeccion = glm::perspective(glm::radians(angVision + angulo), (float)(ancho / alto), zNear, zFar);
    }

}