#version 330 core

out vec4 FragColor;

in vec3 vertexPos;

void main() {
    float height = vertexPos.y;  //Voglio il colore sia più scuro sotto e diventi man mano più chiaro
    float heightCoeff = (height+1)/2; //le y dei vertici partono da -1
    vec3 color = vec3(0.974, 1.0, 0.71)-0.5;
    vec3 result = color + heightCoeff*heightCoeff*0.7;
    FragColor = vec4(result ,1.0); //giallino chiaro
}