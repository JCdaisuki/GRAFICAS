#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace PAG
{
    class Camera
    {
        private:
            static Camera* instancia;

            glm::vec3 posicion = glm::vec3(0, 0, 5);
            glm::vec3 target = glm::vec3(0, 0, 0); //Asignamos el origen como punto al que mira
            glm::vec3 up = glm::vec3(0, 1, 0);

            //Sistema de coordenadas local
            glm::vec3 u;
            glm::vec3 v;
            glm::vec3 n;

            float angVision = 45; //Ángulo de vision en horizontal
            int alto = 576; //Alto y ancho del viewport
            int ancho = 1024;
            float zNear = 0.1;
            float zFar = 100;

            glm::mat4 viewMatrix;
            glm::mat4 projectionMatrix;

            // - Función auxiliar que permite recalcular el sistema de coordenadas y la viewMatrix tras cada movimiento de cámara
            void RecalcularValores();
        public:
            static Camera* GetInstancia();

            Camera();

            void SetAltoAncho(int alt, int anch){alto = alt; ancho = anch;}

            glm::mat4 GetViewMatrix();
            glm::mat4 GetProjectionMatrix();

            void Zoom(float angulo);
            void Pan(float angulo);
            void Tilt(float angulo);
            void Dolly(const std::string& direccion, float distancia);
            void Crane(float distancia);
    };
}



#endif //CAMERA_H
