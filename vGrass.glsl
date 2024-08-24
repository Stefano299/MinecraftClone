#version 330 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 tCoord;
layout (location = 2) in mat4 cubeModel;
layout (location = 6) in int cType;

out vec3 texCoord;

flat out int cubeType;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection*view*cubeModel*vec4(vPos, 1.0);
    texCoord = tCoord;
    cubeType = cType;
}