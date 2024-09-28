#version 410
layout (location = 0) in vec3 posicion;
layout (location = 1) in vec3 colorVertice;

out vec3 colorFragmento;

void main()
{
    gl_Position = vec4(posicion, 1.0);
    colorFragmento = colorVertice;
}