//
// Created by stefano on 8/26/24.
//

#include "FirstPersonController.h"
#include"Player.h"
#include"Camera.h"


FirstPersonController::FirstPersonController(Camera *camera, Player *player) {
    this->camera = camera;
    this->player = player;
    active = false;
}

void FirstPersonController::update() const {
    if(active) {
        player->setFirstPerson(true);
        camera->setPos(player->getPos() + glm::vec3(0.0, 1.0, 0.0)); //Lo metto in cima al cilindro
        player->setYaw(camera->getYaw()+90.0f);
        //std::cout << "CAMERA: " << camera->getYaw() << " PLAYER: "<< player->getYaw() << std::endl;
    }
}

void FirstPersonController::getInput(sf::Event& event) {
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P){
        if(!active)
            active = true;
        else {
            active = false;
            player->setFirstPerson(false);
        }
    }
}
