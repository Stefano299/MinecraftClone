//
// Created by stefano on 8/26/24.
//

#ifndef MINECRAFT_CUBEBORDER_H
#define MINECRAFT_CUBEBORDER_H

#include <iostream>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include"stb_image.h"
#include"Shader.h"

class CubeBorder {
private:
    void initVertices();
    void initBuffers();
    void initShader();
    float vertices[72];
    unsigned int VAO;
    unsigned int VBO;
    glm::vec3 pos;
    glm::mat4 model;
    Shader shader;
public:
    CubeBorder();
    void setPos(const glm::vec3& newPos);
    const glm::vec3& getPos() const;
    void draw(const glm::mat4& projection, const glm::mat4& view) const;
};


#endif //MINECRAFT_CUBEBORDER_H
