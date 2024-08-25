//
// Created by stefano on 8/18/24.
//

#ifndef LIGHTING_CAMERA_H
#define LIGHTING_CAMERA_H

#include <iostream>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SFML/Window.hpp>


class Camera {
private:
    float yaw;
    float pitch;
    float sensitivity;
    float speed;
    int lastX;
    int lastY;
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
public:
    explicit Camera(const glm::vec3& pos, float speed, float sensitivity);
    void handleMovement();
    void handleRotation(const sf::Event& event);
    void reset(sf::Window& window);
    const glm::vec3& getFront() const;
    const glm::vec3& getPos() const;;
};


#endif //LIGHTING_CAMERA_H
