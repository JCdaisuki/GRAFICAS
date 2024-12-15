#version 410

layout (location = 0) in vec3 posicion;        // Posición del vértice
layout (location = 1) in vec3 normal;          // Normal del vértice

uniform mat4 projection;      // Matriz de proyección
uniform mat4 viewXmodelMatrix;// Matriz de visión * Matriz de modelado
uniform mat4 normalMatrix;    // Matriz para transformar las normales

out vec3 fragPosition;        // Posición del fragmento en el espacio de visión
out vec3 fragNormal;          // Normal del fragmento

layout (location = 2) in vec2 texCoord; // Coordenadas de textura

out vec2 fragTexCoord; // Coordenadas de textura para el fragment shader

void main()
{
    vec4 viewPosition = viewXmodelMatrix * vec4(posicion, 1.0);
    fragPosition = vec3(viewPosition);

    fragNormal = normalize(vec3(normalMatrix * vec4(normal, 0.0)));
    fragTexCoord = texCoord;

    gl_Position = projection * viewPosition;
}