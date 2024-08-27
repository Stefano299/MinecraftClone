//
// Created by stefano on 8/23/24.
//

#include "../headers/Sphere.h"
#include "../headers/Player.h"

void Sphere::createShader() {
    shader.loadVertex("../shaders/vLight.glsl");
    shader.loadFragment("../shaders/fLight.glsl");
    shader.createProgram();
}

Sphere::Sphere(const glm::vec3 &pos, const Player& player) {
    this->pos = pos;
    createShader();
    createVertices();
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, (void*)0);
    glEnableVertexAttribArray(0);
    shader.useProgram();
    shader.changeUniform4M("model", glm::translate(glm::mat4(1.0), pos));
    player.setLightPos(pos);
}

void Sphere::createVertices() {
    for(int i = 0; i < 18; i++){
        float y1 = cos(glm::radians(i*10.0f));
        float y2 = cos(glm::radians((i+1)*10.0f));
        float coeff1 = sin(glm::radians((i)*10.0f)); //Coefficenti da moltiplicare per le coordinate, come con il cos del pitch
        float coeff2 = sin(glm::radians((i+1)*10.0f));
        for(int j = 0; j < 36; j++){
            float x1 = sin(glm::radians(j*10.0f));
            float z1 = cos(glm::radians(j*10.0f));
            float x2 = sin(glm::radians((j+1)*10.0f));
            float z2 = cos(glm::radians((j+1)*10.0f));

            vertices[i*18*36+j*18] = x1*coeff1;
            vertices[i*18*36+j*18+1] = y1;
            vertices[i*18*36+j*18+2] = z1*coeff1;

            vertices[i*18*36+j*18+3] = x2*coeff2;
            vertices[i*18*36+j*18+4] = y2;
            vertices[i*18*36+j*18+5] = z2*coeff2;

            vertices[i*18*36+j*18+6] = x1*coeff2;
            vertices[i*18*36+j*18+7] = y2;
            vertices[i*18*36+j*18+8] = z1*coeff2;

            vertices[i*18*36+j*18+9] = x2*coeff1;
            vertices[i*18*36+j*18+10] = y1;
            vertices[i*18*36+j*18+11] = z2*coeff1;

            vertices[i*18*36+j*18+12] =x2*coeff2;
            vertices[i*18*36+j*18+13] = y2;
            vertices[i*18*36+j*18+14] = z2*coeff2;

            vertices[i*18*36+j*18+15] = x1*coeff1;
            vertices[i*18*36+j*18+16] = y1;
            vertices[i*18*36+j*18+17] = z1*coeff1;
        }
    }
}

void Sphere::draw(const glm::mat4& projection, const glm::mat4& view) const {
    shader.useProgram();
    shader.changeUniform4M("view", view);
    shader.changeUniform4M("projection", projection);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3888);
}


