#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL

#include <glad/glad.h>
#include <SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<glm/gtx/string_cast.hpp>
#include"helper.h"
#include"stb_image.h"
#include"Shader.h"
#include "Camera.h"
#include"GrassCube.h"

void initWindow(sf::Window& window);
void initOpenGL();
int main() {
    sf::Window window;
    initWindow(window);
    initOpenGL();

    GrassCube::init();
    GrassCube grassCube(glm::vec3(0.0, 0.0, 0.0), Type::Grass);
    GrassCube grass2(glm::vec3 (2.0, 0.0, 0.0), Type::Terrain);

    Camera camera;

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1600.f/1200.f, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(camera.getPos(), camera.getPos() + camera.getFront(), glm::vec3(0.0, 1.0, 0.0));

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)){
                window.close();
                return -1;
            }
            else if(event.type == sf::Event::Resized){
                glViewport(0, 0, event.size.width, event.size.height);
            }
            else if(event.type == sf::Event::MouseMoved){
                camera.handleRotation(event);
            }
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.handleMovement();

        grass2.draw();

        grassCube.draw();

        view = glm::lookAt(camera.getPos(), camera.getPos() + camera.getFront(), glm::vec3(0.0, 1.0, 0.0));

        GrassCube::updateMatrix(view, projection);

        camera.reset(window);

        window.display();
    }
}











void initWindow(sf::Window& window){
    sf::ContextSettings settings;
    settings.minorVersion = 3;
    settings.majorVersion = 3;
    settings.attributeFlags = sf::ContextSettings::Core;
    settings.depthBits = 24;
    window.create(sf::VideoMode(1600, 1200), "Minecraft", sf::Style::Default, settings);
    window.setFramerateLimit(60);
    window.setActive();
    window.setMouseCursorVisible(false);
}

void initOpenGL(){
    if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(sf::Context::getFunction))){
        std::cerr << "Errore nel caricamento di glad" << std::endl;
    }

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2, 0.3, 0.3, 1.0);
    glViewport(0, 0, 1600, 1200);
}