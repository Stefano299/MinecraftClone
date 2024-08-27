#version 330 core

in vec3 texCoord;
flat in int cubeType;

out vec4 FragColor;

uniform sampler2D side;
uniform sampler2D top;
uniform sampler2D bottom;

void main() {
    if(cubeType == 1) { //Se è tipo grass
        if (texCoord.z == 0.0f) {
            FragColor = texture(side, vec2(texCoord));
        }
        else if (texCoord.z == 2.0f) {
            FragColor = texture(top, vec2(texCoord));
        }
        else if (texCoord.z == 1.0f) {
            FragColor = texture(bottom, vec2(texCoord));
        }
    }
    else if(cubeType == 0){  //Se è tipo terrain
        FragColor = texture(bottom, vec2(texCoord));
    }
}