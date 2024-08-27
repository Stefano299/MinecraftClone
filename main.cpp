#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL

#include <glad/glad.h>
#include <SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<glm/gtx/string_cast.hpp>
#include"headers/helper.h"
#include"headers/stb_image.h"
#include"headers/Shader.h"
#include "headers/Camera.h"
#include"headers/GrassCube.h"
#include"headers/constants.h"
#include"headers/CubesContainer.h"
#include"headers/Player.h"
#include"headers/Sphere.h"
#include"headers/SkyBox.h"
#include "headers/PhysicsWorld.h"
#include"headers/frameTime.h"
#include"headers/FirstPersonController.h"
#include"headers/CrossAir.h"
#include<cstdlib>

long int frameTime = 0;

void initWindow(sf::Window& window);
void initOpenGL();
void showFPS();

void handleEvents(sf::Window &window, Camera &camera, FirstPersonController &firstPersonController,
                  PhysicsWorld &physicsWorld);

void update(sf::Window &window, const CubesContainer &container, Camera &camera, Player &player,
            const FirstPersonController &firstPersonController, const Sphere &lightSource, const SkyBox &skyBox,
            PhysicsWorld &physicsWorld, const CrossAir &crossAir);

int main() {
    sf::Window window;
    initWindow(window);
    initOpenGL();

    CubesContainer container;
    container.genCube(glm::vec3(-10, -1.5, 50), 100, 7, 100);

    Camera camera(glm::vec3(0.0, 0.0, 20.0), 0.3, 0.12);

    Player player(glm::vec3(0.0, 0.0, 0.0), 0.14);
    FirstPersonController firstPersonController(&camera, &player);
    Sphere lightSource(glm::vec3 (0, 10, 30), player);
    SkyBox skyBox;
    PhysicsWorld physicsWorld(&player, &container);
    player.setPhysicsWorld(&physicsWorld);
    CrossAir crossAir;
    while(window.isOpen()){
        //showFPS();
        frameTime++;
        handleEvents(window, camera, firstPersonController, physicsWorld);
        update(window, container, camera, player, firstPersonController, lightSource, skyBox,
               physicsWorld, crossAir);

    }
}



void update(sf::Window &window, const CubesContainer &container, Camera &camera,
            Player &player, const FirstPersonController &firstPersonController,
            const Sphere &lightSource, const SkyBox &skyBox, PhysicsWorld &physicsWorld, const CrossAir &crossAir) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 projection = camera.getProjection();
    glm::mat4 view = camera.getView();

    camera.handleMovement();
    player.handleInput();  //Deve stare prima per jumping
    physicsWorld.rayCastCheck(camera.getFront());
    physicsWorld.playerJump();//Deve stare prima sennò playerFall mette jumping=false visto che tocca terra
    physicsWorld.playerFall();

    lightSource.draw(projection, view);
    container.drawCubes();
    physicsWorld.drawBorderCube(projection, view);
    firstPersonController.update();
    player.draw(projection, view, camera.getPos());
    skyBox.draw(projection, glm::mat4(glm::mat3(view)));
    crossAir.draw(projection);
    GrassCube::updateMatrix(view, projection);

    camera.reset(window);

    window.display();
}

void handleEvents(sf::Window &window, Camera &camera, FirstPersonController &firstPersonController,
                  PhysicsWorld &physicsWorld) {
    static sf::Event event;
    while(window.pollEvent(event)){
        if(event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)){
            window.close();
        }
        else if(event.type == sf::Event::Resized){
            glViewport(0, 0, event.size.width, event.size.height);
        }
        else if(event.type == sf::Event::MouseMoved){
            camera.handleRotation(event);
        }
        camera.handleCursorLock(event, window);
        firstPersonController.getInput(event);
        physicsWorld.cubeInteractions(event);
    }
}


void initWindow(sf::Window& window){
    srand(time(0)); //Per una funzione in helper
    sf::ContextSettings settings;
    settings.minorVersion = 3;
    settings.majorVersion = 3;
    settings.attributeFlags = sf::ContextSettings::Core;
    settings.depthBits = 24;
    settings.antialiasingLevel = 4;
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Minecraft", sf::Style::Default, settings);
    window.setFramerateLimit(60);
    window.setActive();
}

void initOpenGL(){
    if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(sf::Context::getFunction))){
        std::cerr << "Errore nel caricamento di glad" << std::endl;
    }
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2, 0.3, 0.3, 1.0);
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_MULTISAMPLE);
    glLineWidth(5.0f); //Per il disegno del bordo dei cubi
}

void showFPS(){
    static sf::Clock clock;
    sf::Time time;
    time = clock.getElapsedTime();
    std::cout << 1.f/time.asSeconds() << std::endl;
    clock.restart();
}