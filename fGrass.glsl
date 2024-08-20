#version 330 core

in vec3 texCoord;

out vec4 FragColor;

uniform sampler2D side;
uniform sampler2D top;
uniform sampler2D bottom;

void main() {
    if(texCoord.z == 0.0f) {
        FragColor = texture(side, vec2(texCoord));
    }
    else if(texCoord.z == 2.0f){
        FragColor = texture(top, vec2(texCoord));
    }
    else if(texCoord.z == 1.0f){
        FragColor = texture(bottom, vec2(texCoord));
    }
}