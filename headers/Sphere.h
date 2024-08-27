//
// Created by stefano on 8/23/24.
//

#ifndef MINECRAFT_SPHERE_H
#define MINECRAFT_SPHERE_H

#include <iostream>
#include <SFML/Window.hpp>

#include "glad/glad.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Shader.h"

class Player;
class Sphere {
private:
    void createShader();
    void createVertices();
    float vertices[11664];
    unsigned int VAO;
    unsigned int VBO;
    glm::vec3 pos;
    Shader shader;
public:
    explicit Sphere(const glm::vec3& pos, const Player& player);
    void draw(const glm::mat4& projection, const glm::mat4& view) const;
};


#endif //MINECRAFT_SPHERE_H
