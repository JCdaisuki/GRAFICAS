#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/vec3.hpp>

namespace PAG
{
    class Material
    {
        private:
            glm::vec3 colorAmbiente = glm::vec3(0.1, 0.1, 0.1);
            glm::vec3 colorDifuso = glm::vec3(0.8, 0.8, 0.8);
            glm::vec3 colorEspecular = glm::vec3(1.0, 1.0, 1.0);
            float brillo = 32;

        public:
            Material() = default;
            Material(glm::vec3 colorAmbiente, glm::vec3 colorDifuso, glm::vec3 colorEspecular, float brillo);

            glm::vec3 getColorAmbiente(){ return colorAmbiente; }
            glm::vec3 getColorDifuso(){ return colorDifuso; }
            glm::vec3 getColorEspecular(){ return colorEspecular; }
            float getBrillo(){ return brillo; }

            void SetColorAmbiente(glm::vec3 colorA){ colorAmbiente = colorA; }
            void SetColorDifuso(glm::vec3 colorD){ colorDifuso = colorD; }
            void SetColorEspecular(glm::vec3 colorE){ colorEspecular = colorE; }
            void SetBrillo(float b){ brillo = b; }
    };
}

#endif //MATERIAL_H