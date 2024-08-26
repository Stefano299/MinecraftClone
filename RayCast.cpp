//
// Created by stefano on 8/26/24.
//

#include "RayCast.h"

RayCast::RayCast() {
    step = 1;
    stepLength = 0.02; //Abbastanza piccolo per essere piuttosto preciso
    lastStep = 250;
}

bool RayCast::checkCube(const glm::vec3 &startPos, const glm::vec3 &direction, const glm::vec3& cubePos) {
    //do per scontato direction sia NORMALIZZATO
    step = 1;
    bool hit = false;
    for(int i = 1; i<= lastStep; i++){  //TODO scrivere meglio questo loop, magari facendolo while
        float length = stepLength*step;
        glm::vec3 point = startPos+direction*length;
        if(isPresent(point, cubePos)){
            hit = true;
            break;
        }
        step++;
    }
    return hit;
}

bool RayCast::isPresent(const glm::vec3 &pointPos, const glm::vec3& cubePos) const {
    return(std::abs(cubePos.x-pointPos.x) <= 0.5 && std::abs(cubePos.y-pointPos.y) <= 0.5 && std::abs(cubePos.z-pointPos.z) <= 0.5);
}

int RayCast::getStep() const {
    return step;
}
