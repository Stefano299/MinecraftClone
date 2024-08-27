//
// Created by stefano on 8/26/24.
//

#include "../headers/CubeBorder.h"

float data[72] = {
        // Linee della base
        -0.5f, -0.5f, -0.5f,   0.5f, -0.5f, -0.5f,  // V0 -> V1
        0.5f, -0.5f, -0.5f,   0.5f,  0.5f, -0.5f,  // V1 -> V2
        0.5f,  0.5f, -0.5f,  -0.5f,  0.5f, -0.5f,  // V2 -> V3
        -0.5f,  0.5f, -0.5f,  -0.5f, -0.5f, -0.5f,  // V3 -> V0

        // Linee della parte superiore (z = 0.5f)
        -0.5f, -0.5f,  0.5f,   0.5f, -0.5f,  0.5f,  // V4 -> V5
        0.5f, -0.5f,  0.5f,   0.5f,  0.5f,  0.5f,  // V5 -> V6
        0.5f,  0.5f,  0.5f,  -0.5f,  0.5f,  0.5f,  // V6 -> V7
        -0.5f,  0.5f,  0.5f,  -0.5f, -0.5f,  0.5f,  // V7 -> V4

        // Linee verticali (collegano la base alla parte superiore)
        -0.5f, -0.5f, -0.5f,  -0.5f, -0.5f,  0.5f,  // V0 -> V4
        0.5f, -0.5f, -0.5f,   0.5f, -0.5f,  0.5f,  // V1 -> V5
        0.5f,  0.5f, -0.5f,   0.5f,  0.5f,  0.5f,  // V2 -> V6
        -0.5f,  0.5f, -0.5f,  -0.5f,  0.5f,  0.5f   // V3 -> V7
};

CubeBorder::CubeBorder() {
    VAO = 0;
    VBO = 0;
    this->pos = pos;
    initVertices();
    initBuffers();
    initShader();
}

void CubeBorder::initVertices() {
    for(int i = 0; i < 72; i++){
        vertices[i] = data[i];
    }
}

void CubeBorder::initBuffers() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, (void*)0);
    glEnableVertexAttribArray(0);
}

void CubeBorder::initShader() {
    shader.loadVertex("../shaders/vBorder.glsl");
    shader.loadFragment("../shaders/fBorder.glsl");
    shader.createProgram();
}

const glm::vec3 &CubeBorder::getPos() const {
    return pos;
}

void CubeBorder::setPos(const glm::vec3 &newPos) {
    pos = newPos;
    model = glm::translate(glm::mat4(1.0), pos);
    shader.useProgram();
    shader.changeUniform4M("model", model);
}

void CubeBorder::draw(const glm::mat4& projection, const glm::mat4& view) const {
    shader.useProgram();
    shader.changeUniform4M("projection", projection);
    shader.changeUniform4M("view", view);
    glEnable(GL_POLYGON_OFFSET_LINE);  //Voglio che la linea venga messa unpoì avanti nel depth buffer o non viene disegnata
    glPolygonOffset(-5.f, -3.f);
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 24);
    glDisable(GL_POLYGON_OFFSET_LINE);
}
