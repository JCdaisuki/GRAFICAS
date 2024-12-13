#version 410

in vec3 fragPosition;
in vec3 fragNormal;
in vec2 fragTexCoord; // Coordenadas de textura desde el vertex shader

uniform vec4 colorDifuso;
uniform sampler2D texture1; // Textura del material

// Material
uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float ns;

// Luz ambiental
uniform vec3 Ia;

// Luz puntual (Direccional + Foco)
uniform vec3 lightPosition;
uniform vec3 Id;
uniform vec3 Is;

// Luz direccional
uniform vec3 lightDirection;

// Luz foco
uniform vec3 spotPosition;
uniform vec3 spotDirection;
uniform float spotAngle;
uniform float spotExponent;

out vec4 fragColor;

subroutine vec4 calcularColor();
subroutine vec3 calcularLuz();

subroutine uniform calcularColor metodoColorElegido;
subroutine uniform calcularLuz metodoLuzElegido;

subroutine(calcularLuz)
vec3 calculateAmbient()
{
    return Ia * Ka;
}

subroutine(calcularLuz)
vec3 calculatePointLight()
{
    vec3 L = normalize(lightPosition - fragPosition);
    vec3 N = normalize(fragNormal);
    vec3 V = normalize(-fragPosition);
    vec3 R = reflect(-L, N);

    vec3 diffuse = max(dot(N, L), 0.0) * Kd * Id;
    vec3 specular = vec3(0.0);
    if (dot(N, L) > 0.0)
    {
        specular = pow(max(dot(R, V), 0.0), ns) * Ks * Is;
    }
    return diffuse + specular;
}

subroutine(calcularLuz)
vec3 calculateDirectionalLight()
{
    vec3 L = normalize(-lightDirection);
    vec3 N = normalize(fragNormal);
    vec3 V = normalize(-fragPosition);
    vec3 R = reflect(-L, N);

    vec3 diffuse = max(dot(N, L), 0.0) * Kd * Id;
    vec3 specular = vec3(0.0);
    if (dot(N, L) > 0.0)
    {
        specular = pow(max(dot(R, V), 0.0), ns) * Ks * Is;
    }
    return diffuse + specular;
}

subroutine(calcularLuz)
vec3 calculateSpotLight()
{
    vec3 L = normalize(spotPosition - fragPosition);
    vec3 D = normalize(-spotDirection);
    float theta = dot(D, L);
    float cosGamma = cos(spotAngle);

    float spotFactor = pow(max(theta, 0.0), spotExponent) * step(cosGamma, theta);

    vec3 N = normalize(fragNormal);
    vec3 V = normalize(-fragPosition);
    vec3 R = reflect(-L, N);

    vec3 diffuse = max(dot(N, L), 0.0) * Kd * Id;
    vec3 specular = vec3(0.0);
    if (dot(N, L) > 0.0)
    {
        specular = pow(max(dot(R, V), 0.0), ns) * Ks * Is;
    }

    return spotFactor * (diffuse + specular);
}

subroutine(calcularColor)
vec4 colorNegro ()
{
    return vec4 ( 0, 0, 0, 1 );
}

subroutine(calcularColor)
vec4 colorDifusoMaterial ()
{
    //return vec4 ( metodoLuzElegido(), 1.0 );
    vec3 luz = metodoLuzElegido(); // Calcular iluminación según el método elegido
    vec4 texturaColor = texture(texture1, fragTexCoord); // Muestra el color de la textura
    return vec4(luz, 1.0) * texturaColor; // Combina iluminación con textura
}

subroutine(calcularColor)
vec4 colorTexturaMaterial ()
{
    vec3 luz = metodoLuzElegido(); // Calcular iluminación según el método elegido
    vec4 texturaColor = texture(texture1, fragTexCoord); // Muestra el color de la textura
    return vec4(luz, 1.0) * texturaColor; // Combina iluminación con textura
}

void main()
{
    fragColor = metodoColorElegido();
}