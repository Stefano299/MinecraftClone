//
// Created by stefano on 8/25/24.
//

#include "PhysicsWorld.h"

bool PhysicsWorld::isPlayerFalling() const {
    for(const auto& it: cubesContainer->getTopCubesPos()){
        glm::vec3 futurePlayerPos = player->getPos()+glm::vec3(0.0, fallCoeff, 0.0);
        if(isCubeColliding(it, futurePlayerPos)){
            return false;
        }
    }
    return true;
}

PhysicsWorld::PhysicsWorld(Player *player, CubesContainer *cubesContainer) {
    this->player = player;
    this->cubesContainer = cubesContainer;
    startFallingTime = 0;
    fallCoeff = 0;
    //maxPlayerFloorDist = sqrt(0.5*0.5+)
}

bool PhysicsWorld::isCubeColliding(const glm::vec3& cubePos, const glm::vec3& playerPos) const {
    float bottomPlayerY = playerPos.y-1;
    float cubeTopY = cubePos.y+0.5f;
    float cubeBottomY = cubePos.y-0.5f;
    bool isCollidingXZ = (abs(playerPos.z - cubePos.z) <= 1 && abs(playerPos.x - cubePos.x) <= 1); //Ritorna verso  se il centro è tra i confini dl blocco (x e z)
    bool isCollidingY = (bottomPlayerY <= cubeTopY && cubeBottomY - bottomPlayerY <= 2);  //(Controlla collisione nella y)
    return(isCollidingXZ && isCollidingY);
}

void PhysicsWorld::playerFall() {
    if(isPlayerFalling()){
        if(!player->isFalling()) {
            player->setFalling(true);
            startFallingTime = frameTime;
        }
        float elapsedTime = (frameTime-startFallingTime)*0.2f;
        player->setPos(player->getPos()+(glm::vec3 (0.0, -0.02*elapsedTime, 0.0)));
        fallCoeff = -0.02f*((frameTime+1-startFallingTime)*0.2f); //Devo contare quella che avrà al frame dopo
    }
    else{
        player->setFalling(false);
        fallCoeff = 0;
        startFallingTime = 0;
    }
}

bool PhysicsWorld::isPlayerCollidingSides(const glm::vec3& move) const {
    for(const auto& it: cubesContainer->getSideCubesPos()){
        //devo mettere fallcoeef
        glm::vec3 futurePlayerPos = player->getPos()+glm::vec3(move.x, 0, move.z); //XZ devono considerare il movimento laterale
        if(isCubeSideColliding(it, futurePlayerPos)){
            return true;
        }
    }
    return false;
}

bool PhysicsWorld::isCubeSideColliding(const glm::vec3 &cubePos, const glm::vec3 &playerPos) const {
    bool isCollidingXZ = (abs(playerPos.z - cubePos.z) < 1 && abs(playerPos.x - cubePos.x) < 1); //Ritorna verso  se il centro è tra i confini dl blocco (x e z)
    //Il player appare più alto... devorebbe quindi non considerare le collisioni con pavimento
    bool isCollidingY = (abs(playerPos.y-cubePos.y) < 1.5);  //(Controlla collisione nella y)
    return(isCollidingXZ && isCollidingY);
}

void PhysicsWorld::playerSideCollisions(const glm::vec3& move) const{
    if(isPlayerCollidingSides(move)){
        player->setSideColliding(true);
    }
    else{
        player->setSideColliding(false);
    }
}
