#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>

namespace PAG
{
    class Camera
    {
        private:
            static Camera* instancia;

            glm::vec3 posicion;
            glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f); //Asignamos el origen como punto al que mira

            float angVision = 45; //Ángulo de vision en horizontal
            int alto = 0; //Alto y ancho del viewport
            int ancho = 0;
            float zNear = 0.1;
            float zFar = 100;

            glm::mat4 matrizProyeccion;
        public:
            static Camera* GetInstancia();

            Camera() = default;

            void setAlto(int a){alto = a;}
            void setAncho(int a){ancho = a;}

            void Zoom(float angulo);
    };
}



#endif //CAMERA_H
