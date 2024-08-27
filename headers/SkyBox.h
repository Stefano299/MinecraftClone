//
// Created by stefano on 8/24/24.
//

#ifndef MINECRAFT_SKYBOX_H
#define MINECRAFT_SKYBOX_H

#include <iostream>
#include <SFML/Window.hpp>

#include "glad/glad.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Shader.h"

class SkyBox {
private:
    void setPaths();
    void setVertices();
    void initBuffers();
    void initTextures();
    void loadShader();
    std::string paths[6];
    float vertices[108];
    unsigned int VAO;
    unsigned int VBO;
    unsigned int cubeMapText;
    Shader shader;
public:
    SkyBox();
    void draw(const glm::mat4& projection, const glm::mat4& view) const;
};


#endif //MINECRAFT_SKYBOX_H
