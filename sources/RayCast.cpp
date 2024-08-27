//
// Created by stefano on 8/26/24.
//

#include "../headers/RayCast.h"
#include<list>

RayCast::RayCast() {
    step = 1;
    stepLength = 0.02; //Abbastanza piccolo per essere piuttosto preciso
    lastStep = 250;
}

bool RayCast::checkCube(const glm::vec3 &startPos, const glm::vec3 &direction, const glm::vec3& cubePos) {
    //do per scontato direction sia NORMALIZZATO
    origin = startPos;
    this->direction = direction;
    step = 1;
    bool hit = false;
    while(!hit && step <= lastStep){
        float length = stepLength*step;
        step++;
        glm::vec3 point = startPos+direction*length;
        if(isPresent(point, cubePos)){
            hit = true;
        }
    }
    return hit;
}

bool RayCast::isPresent(const glm::vec3 &pointPos, const glm::vec3& cubePos) const {
    //Aggiungo margine di errore per la funzione getFaces
    return(std::abs(cubePos.x-pointPos.x) <= 0.501 && std::abs(cubePos.y-pointPos.y) <= 0.501 && std::abs(cubePos.z-pointPos.z) <= 0.501);
}

int RayCast::getStep() const {
    return step;
}

Face RayCast::calcSelectedFace(const glm::vec3 &cubePos) const {
    // PUNTO = STARTPOS + T*DIRECTION
    // T = (PUNTO - STARTPOS)/DIRECTION
    float frontZ = cubePos.z+0.5f;
    float backZ = cubePos.z-0.5f;
    float rightX = cubePos.x+0.5f;
    float leftX = cubePos.x-0.5f;
    float topY = cubePos.y+0.5f;
    float bottomY = cubePos.y-0.5f;

    std::list<std::pair<Face, float>> tFaces;
    std::pair<Face, float> front = {Face::front, (frontZ-origin.z)/direction.z};
    std::pair<Face, float> back = {Face::back, (backZ-origin.z)/direction.z};
    std::pair<Face, float> top = {Face::top, (topY-origin.y)/direction.y};
    std::pair<Face, float> bottom = {Face::bottom, (bottomY-origin.y)/direction.y};
    std::pair<Face, float> right = {Face::right, (rightX-origin.x)/direction.x};
    std::pair<Face, float> left = {Face::left, (leftX-origin.x)/direction.x};
    tFaces.push_back(front);
    tFaces.push_back(back);
    tFaces.push_back(top);
    tFaces.push_back(bottom);
    tFaces.push_back(right);
    tFaces.push_back(left);

    auto it = tFaces.begin();
    while (it != tFaces.end()) {
        glm::vec3 point = origin + (it->second) * direction;
        if (!isPresent(point, cubePos)) {
            it = tFaces.erase(it);  // erase ritorna il prossimo iteratore valido
        } else {
            it++;  // Avanza l'iteratore solo se l'elemento non viene cancellato
        }
    }

    std::pair<Face, float> min = {Face::front, 100};
    for(auto& it: tFaces){
        if(it.second < min.second){
            min = it;
        }
    }
    return min.first;
}

