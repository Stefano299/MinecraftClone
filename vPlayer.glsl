#version 330 core
layout (location = 0) in vec3 vPos;
layout  (location = 1) in vec3 nPos;

out vec3 normalPos;
out vec3 vertexPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection*view*model*vec4(vPos, 1.0);
    vertexPos = vec3(model*vec4(vPos,1.0));
    normalPos = mat3(transpose(inverse(model)))*nPos;
}