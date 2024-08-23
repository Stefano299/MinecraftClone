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
#include"constants.h"
#include"CubesContainer.h"
#include"Player.h"
#include"Sphere.h"
#include<cstdlib>


void initWindow(sf::Window& window);
void initOpenGL();
int main() {
    sf::Window window;
    initWindow(window);
    initOpenGL();

    GrassCube::init();
    CubesContainer container;
    container.genCube(glm::vec3(-10, -1.5, 10), 20, 5, 20);

    Camera camera(glm::vec3(0.0, 0.0, 20.0));

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH/SCREEN_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(camera.getPos(), camera.getPos() + camera.getFront(), glm::vec3(0.0, 1.0, 0.0));

    Player player(glm::vec3(0.0, 0.0, 0.0), 0.1);
    Sphere lightSource(glm::vec3 (0, 10, 0), player);

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
        player.handleInput();

        lightSource.draw(projection, view);
        container.drawCubes();
        player.draw(projection, view, camera.getPos());

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
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Minecraft", sf::Style::Default, settings);
    window.setFramerateLimit(60);
    window.setActive();
    window.setMouseCursorVisible(false);
}

void initOpenGL(){
    srand(time(0)); //TODO qua non ci sta ma va beh per ora lo lascio
    if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(sf::Context::getFunction))){
        std::cerr << "Errore nel caricamento di glad" << std::endl;
    }

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2, 0.3, 0.3, 1.0);
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}