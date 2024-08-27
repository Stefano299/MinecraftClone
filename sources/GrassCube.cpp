//
// Created by stefano on 8/20/24.
//

#include "../headers/GrassCube.h"

float GrassCube::data[216] = {

        //BACK
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,


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
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,

        //BOTTOM
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,

        //TOP
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 2.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 2.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 2.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 2.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 2.0,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 2.0f,
};

unsigned int GrassCube::VAO = 0;
unsigned int GrassCube::VBO = 0;
unsigned int GrassCube::sideTexture = 0;
unsigned int GrassCube::topTexture = 0;
unsigned int GrassCube::bottomTexture = 0;
Shader GrassCube::grassShader;

GrassCube::GrassCube(const glm::vec3 &pos, Type type)
{
    this->pos = pos;
    this->type = type;
    hidden = false;
    model = glm::translate(glm::mat4(1.0), pos);
    grassShader.useProgram();
    grassShader.changeUniform4M("model", model);
}

void GrassCube::draw() {
    glBindVertexArray(VAO);

    grassShader.useProgram();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, sideTexture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, topTexture);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, bottomTexture);


    //Oh ma dove stramaledattamente è sto bug cazzo
    //glBindTexture(GL_TEXTURE_2D, 0);
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

    //codice di merda dovevo fare una classe texture ma senttie che cazzo me ne frega tanto è solo un cubo
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

    grassShader.loadVertex("../shaders/vGrass.glsl");
    grassShader.loadFragment("../shaders/fGrass.glsl");
    grassShader.createProgram();

    grassShader.useProgram();

    grassShader.changeUniform1i("side", 0);
    grassShader.changeUniform1i("top", 1);
    grassShader.changeUniform1i("bottom", 2);
}

void GrassCube::updateMatrix(const glm::mat4 &view, const glm::mat4& projection) {
    grassShader.useProgram();
    grassShader.changeUniform4M("view", view);
    grassShader.changeUniform4M("projection", projection);
}

const glm::vec3 &GrassCube::getPos() const {
    return pos;
}

void GrassCube::setPos(const glm::vec3& newPos) {
    pos = newPos;
    model = glm::translate(glm::mat4(1.0), pos);
}

bool GrassCube::operator!=(const GrassCube &right) const{
    if(pos != right.pos){
        return true;
    }
    else
        return false;
}

void GrassCube::setHidden(bool h) {
    hidden = h;
}

bool GrassCube::isHidden() const {
    return hidden;
}

unsigned int GrassCube::getVAO() {
    return VAO;
}

const glm::mat4& GrassCube::getModel() const {
    return model;
}

Type GrassCube::getType() const {
    return type;
}

bool GrassCube::operator==(const GrassCube &right) const {
    return(pos == right.pos);
}
