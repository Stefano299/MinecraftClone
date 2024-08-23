//
// Created by stefano on 8/23/24.
//

#ifndef MINECRAFT_PLAYER_H
#define MINECRAFT_PLAYER_H

#include <iostream>
#include <SFML/Window.hpp>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include"stb_image.h"
#include"Shader.h"


class Player {
private:
    void createVertices();
    void calculateNormals();
    void createShader();
    float vertices[648];
    float normals[648]; //Per ogni vertici dò il vettore normale
    unsigned int VAO;
    unsigned int verticesVBO;
    unsigned int normalsVBO;
    glm::vec3 pos;
    Shader shader;
    float speed;
public:
    explicit Player(const glm::vec3& pos, float speed = 0.2);
    void draw(const glm::mat4& projection, const glm::mat4& view) const;
    const glm::vec3& getPos() const;
    void setPos(const glm::vec3& newPos);
    void handleInput();
};


#endif //MINECRAFT_PLAYER_H
