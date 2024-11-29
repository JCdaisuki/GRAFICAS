#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace PAG
{
    class Material
    {
        private:
            glm::vec4 colorAmbiente = glm::vec4(0.1, 0.1, 0.1, 1.0);
            glm::vec4 colorDifuso = glm::vec4(0.8, 0.8, 0.8, 1.0);
            glm::vec4 colorEspecular = glm::vec4(1.0, 1.0, 1.0, 1.0);
            float brillo = 32;

        public:
            Material() = default;
            Material(glm::vec4 colorAmbiente, glm::vec4 colorDifuso, glm::vec4 colorEspecular, float brillo);

            glm::vec4 getColorAmbiente(){ return colorAmbiente; }
            glm::vec4 getColorDifuso(){ return colorDifuso; }
            glm::vec4 getColorEspecular(){ return colorEspecular; }
            float getBrillo(){ return brillo; }

            void SetColorAmbiente(glm::vec4 colorA){ colorAmbiente = colorA; }
            void SetColorDifuso(glm::vec4 colorD){ colorDifuso = colorD; }
            void SetColorEspecular(glm::vec4 colorE){ colorEspecular = colorE; }
            void SetBrillo(float b){ brillo = b; }
    };
}

#endif //MATERIAL_H