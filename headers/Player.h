//
// Created by stefano on 8/23/24.
//

#ifndef MINECRAFT_PLAYER_H
#define MINECRAFT_PLAYER_H

#include <iostream>
#include <SFML/Window.hpp>

#include "glad/glad.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Shader.h"

class PhysicsWorld;
class Player {
private:
    void createVertices();
    void calculateNormals();
    void createShader();
    float vertices[1944];
    float normals[1944]; //Per ogni vertici dò il vettore normale
    unsigned int VAO;
    unsigned int verticesVBO;
    unsigned int normalsVBO;
    glm::vec3 pos;
    glm::mat4 model;
    float yaw;
    Shader shader;
    PhysicsWorld* physicsWorld;
    float speed;
    bool falling;
    bool sideColliding;
    bool jumping;
    bool firstPerson;
public:
    explicit Player(const glm::vec3& pos, float speed = 0.2);
    void setPhysicsWorld( PhysicsWorld* physicsWorld1);
    void draw(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& cameraPos) const;
    const glm::vec3& getPos() const;
    void setPos(const glm::vec3& newPos);
    void handleInput();
    void setLightPos(const glm::vec3& pos) const;
    void setFalling(bool f);
    bool isFalling() const;
    float getSpeed() const;
    void setSideColliding(bool c);
    bool isSideColliding() const;
    bool isJumping() const;
    void setJumping(bool j);
    void changeY(float dy);
    void setYaw(float yaw);
    void setFirstPerson(bool f);
    float getYaw() const;
};


#endif //MINECRAFT_PLAYER_H
