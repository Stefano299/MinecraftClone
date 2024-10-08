//
// Created by stefano on 8/25/24.
//

#include "../headers/PhysicsWorld.h"
#include "../headers/CubesContainer.h"
#include "../headers/Player.h"

bool PhysicsWorld::isPlayerFalling(glm::vec3& collidingCubePos) const {
    for(const auto& it: cubesContainer->getVisibleCubesPos()){
        glm::vec3 futurePlayerPos = player->getPos()+glm::vec3(0.0, fallCoeff, 0.0);
        if(isCubeColliding(it, futurePlayerPos)){
            collidingCubePos = it;
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
    bool isCollidingXZ = (abs(playerPos.z - cubePos.z) <= 1 && abs(playerPos.x - cubePos.x) <= 1); //Ritorna verso  se il centro è tra i confini dl blocco (x e z)
    bool isCollidingY = (abs(playerPos.y-cubePos.y)<=1.5);  //(Controlla collisione nella y)
    return(isCollidingXZ && isCollidingY);
}

void PhysicsWorld::playerFall() {
    glm::vec3 collidingCubePos;
    if(isPlayerFalling(collidingCubePos)){ //Assegna alla variabile la posizione del cubo con cui collide
        if(!player->isFalling()) {
            player->setFalling(true);
            startFallingTime = frameTime;
        }
        float elapsedTime = (frameTime-startFallingTime)*0.2f;
        player->changeY(-0.02*elapsedTime);
        fallCoeff = -0.02f*((frameTime+1-startFallingTime)*0.2f); //Devo contare quella che avrà al frame dopo
        if(fallCoeff >= 1) fallCoeff = 1; //Sennò se è troppo grande controla il cubo sotto
    }
    else{
        if(player->isFalling()){ //Voglio che il blocco venga eseguto solo nel frame dopo che smette di cadere
            glm::vec3 playerPos = player->getPos();
            glm::vec3 newPos = glm::vec3 (playerPos.x, collidingCubePos.y+1.5, playerPos.z);
            player->setPos(newPos); //Per evitare che player venga teletrasportato troppo su, quando deve smette di cadere lo porto direttamente sopra il cubo sotto
            player->setJumping(false); //Quando tocca terra smette di saltare
            player->setFalling(false);
            fallCoeff = 0;
            startFallingTime = 0;
        }
    }
}

bool PhysicsWorld::isPlayerCollidingSides(const glm::vec3& move) const {
    for(const auto& it: cubesContainer->getVisibleCubesPos()){
        glm::vec3 futurePlayerPos = player->getPos()+glm::vec3(move.x, fallCoeff, move.z); //XZ devono considerare il movimento laterale
        if(isCubeSideColliding(it, futurePlayerPos)){
            return true;
        }
    }
    return false;
}

bool PhysicsWorld::isCubeSideColliding(const glm::vec3 &cubePos, const glm::vec3 &playerPos) const {
    bool isCollidingXZ = (abs(playerPos.z - cubePos.z) < 1 && abs(playerPos.x - cubePos.x) < 1); //Ritorna verso  se il centro è tra i confini dl blocco (x e z)
    //Il player appare più alto... devorebbe quindi non considerare le collisioni con pavimento
    bool isCollidingY = false;
    if(playerPos.y>cubePos.y)
        isCollidingY = (abs(playerPos.y-cubePos.y) < 1.5);  //(Controlla collisione nella y)
    else
        //Sennò la camera si bugga nei blocchi sopra il player...
        isCollidingY = (abs(playerPos.y-cubePos.y) < 2);  //(Controlla collisione nella y)
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

void PhysicsWorld::playerJump() const {
    if(player->isJumping()){
        player->changeY(0.1);
    }
}

void PhysicsWorld::rayCastCheck(const glm::vec3& camDirection){
    bool found = false;
    std::vector<int> raySteps;
    std::vector<std::pair<glm::vec3, float>> distances;
    for(const auto& it: cubesContainer->getVisibleCubesPos()){
        if(isNear(player->getPos(), it, 6)) {  //Se non è vicino manco lo controllo
            if (rayCast.checkCube(player->getPos() + glm::vec3(0.0, 1.0, 0.0), camDirection, it)) {
                distances.push_back({it, glm::distance(player->getPos() + glm::vec3(0.0, 1.0, 0.0), it)});
                found = true;
            }
        }
    }
    //PEr essere sicuro venga preso il blocco individuato  più vicino
    std::pair<glm::vec3, float> min = {glm::vec3(0.0), 100.f};
    for(const auto& it:distances){
        if(it.second < min.second)
            min = it;
    }
    if(found) {
        cubeBorder.setPos(min.first);
        rayCastFound = true;
    }
    else
        rayCastFound = false;
}

void PhysicsWorld::drawBorderCube(const glm::mat4 &projection, const glm::mat4 &view) const {
    if(rayCastFound){
        cubeBorder.draw(projection, view);
    }
}

void PhysicsWorld::cubeInteractions(sf::Event& event) {
    if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left){
        if(rayCastFound){
            Face selectedFace = rayCast.calcSelectedFace(cubeBorder.getPos());
            glm::vec3 posOffeset;
            if(selectedFace == Face::front)
                posOffeset = glm::vec3(0.0, 0.0, 1.0);
            if(selectedFace == Face::back)
                posOffeset = glm::vec3(0.0, 0.0, -1.0);
            if(selectedFace == Face::right)
                posOffeset = glm::vec3(1.0, 0.0, 0.0);
            if(selectedFace == Face::left)
                posOffeset = glm::vec3(-1.0, 0.0, 0.0);
            if(selectedFace == Face::top)
                posOffeset = glm::vec3(0.0, 1.0 ,0.0);
            if(selectedFace == Face::bottom)
                posOffeset = glm::vec3(0.0, -1.0, 0.0);
            glm::vec3 newCubePos = cubeBorder.getPos()+posOffeset;
            if(!isCubeColliding(newCubePos, player->getPos())) //Sennè il player si bugga dentro il blocco aggiunto
                cubesContainer->addCube(newCubePos, Type::Grass);
        }
    }
    else if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Right){
        if(rayCastFound){
            cubesContainer->removeCube(cubeBorder.getPos());
        }
    }
}

bool PhysicsWorld::isNear(const glm::vec3 &point1, const glm::vec3 point2, float dist) const {
    return(glm::distance(point1, point2) < dist);
}

