//
// Created by stefano on 8/20/24.
//

#ifndef MINECRAFT_GRASSCUBE_H
#define MINECRAFT_GRASSCUBE_H

#include <iostream>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include"stb_image.h"
#include"Shader.h"

enum Type{
    Terrain,
    Grass
};

class GrassCube {
private:
    static float data[216];
    static unsigned int VAO;
    static unsigned int VBO;
    static unsigned int sideTexture;
    static unsigned int topTexture;
    static unsigned int bottomTexture;
    static Shader grassShader;
    static Shader terrainShader;
    Type type;
    glm::vec3 pos;
public:
    GrassCube(const glm::vec3& pos, Type type);
    static void init();
    void draw() const;
    static void updateMatrix(const glm::mat4& view, const glm::mat4& projection);
    const glm::vec3& getPos() const;
    void setPos(const glm::vec3& newPos);
};


#endif //MINECRAFT_GRASSCUBE_H
