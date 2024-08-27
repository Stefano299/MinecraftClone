//
// Created by stefano on 8/18/24.
//

#include "../headers/Camera.h"
#include <SFML/Window.hpp>
#include"../headers/constants.h"

Camera::Camera(const glm::vec3 &pos, float speed, float sensitivity) {
    yaw = -90.0f;
    pitch = 0.0f;
    this->speed = speed;
    this->sensitivity = sensitivity;
    lastX = SCREEN_WIDTH/2;
    lastY = SCREEN_HEIGHT/2;
    cursorLock = true;
    position = pos;
    front = glm::vec3(0.0, 0.0, -1.0);
    projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH/SCREEN_HEIGHT, 0.1f, 100.0f);
}

void Camera::handleMovement() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        position += speed * front;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        position -= speed * front;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        position -= glm::normalize(glm::cross(front, glm::vec3(0.0, 1.0, 0.0))) * speed;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        position += glm::normalize(glm::cross(front, glm::vec3(0.0, 1.0, 0.0))) * speed;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
        glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0.0, 1.0, 0.0)));
        position += glm::normalize(glm::cross(right, front)) * speed;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
        glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0.0, 1.0, 0.0)));
        position -= glm::normalize(glm::cross(right, front)) * speed;
    }
}

const glm::vec3 &Camera::getFront() const {
    return front;
}

const glm::vec3 &Camera::getPos() const {
    return position;
}

void Camera::handleRotation(const sf::Event &event) {
    if(cursorLock){
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
        front = glm::normalize(direction);
    }
}

void Camera::reset(sf::Window& window) {
    if(cursorLock) {
        window.setMouseCursorVisible(false);
        sf::Mouse::setPosition(sf::Vector2i(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), window);
        lastX = SCREEN_WIDTH / 2;
        lastY = SCREEN_HEIGHT / 2;
    }
}

void Camera::setPos(const glm::vec3 &newPos) {
    position = newPos;
}

float Camera::getYaw() const {
    return yaw;
}

glm::mat4 Camera::getView() const {
    return(glm::lookAt(position, position + front, glm::vec3(0.0, 1.0, 0.0)));
}

void Camera::handleCursorLock(sf::Event &event, sf::Window& window) {
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::L){
        if(cursorLock){
            cursorLock = false;
            window.setMouseCursorVisible(true);
        }
        else{
            cursorLock = true;
            window.setMouseCursorVisible(false);
        }
    }
}

bool Camera::isCursorLocked() const {
    return  cursorLock;
}

const glm::mat4 &Camera::getProjection() const {
    return projection;
}


