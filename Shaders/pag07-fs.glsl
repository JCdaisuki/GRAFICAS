#version 410

in vec3 colorFragmento;
out vec4 colorFinal;

void main()
{
    colorFinal = vec4(colorFragmento, 1.0);
}