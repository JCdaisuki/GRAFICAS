#version 410
layout (location = 0) in vec3 posicion;
layout (location = 1) in vec3 colorVertice;

uniform mat4 view;
uniform mat4 projection;

out vec3 colorFragmento;

void main()
{
    gl_Position = projection * view * vec4(posicion, 1.0);
    colorFragmento = colorVertice;
}

