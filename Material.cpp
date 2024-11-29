#include "Material.h"

namespace PAG
{
    Material::Material(glm::vec4 colorAmbiente, glm::vec4 colorDifuso, glm::vec4 colorEspecular, float brillo)
    {
        this->colorAmbiente = colorAmbiente;
        this->colorDifuso = colorDifuso;
        this->colorEspecular = colorEspecular;
        this->brillo = brillo;
    }

}