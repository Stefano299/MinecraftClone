//
// Created by stefano on 8/26/24.
//

#ifndef MINECRAFT_CROSSAIR_H
#define MINECRAFT_CROSSAIR_H

#include <iostream>
#include <SFML/Window.hpp>

#include "glad/glad.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Shader.h"

class  Shader;
class CrossAir {
private:
    void initVertices();
    void initBuffers();
    void initShader();
    void setScale();
    float vertices[36];
    unsigned int VAO;
    unsigned int VBO;
    Shader shader;
    glm::mat4 model;
public:
    CrossAir();
    void draw(const glm::mat4& projection) const;
};


#endif //MINECRAFT_CROSSAIR_H
