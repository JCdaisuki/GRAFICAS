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

    };
}

#endif //MATERIAL_H