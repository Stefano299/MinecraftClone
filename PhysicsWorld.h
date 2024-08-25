//
// Created by stefano on 8/25/24.
//

#ifndef MINECRAFT_PHYSICSWORLD_H
#define MINECRAFT_PHYSICSWORLD_H

#include"CubesContainer.h"
#include"frameTime.h"
#include"Player.h"

class PhysicsWorld {
private:
    Player* player;
    CubesContainer* cubesContainer;
    long int startFallingTime;
    bool isCubeColliding(const glm::vec3& cubePos) const;  //Se player collide con il sopra di un cubo
    bool isPlayerFalling() const; //Controlla se player sta cadendo dalla superficie

public:
    PhysicsWorld(Player* player, CubesContainer* cubesContainer);
    void playerFall(); //Si occupa a far cadere il player
};


#endif //MINECRAFT_PHYSICSWORLD_H
