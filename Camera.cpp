#include <glm/glm.hpp>

#include "Camera.h"

PAG::Camera* PAG::Camera::instancia = nullptr;

namespace PAG
{
    Camera* Camera::GetInstancia ()
    {
        if ( !instancia )
        {
            instancia = new Camera();
        }

        return instancia;
    }
}