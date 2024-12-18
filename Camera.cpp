#include "Camera.h"

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

        RecalcularValores();
    }

    void Camera::Tilt(float angulo)
    {
        //Mismo funcionamiento que Pan() excepto que la rotación es sobre el eje u
        glm::mat4 moverAlOrigen = glm::translate(glm::mat4(1.0f), -posicion);
        glm::mat4 rotacion = glm::rotate(glm::mat4(1.0f), glm::radians(angulo), u);
        glm::mat4 moverAOriginal = glm::translate(glm::mat4(1.0f), posicion);

        glm::mat4 transformacion = moverAOriginal * rotacion * moverAlOrigen;

        target = glm::vec3(transformacion * glm::vec4(target, 1.0f));

        RecalcularValores();
    }

    //Nota: Aunque pan y tilt puedan parecer iguales a dolly, si hacemos zoom podmeos ver que pan y tilt estan rotando!

    void Camera::Dolly(const std::string& direccion, float distancia)
    {
        glm::vec3 movimiento(0.0f);

        //Calcular el movimiento en función de la dirección introducida
        if (direccion == "front")
        {
            movimiento = n * distancia;
        }
        else if (direccion == "left")
        {
            movimiento = -u * distancia;
        }
        else if (direccion == "right")
        {
            movimiento = u * distancia;
        }
        else if (direccion == "back")
        {
            movimiento = -n * distancia;
        }

        //Actualizar la posición de la cámara y el punto al que se mira
        posicion += movimiento;
        target += movimiento;

        RecalcularValores();
    }

    void Camera::Crane(float distancia)
    {
        //Mover la cámara y el punto al que se mira en el eje Y
        posicion.y += distancia;
        target.y += distancia;

        RecalcularValores();
    }

    void Camera::Orbit(float latitud, float longitud)
    {
        //Calcular las matrices de rotación paralos ejes u y v
        glm::mat4 moverAlOrigen = glm::translate(glm::mat4(1.0f), -posicion);
        glm::mat4 rotacionLatitud = glm::rotate(glm::mat4(1.0f), glm::radians(latitud), u);
        glm::mat4 rotacionLongitud = glm::rotate(glm::mat4(1.0f), glm::radians(longitud), v);
        glm::mat4 moverAOriginal = glm::translate(glm::mat4(1.0f), posicion);

        glm::mat4 transformacion = moverAOriginal * rotacionLongitud * rotacionLatitud * moverAlOrigen;

        //Aplicar la transformación a la posición de la cámara
        glm::vec3 direccion = glm::vec3(transformacion * glm::vec4(posicion - target, 0.0f));
        posicion = target + direccion; //Actualizar la posición de la cámara

        RecalcularValores();
    }

    void Camera::RecalcularValores()
    {
        //Recalcular los valores del sistema de coordenadas
        n = glm::normalize(target - posicion);
        u = glm::normalize(glm::cross(up, n));
        v = glm::normalize(glm::cross(n, u));

        //Actualizar matriz de vista
        viewMatrix = glm::lookAt(posicion, target, up);
    }

    Camera::~Camera()
    {
        if (instancia)
        {
            delete instancia;
            instancia = nullptr;
        }
    }
}