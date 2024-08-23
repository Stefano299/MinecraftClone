#version 330 core

out vec4 FragColor;
in vec3 vertexPos;

in vec3 normalPos;

uniform vec3 lightPos;

void main() {
    vec3 objectColor = vec3(0.3, 0.1, 0.37);
    vec3 lightColor = vec3(0.974, 1.0, 0.71);

    float ambientStength = 0.5;

    vec3 ambientLight = ambientStength*lightColor;

    vec3 vertexDist = normalize(lightPos-vertexPos);
    float diff = max(dot(vertexDist, normalPos), 0.0)*2;
    vec3 diffuseLight = diff*lightColor;

    vec3 result = (diffuseLight+ambientLight)*objectColor;

    FragColor = vec4(result, 1.0);
}