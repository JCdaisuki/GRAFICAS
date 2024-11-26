#version 410

layout (location = 0) in vec3 posicion;        // Posición del vértice
layout (location = 1) in vec3 normal;          // Normal del vértice
layout (location = 2) in vec3 colorVertice;    // Color del vértice

uniform mat4 view;            // Matriz de vista
uniform mat4 projection;      // Matriz de proyección
uniform mat4 model;           // Matriz del modelo (opcional, si necesitas transformaciones locales)
uniform mat3 normalMatrix;    // Matriz para transformar las normales

out vec3 fragPosition;        // Posición del fragmento en el espacio de vista
out vec3 fragNormal;          // Normal del fragmento
out vec3 colorFragmento;      // Color interpolado del vértice

void main() {
    // Transformar la posición del vértice al espacio de vista
    vec4 viewPosition = view * model * vec4(posicion, 1.0);
    fragPosition = vec3(viewPosition);

    // Transformar la normal al espacio de vista
    fragNormal = normalize(normalMatrix * normal);

    // Transformar la posición del vértice al espacio de recorte
    gl_Position = projection * viewPosition;

    // Pasar el color del vértice al fragment shader
    colorFragmento = colorVertice;
}