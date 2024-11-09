#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/vec3.hpp>

namespace PAG
{
    class Material
    {
        private:
            glm::vec3 colorAmbiente;
            glm::vec3 colorDifuso;
            glm::vec3 colorEspecular;
            float brillo;

        public:
            Material(glm::vec3 colorAmbiente, glm::vec3 colorDifuso, glm::vec3 colorEspecular, float brillo);

    };
}

#endif //MATERIAL_H