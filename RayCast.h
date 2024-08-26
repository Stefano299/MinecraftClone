//
// Created by stefano on 8/26/24.
//

#ifndef MINECRAFT_RAYCAST_H
#define MINECRAFT_RAYCAST_H

#include <iostream>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SFML/Window.hpp>

class RayCast {
private:
    bool isPresent(const glm::vec3 &pointPos, const glm::vec3& cubePos) const; //Per determinare se in una posizione si trova un cubo
    int step;  //TODO se non uso l'attributo step lo posso anche rimuovere
    float stepLength;
    int lastStep;
public:
    RayCast();
    bool checkCube(const glm::vec3 &startPos, const glm::vec3 &direction, const glm::vec3& cubePos);
};


#endif //MINECRAFT_RAYCAST_H
