//
// Created by stefano on 8/25/24.
//

#include "../headers/Plane.h"

Plane::Plane(const glm::vec3 &point0, const glm::vec3 &point1, const glm::vec3 &point2) {
    a = glm::determinant(glm::mat2 (point1.y - point0.y, point1.z - point0.z,
                                    point2.y - point0.y, point2.z - point0.z));
    b = (-1)*glm::determinant(glm::mat2 (point1.x - point0.x, point1.z - point0.z,
                                         point2.x - point0.x, point2.z - point0.z));
    c = glm::determinant(glm::mat2 (point1.x - point0.x, point1.y - point0.y,
                                    point2.x - point0.x, point2.y - point0.y));
    d = -a*point0.x-b*point0.y-c*point0.z;
}

float Plane::calcPointDist(const glm::vec3 &point) const {
    return ((abs(a*point.x+b*point.y+c*point.z+d))/(sqrt(a*a+b*b+c*c)));
}

void Plane::calcParams(const glm::vec3 &point0, const glm::vec3 &point1, const glm::vec3 &point2) {
    a = glm::determinant(glm::mat2 (point1.y - point0.y, point1.z - point0.z,
                                    point2.y - point0.y, point2.z - point0.z));
    b = (-1)*glm::determinant(glm::mat2 (point1.x - point0.x, point1.z - point0.z,
                                         point2.x - point0.x, point2.z - point0.z));
    c = glm::determinant(glm::mat2 (point1.x - point0.x, point1.y - point0.y,
                                    point2.x - point0.x, point2.y - point0.y));
    d = -a*point0.x-b*point0.y-c*point0.z;
}
