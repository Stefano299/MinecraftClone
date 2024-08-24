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
    bool hidden; //Se è circondato da cubi è nasconto e non va disegnato
    Type type;
    glm::vec3 pos;
    glm::mat4 model;
public:
    GrassCube(const glm::vec3& pos, Type type);
    static void init();
    static void draw();
    static void updateMatrix(const glm::mat4& view, const glm::mat4& projection);
    static unsigned int getVAO();
    const glm::vec3& getPos() const;
    void setPos(const glm::vec3& newPos);
    bool operator!=(const GrassCube& right) const;
    void setHidden(bool h);
    bool isHidden() const;
    const glm::mat4& getModel() const;
};


#endif //MINECRAFT_GRASSCUBE_H
