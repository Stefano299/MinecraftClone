//
// Created by stefano on 8/26/24.
//

#include "../headers/CrossAir.h"
#include "../headers/constants.h"

float vertexData[36] = {-1.0f, -0.2f, 0.0f,
                  1.0f, -0.2f, 0.0f,
                  1.0f, 0.2f, 0.0f,

                  1.0f, 0.2f, 0.0f,
                  -1.0f, 0.2f, 0.0f,
                  -1.0f, -0.2f, 0.0f,

                  -0.2f, -1.0f, 0.0f,
                  0.2f, -1.0f, 0.0f,
                  0.2f, 1.0f, 0.0f,

                  0.2f, 1.0f, 0.0f,
                  -0.2f, 1.0f, 0.0f,
                  -0.2f, -1.0f, 0.0f};

CrossAir::CrossAir() {
    VAO = 0;
    VBO = 0;
    initVertices();
    initBuffers();
    initShader();
    setScale();
}

void CrossAir::initVertices() {
    for(int i = 0; i < 36; i++){
        vertices[i] = vertexData[i];
    }
}

void CrossAir::initBuffers() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, (void*)0);
    glEnableVertexAttribArray(0);
}

void CrossAir::initShader() {
    shader.loadVertex("../shaders/vCrossAir.glsl");
    shader.loadFragment("../shaders/fCrossAir.glsl");
    shader.createProgram();
}

void CrossAir::draw(const glm::mat4& projection) const {
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
    shader.useProgram();
    shader.changeUniform4M("projection", projection);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 12);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
}

void CrossAir::setScale() {
    int screenTotalSize = SCREEN_HEIGHT+SCREEN_WIDTH;  //Per mantenerlo piccolo anche a grandi risoluzioni
    double scaleFactor = (0.001/4000)*screenTotalSize;
    model = glm::translate(glm::mat4(1.0), glm::vec3(0.0, 0.0, -0.1));
    model = glm::scale(model, glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    shader.useProgram();
    shader.changeUniform4M("model", model);
}
