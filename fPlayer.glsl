#version 330 core

out vec4 FragColor;
in vec3 vertexPos;

in vec3 normalPos;

void main() {
    vec3 objectColor = vec3(0.3, 0.1, 0.37);
    vec3 lightPos = vec3(-4.0, 5.0, 0.0);
    vec3 lightColor = vec3(1.0, 1.0, 1.0);

    float ambientStength = 0.2;

    vec3 ambientLight = ambientStength*lightColor;

    vec3 vertexDist = normalize(lightPos-vertexPos);
    float diff = max(dot(vertexDist, normalPos), 0.0)*2;
    vec3 diffuseLight = diff*lightColor;

    vec3 result = (diffuseLight+ambientLight)*objectColor;

    FragColor = vec4(result, 1.0);
}