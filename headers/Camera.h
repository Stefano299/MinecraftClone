//
// Created by stefano on 8/18/24.
//

#ifndef LIGHTING_CAMERA_H
#define LIGHTING_CAMERA_H

#include <iostream>

#include <SFML/Window.hpp>
#include "glad/glad.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Camera {
private:
    float yaw;
    float pitch;
    float sensitivity;
    float speed;
    int lastX;
    int lastY;
    bool cursorLock;
    glm::vec3 position;
    glm::vec3 front;
    glm::mat4 projection;
public:
    explicit Camera(const glm::vec3& pos, float speed, float sensitivity);
    void handleMovement();
    void handleCursorLock(sf::Event& event, sf::Window& window);
    void handleRotation(const sf::Event& event);
    void reset(sf::Window& window);
    const glm::vec3& getFront() const;
    const glm::vec3& getPos() const;;
    void setPos(const glm::vec3& newPos);
    float getYaw() const;
    glm::mat4 getView() const;
    bool isCursorLocked() const;
    const glm::mat4& getProjection() const;
};


#endif //LIGHTING_CAMERA_H
