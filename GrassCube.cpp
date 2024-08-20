//
// Created by stefano on 8/20/24.
//

#include "GrassCube.h"

float GrassCube::data[216] = {

        //BACK
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,

        //FRONT
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,

        //SIDE LEFT
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,

        //SIDE RIGHT
        0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,

        //BOTTOM
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,

        //TOP
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 2.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 2.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 2.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 2.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 2.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 2.0
};

unsigned int GrassCube::VAO = 0;
unsigned int GrassCube::VBO = 0;
unsigned int GrassCube::sideTexture = 0;
unsigned int GrassCube::topTexture = 0;
unsigned int GrassCube::bottomTexture = 0;
Shader GrassCube::grassShader;
Shader GrassCube::terrainShader;

GrassCube::GrassCube(const glm::vec3 &pos, Type type)
{
    this->pos = pos;
    this->type = type;
    if(type == Type::Grass){
        grassShader.changeUniform4M("model", glm::translate(glm::mat4(1.0), pos));
    }
    else if(type == Type::Terrain){
        terrainShader.changeUniform4M("model", glm::translate(glm::mat4(1.0), pos));
    }
}

void GrassCube::draw() const {
    glBindVertexArray(VAO);
    if(type == Type::Grass) {
        grassShader.useProgram();
        grassShader.changeUniform4M("model", glm::translate(glm::mat4(1.0), pos));
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, sideTexture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, topTexture);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, bottomTexture);
    }
    else if(type == Type::Terrain){
        terrainShader.useProgram();
        terrainShader.changeUniform4M("model", glm::translate(glm::mat4(1.0), pos));
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, bottomTexture);
    }

    glDrawArrays(GL_TRIANGLES, 0, 36);

    //Oh ma dove stramaledattamente è sto bug cazzo
    //glBindTexture(GL_TEXTURE_2D, 0);
}

GrassCube::~GrassCube() {
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteTextures(1, &sideTexture);
    glDeleteTextures(1, &topTexture);
    glDeleteTextures(1, &bottomTexture);
}

void GrassCube::init() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, (void*)(sizeof(float)*3));
    glEnableVertexAttribArray(1);

    glGenTextures(1, &sideTexture);
    glBindTexture(GL_TEXTURE_2D, sideTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    int width, height, nChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("../img/side.png", &width, &height, &nChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    glGenTextures(1, &topTexture);
    glBindTexture(GL_TEXTURE_2D, topTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    data = stbi_load("../img/top.png", &width, &height, &nChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    glGenTextures(1, &bottomTexture);
    glBindTexture(GL_TEXTURE_2D, bottomTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    data = stbi_load("../img/bottom.png", &width, &height, &nChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    grassShader.loadVertex("../vGrass.glsl");
    grassShader.loadFragment("../fGrass.glsl");
    grassShader.createProgram();

    grassShader.useProgram();

    grassShader.changeUniform1i("side", 0);
    grassShader.changeUniform1i("top", 1);
    grassShader.changeUniform1i("bottom", 2);

    terrainShader.loadVertex("../vGrass.glsl");
    terrainShader.loadFragment("../fTerrain.glsl");
    terrainShader.createProgram();

    terrainShader.useProgram();
    terrainShader.changeUniform1i("texture1", 0);
}

void GrassCube::updateMatrix(const glm::mat4 &view, const glm::mat4& projection) {
    grassShader.changeUniform4M("view", view);
    grassShader.changeUniform4M("projection", projection);
    terrainShader.changeUniform4M("view", view);
    terrainShader.changeUniform4M("projection", projection);
}

const glm::vec3 &GrassCube::getPos() const {
    return pos;
}

void GrassCube::setPos(const glm::vec3& newPos) {
    pos = newPos;
}
