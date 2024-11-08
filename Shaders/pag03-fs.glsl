#version 410
in vec3 colorFragmento;
out vec4 colorFinal;

in salidaVS
{
    vec3 posicionV;
    vec3 normalV;
} entrada;

void main()
{
    colorFinal = vec4(colorFragmento, 1.0);

    vec3 n = normalize ( entrada.normalV );
}