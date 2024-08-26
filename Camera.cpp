//
// Created by stefano on 8/18/24.
//

#include "Camera.h"
#include <SFML/Window.hpp>
#include"constants.h"

Camera::Camera(const glm::vec3 &pos, float speed, float sensitivity) {
    yaw = -90.0f;
    pitch = 0.0f;
    this->speed = speed;
    this->sensitivity = sensitivity;
    lastX = SCREEN_WIDTH/2;
    lastY = SCREEN_HEIGHT/2;
    cameraPos = pos;
    cameraFront = glm::vec3(0.0, 0.0, -1.0);
}

void Camera::handleMovement() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        cameraPos += speed*cameraFront;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        cameraPos -= speed*cameraFront;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        cameraPos -= glm::normalize(glm::cross(cameraFront, glm::vec3(0.0, 1.0, 0.0)))*speed;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        cameraPos += glm::normalize(glm::cross(cameraFront, glm::vec3(0.0, 1.0, 0.0)))*speed;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
        glm::vec3 right = glm::normalize(glm::cross(cameraFront, glm::vec3(0.0, 1.0, 0.0)));
        cameraPos += glm::normalize(glm::cross(right, cameraFront))*speed;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
        glm::vec3 right = glm::normalize(glm::cross(cameraFront, glm::vec3(0.0, 1.0, 0.0)));
        cameraPos -= glm::normalize(glm::cross(right, cameraFront))*speed;
    }
}

const glm::vec3 &Camera::getFront() const {
    return cameraFront;
}

const glm::vec3 &Camera::getPos() const {
    return cameraPos;
}

void Camera::handleRotation(const sf::Event &event) {
    float offsetX = event.mouseMove.x - lastX;
    float offsetY = lastY - event.mouseMove.y;
    lastX = event.mouseMove.x;
    lastY = event.mouseMove.y;

    offsetX *= sensitivity;
    offsetY *= sensitivity;

    pitch += offsetY;
    yaw += offsetX;

    if(pitch > 89.0f)
        pitch = 89.0f;
    else if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw))*cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z= sin(glm::radians(yaw))*cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}

void Camera::reset(sf::Window& window) {
    sf::Mouse::setPosition(sf::Vector2i (SCREEN_WIDTH/2, SCREEN_HEIGHT/2), window);
    lastX = SCREEN_WIDTH/2;
    lastY = SCREEN_HEIGHT/2;
}

void Camera::setPos(const glm::vec3 &newPos) {
    cameraPos = newPos;
}

float Camera::getYaw() const {
    return yaw;
}


