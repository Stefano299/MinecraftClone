//
// Created by stefano on 8/26/24.
//

#ifndef MINECRAFT_RAYCAST_H
#define MINECRAFT_RAYCAST_H

#include <iostream>
#include <SFML/Window.hpp>

#include "glad/glad.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

enum class Face{
    front,
    back,
    top,
    bottom,
    left,
    right
};
class RayCast {
private:
    bool isPresent(const glm::vec3 &pointPos, const glm::vec3& cubePos) const; //Per determinare se in una posizione si trova un cubo
    int step;
    float stepLength;
    int lastStep;
    glm::vec3 origin;
    glm::vec3 direction;
public:
    RayCast();
    bool checkCube(const glm::vec3 &startPos, const glm::vec3 &direction, const glm::vec3& cubePos);
    int getStep() const;
    Face calcSelectedFace(const glm::vec3& cubePos) const;
};


#endif //MINECRAFT_RAYCAST_H
