#ifndef LIGHT_H
#define LIGHT_H
#include <glm/vec3.hpp>

namespace PAG
{
    class Light
    {
        public:
            enum LightType
            {
                Ambiente,
                Puntual,
                Direccional,
                Foco
            };

        private:
            LightType type;

            glm::vec3 colorDifuso;
            glm::vec3 colorEspecular;
            glm::vec3 posicion;
            glm::vec3 direccion;

        public:
            Light(LightType type, const glm::vec3 &color_difuso, const glm::vec3 &color_especular,const glm::vec3 &posicion, const glm::vec3 &direccion) : type(type),colorDifuso(color_difuso),colorEspecular(color_especular),posicion(posicion),direccion(direccion) {}

            LightType GetType(){return type;}
            glm::vec3 GetColorDifuso(){return colorDifuso;}
            glm::vec3 GetColorEspecular(){return colorEspecular;}
            glm::vec3 GetPosicion(){return posicion;}
            glm::vec3 GetDireccion(){return direccion;}
    };
}

#endif //LIGHT_H