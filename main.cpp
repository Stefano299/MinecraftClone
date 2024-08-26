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
#include"SkyBox.h"
#include "PhysicsWorld.h"
#include"frameTime.h"
#include"FirstPersonController.h"
#include"CrossAir.h"
#include<cstdlib>

long int frameTime = 0;

void initWindow(sf::Window& window);
void initOpenGL();

int main() {
    sf::Window window;
    initWindow(window);
    initOpenGL();

    GrassCube::init();
    CubesContainer container;
    container.genCube(glm::vec3(-10, -1.5, 10), 20, 10, 20);
    container.genCube(glm::vec3 (-16, -9, 10), 4, 1, 15);
    container.genCube(glm::vec3(-6, -0.5, -12), 5, 1, 3);
    container.genCube(glm::vec3(-6, 1.5, -15), 5, 2, 3);


    Camera camera(glm::vec3(0.0, 0.0, 20.0), 0.3, 0.12);

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH/SCREEN_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(camera.getPos(), camera.getPos() + camera.getFront(), glm::vec3(0.0, 1.0, 0.0));

    Player player(glm::vec3(0.0, 0.0, 0.0), 0.14);
    FirstPersonController firstPersonController(&camera, &player);
    Sphere lightSource(glm::vec3 (0, 10, 30), player);
    SkyBox skyBox;
    PhysicsWorld physicsWorld(&player, &container);
    player.setPhysicsWorld(&physicsWorld);
    CrossAir crossAir;
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //sf::Clock clock;
    //sf::Time time;

    while(window.isOpen()){
        /*time = clock.getElapsedTime();
        std::cout << 1.f/time.asSeconds() << std::endl;
        clock.restart();*/
        frameTime++;
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
            firstPersonController.getInput(event);
            physicsWorld.cubeInteractions(event);
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.handleMovement();
        player.handleInput();  //Deve stare prima per jumping
        physicsWorld.rayCastCheck(camera.getFront());
        physicsWorld.playerJump();//Deve stare prima sennò playerFall mette jumping=false visto che tocca terra
        physicsWorld.playerFall();

        //physicsWorld.playerSideCollisions(); fa callback metodo move di player

        lightSource.draw(projection, view);
        container.drawCubes();
        physicsWorld.drawBorderCube(projection, view);
        firstPersonController.update();
        player.draw(projection, view, camera.getPos());
        skyBox.draw(projection, glm::mat4(glm::mat3(view)));
        crossAir.draw();

        view = glm::lookAt(camera.getPos(), camera.getPos() + camera.getFront(), glm::vec3(0.0, 1.0, 0.0));  //TODO mettere view nella classe camera e fare getView

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
    settings.antialiasingLevel = 4;
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
    glEnable(GL_MULTISAMPLE);
    glLineWidth(5.0f); //Per il disegno del bordo dei cubi
}