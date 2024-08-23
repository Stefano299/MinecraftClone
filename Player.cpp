//
// Created by stefano on 8/23/24.
//

#include "Player.h"

Player::Player(const glm::vec3 &pos, float speed) {
    this->pos = pos;
    this->speed = speed;
    createVertices(); //Creo i vertici per un cilindro
    calculateNormals();
    createShader();
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &verticesVBO);
    glGenBuffers(1, &normalsVBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, normalsVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, (void*)0);
    glEnableVertexAttribArray(1);
    shader.useProgram();
    shader.changeUniform4M("model", glm::translate(glm::mat4(1.0), pos));
}

void Player::createVertices() {
    for(int i = 0; i < 36; i++){
        float x1 = 0.5*cos(glm::radians(10.0*i));
        float z1 = 0.5*sin(glm::radians(10.0*i));
        float x2 = 0.5*cos(glm::radians(10.0*(i+1)));
        float z2 = 0.5*sin(glm::radians(10.0*(i+1)));

        vertices[18*i] = x1;
        vertices[18*i+1] = -1.0f;
        vertices[18*i+2] = -z1;

        vertices[18*i+3]= x1;
        vertices[18*i+4] = 1.0f;
        vertices[18*i+5] = -z1;

        vertices[18*i+6] = x2;
        vertices[18*i+7] = -1.0f;
        vertices[18*i+8] = -z2;

        vertices[18*i+9] = x2;
        vertices[18*i+10] = -1.0f;
        vertices[18*i+11] = -z2;

        vertices[18*i+12] = x1;
        vertices[18*i+13] = 1.0f;
        vertices[18*i+14] = -z1;

        vertices[18*i+15]= x2;
        vertices[18*i+16] = 1.0f;
        vertices[18*i+17] = -z2;
    }
}

void Player::calculateNormals() {
    for(int i = 0; i < 36; i++){
        glm::vec3 vec1(0.0);  //Vettore verticale dal basso all'alto
        vec1.x = vertices[18*i] - vertices[18*i+3];
        vec1.y = vertices[18*i+1] - vertices[18*i+4];
        vec1.z = vertices[18*i+2] - vertices[18*i+5];
        vec1 = -vec1; //Per avere il giusto  verso nel prodotto vettoriale
        glm::vec3 vec2(0.0); //Vettore obliquo dall'alto in basso
        vec2.x = vertices[18*i+6] - vertices[18*i+3];
        vec2.y = vertices[18*i+7] - vertices[18*i+4];
        vec2.z = vertices[18*i+8] - vertices[18*i+5];
        glm::vec3 normal = -glm::normalize(glm::cross(vec1, vec2)); //Vettore normale alla faccia del poligono (ai due vettori trovati)
        for(int j = 0; j < 6; j++){
            normals[(i*18)+j*3] = normal.x;
            normals[(i*18)+j*3+1] = normal.y;
            normals[(i*18)+j*3+2] = normal.z;
        }
    }
}


void Player::draw(const glm::mat4 &projection, const glm::mat4 &view) const {
    shader.useProgram();
    shader.changeUniform4M("view", view);
    shader.changeUniform4M("projection", projection);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 216);
}

void Player::createShader() {
    shader.loadVertex("../vPlayer.glsl");
    shader.loadFragment("../fPlayer.glsl");
    shader.createProgram();
}

const glm::vec3 &Player::getPos() const {
    return pos;
}

void Player::setPos(const glm::vec3 &newPos) {
    shader.useProgram();
    shader.changeUniform4M("model", glm::translate(glm::mat4(1.0), pos));
}

void Player::handleInput() {
    glm::vec3 move(0.0); //Vettore spostamento
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        move.z -= 1;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        move.z += 1;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        move.x += 1;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        move.x -= 1;
    }
    //Solita cosa per impedire vada più veloce in diagonale
    if(abs(move.x) + abs(move.z) == 2){  //Se normalizzo il vettore ed ha un solo componente dà componenti indefiniti
        move = glm::normalize(move);
    }
    pos += move*speed;
    shader.useProgram();
    shader.changeUniform4M("model", glm::translate(glm::mat4(1.0), pos));
}

