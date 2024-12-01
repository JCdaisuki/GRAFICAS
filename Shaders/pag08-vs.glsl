#version 410

layout (location = 0) in vec3 posicion;        // Posición del vértice
layout (location = 1) in vec3 normal;          // Normal del vértice

uniform mat4 projection;      // Matriz de proyección
uniform mat4 viewXmodelMatrix;// Matriz de visión * Matriz de modelado
uniform mat3 normalMatrix;    // Matriz para transformar las normales

out vec3 fragPosition;        // Posición del fragmento en el espacio de visión
out vec3 fragNormal;          // Normal del fragmento
out vec3 colorFragmento;      // Color del vértice

void main()
{
    vec4 viewPosition = viewXmodelMatrix * vec4(posicion, 1.0);
    fragPosition = vec3(viewPosition);

    fragNormal = normalize(normalMatrix * normal);

    gl_Position = projection * viewPosition;
}