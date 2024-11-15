#version 410

out vec4 colorFragmento;

uniform vec4 colorDifuso;

subroutine vec4 calcularColor();
subroutine uniform calcularColor metodoColorElegido;

subroutine(calcularColor)
vec4 colorNegro ()
{
    return vec4 ( 0, 0, 0, 1 );
}

subroutine(calcularColor)
vec4 colorDifusoMaterial ()
{
    return colorDifuso;
}

void main ()
{
    colorFragmento = metodoColorElegido ();
}