#version 330 core

out vec4 FragColor;
in vec3 vertexPos;

in vec3 normalPos;

uniform vec3 lightPos;
uniform vec3 cameraPos;

void main() {
    vec3 objectColor = vec3(16/235.f, 101/235.f, 230/235.f);
    vec3 lightColor = vec3(0.974, 1.0, 0.71);

    float ambientStength = 0.5;

    vec3 ambientLight = ambientStength*lightColor;

    vec3 vertexDist = normalize(lightPos-vertexPos);
    float diff = max(dot(vertexDist, normalPos), 0.0)*2;
    vec3 diffuseLight = diff*lightColor;

    vec3 reflectionDir = normalize(reflect(-vertexDist, normalPos));
    vec3 viewDir = normalize(cameraPos-vertexPos);
    float shiness = 2;
    float specular = pow(max(dot(viewDir, reflectionDir), 0.0), 64);
    float specularLight = specular*shiness;

    vec3 result = (diffuseLight+ambientLight+specularLight)*objectColor;

    FragColor = vec4(result, 1.0);
}