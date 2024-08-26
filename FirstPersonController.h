//
// Created by stefano on 8/26/24.
//

#ifndef MINECRAFT_FIRSTPERSONCONTROLLER_H
#define MINECRAFT_FIRSTPERSONCONTROLLER_H

#include<SFML/Window.hpp>

class Camera;
class Player;
class FirstPersonController {
private:
    Camera* camera;
    Player* player;
    bool active;
public:
    FirstPersonController(Camera* camera, Player* player);
    void getInput(sf::Event& event);
    void update() const;

};


#endif //MINECRAFT_FIRSTPERSONCONTROLLER_H
