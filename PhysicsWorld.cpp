//
// Created by stefano on 8/25/24.
//

#include "PhysicsWorld.h"

bool PhysicsWorld::isPlayerFalling() const {
    for(const auto& it: cubesContainer->getTopCubesPos()){
        if(isCubeColliding(it)){
            return false;
        }
    }
    return true;
}

PhysicsWorld::PhysicsWorld(Player *player, CubesContainer *cubesContainer) {
    this->player = player;
    this->cubesContainer = cubesContainer;
    startFallingTime = 0;
    //maxPlayerFloorDist = sqrt(0.5*0.5+)
}

bool PhysicsWorld::isCubeColliding(const glm::vec3& cubePos) const {
    float bottomPlayerY = player->getPos().y-1;
    float cubeTopY = cubePos.y+0.5f;
    float cubeBottomY = cubePos.y-0.5f;
    bool isCollidingXZ = (abs(player->getPos().z - cubePos.z) <= 1 && abs(player->getPos().x - cubePos.x) <= 1); //Ritorna verso  se il centro è tra i confini dl blocco (x e z)
    bool isCollidingY = (bottomPlayerY <= cubeTopY && cubeBottomY - bottomPlayerY <= 2);  //(Controlla collisione nella y)
    return(isCollidingXZ && isCollidingY);
}

void PhysicsWorld::playerFall() {
    if(isPlayerFalling()){
        if(!player->isFalling()) {
            player->setFalling(true);
            startFallingTime = frameTime;
        }
        float elapsedTime = (frameTime-startFallingTime)*0.3f;
        player->setPos(player->getPos()+(glm::vec3 (0.0, -0.01, 0.0)*elapsedTime));
    }
    else{
        player->setFalling(false);
        startFallingTime = 0;
    }
}
