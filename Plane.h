//
// Created by stefano on 8/25/24.
//

#ifndef MINECRAFT_PLANE_H
#define MINECRAFT_PLANE_H

#include <iostream>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Plane {
public:
    float a;
    float b;
    float c;
    float d;
public:
    Plane() = default;
    Plane(const glm::vec3& point0, const glm::vec3& point1, const glm::vec3& point2);
    void calcParams(const glm::vec3& point0, const glm::vec3& point1, const glm::vec3& point2);
    float calcPointDist(const glm::vec3& point) const;
};


#endif //MINECRAFT_PLANE_H
