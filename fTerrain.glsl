#version 330 core

in vec3 texCoord;

out vec4 FragColor;

uniform sampler2D texture1;

void main() {
    FragColor = texture(texture1, vec2(texCoord));
}