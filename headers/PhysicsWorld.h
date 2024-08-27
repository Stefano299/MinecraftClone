//
// Created by stefano on 8/25/24.
//

#ifndef MINECRAFT_PHYSICSWORLD_H
#define MINECRAFT_PHYSICSWORLD_H

#include "frameTime.h"
#include "RayCast.h"
#include "CubeBorder.h"

class CubesContainer;
class Player;
class PhysicsWorld {
private:
    Player* player;
    CubesContainer* cubesContainer;
    long int startFallingTime;
    RayCast rayCast;
    CubeBorder cubeBorder;
    bool isCubeColliding(const glm::vec3& cubePos, const glm::vec3& playerPos) const;  //Se player collide con il sopra di un cubo
    bool isCubeSideColliding(const glm::vec3& cubePos, const glm::vec3& playerPos) const;
    bool isPlayerFalling(glm::vec3& collidingCubePos) const; //Controlla se player sta cadendo dalla superficie
    bool isPlayerCollidingSides(const glm::vec3& move) const;
    bool isNear(const glm::vec3& point1, const glm::vec3 point2, float dist) const;
    float fallCoeff;
    bool rayCastFound;

public:
    PhysicsWorld(Player* player, CubesContainer* cubesContainer);
    void playerFall(); //Si occupa a far cadere il player
    void playerSideCollisions(const glm::vec3& move) const;
    void playerJump() const;
    void rayCastCheck(const glm::vec3& camDirection);
    void drawBorderCube(const glm::mat4& projection, const glm::mat4& view) const;
    void cubeInteractions(sf::Event& event);
};


#endif //MINECRAFT_PHYSICSWORLD_H
