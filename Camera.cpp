//
// Created by stefano on 8/18/24.
//

#include "Camera.h"
#include <SFML/Window.hpp>

Camera::Camera() {
    yaw = -90.0f;
    pitch = 0.0f;
    speed = 0.08f;
    sensitivity = 0.1f;
    lastX = 800;
    lastY = 600;
    cameraPos = glm::vec3(0.0, 0.0, 6.0);
    cameraFront = glm::vec3(0.0, 0.0, -1.0);
}

void Camera::handleMovement() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        cameraPos += speed*cameraFront;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        cameraPos -= speed*cameraFront;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        cameraPos -= glm::normalize(glm::cross(cameraFront, glm::vec3(0.0, 1.0, 0.0)))*speed;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        cameraPos += glm::normalize(glm::cross(cameraFront, glm::vec3(0.0, 1.0, 0.0)))*speed;
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
    sf::Mouse::setPosition(sf::Vector2i (800, 600), window);
    lastX = 800;
    lastY = 600;
}
