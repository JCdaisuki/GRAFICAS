#include "Material.h"

namespace PAG
{
    Material::Material(glm::vec3 colorAmbiente, glm::vec3 colorDifuso, glm::vec3 colorEspecular, float brillo)
    {
        this->colorAmbiente = colorAmbiente;
        this->colorDifuso = colorDifuso;
        this->colorEspecular = colorEspecular;
        this->brillo = brillo;
    }

}