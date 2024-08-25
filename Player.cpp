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
    for(int i = 0; i < 72; i++){
        float x1 = 0.5*cos(glm::radians(5.0*i));
        float z1 = 0.5*sin(glm::radians(5.0*i));
        float x2 = 0.5*cos(glm::radians(5.0*(i+1)));
        float z2 = 0.5*sin(glm::radians(5.0*(i+1)));

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
    for(int i = 0; i < 36; i++){ //Per coprire la faccia superiore
        float x1 = 0.5*sin(glm::radians(i*5.0));
        float x2 = 0.5*sin(glm::radians((i+1)*5.0));
        float x3 = 0.5*sin(glm::radians(i*5.0+180));
        float x4 = 0.5*sin(glm::radians((i+1)*5.0+180));

        float z1 = 0.5*cos(glm::radians(i*5.0));
        float z2 = 0.5*cos(glm::radians((1+i)*5.0));
        float z3 = 0.5*cos(glm::radians(i*5.0+180));
        float z4 = 0.5*cos(glm::radians((1+i)*5.0+180));

        float y = 1.0f;

        vertices[648*2+i*18] = x1;
        vertices[648*2+i*18+1] = y;
        vertices[648*2+i*18+2] = z1;

        vertices[648*2+i*18+3] = x2;
        vertices[648*2+i*18+4] = y;
        vertices[648*2+i*18+5] = z2;

        vertices[648*2+i*18+6] = x3;
        vertices[648*2+i*18+7] = y;
        vertices[648*2+i*18+8] = z3;

        vertices[648*2+i*18+9] = x2;
        vertices[648*2+i*18+10] = y;
        vertices[648*2+i*18+11] = z2;

        vertices[648*2+i*18+12] = x4;
        vertices[648*2+i*18+13] = y;
        vertices[648*2+i*18+14] = z4;

        vertices[648*2+i*18+15] = x3;
        vertices[648*2+i*18+16] = y;
        vertices[648*2+i*18+17] = z3;
    }
}

void Player::calculateNormals() {
    for(int i = 0; i < 72; i++){
        glm::vec3 vec1(0.0);  //Vettore verticale dal basso all'alto
        vec1.x = vertices[18*i] - vertices[18*i+3];
        vec1.y = vertices[18*i+1] - vertices[18*i+4];
        vec1.z = vertices[18*i+2] - vertices[18*i+5];
        glm::vec3 vec2(0.0); //Vettore obliquo dall'alto in basso
        vec2.x = vertices[18*i+6] - vertices[18*i+3];
        vec2.y = vertices[18*i+7] - vertices[18*i+4];
        vec2.z = vertices[18*i+8] - vertices[18*i+5];
        glm::vec3 normal = glm::normalize(glm::cross(vec1, vec2)); //Vettore normale alla faccia del poligono (ai due vettori trovati)
        for(int j = 0; j < 12; j++){
            normals[(i*18)+j*3] = normal.x;
            normals[(i*18)+j*3+1] = normal.y;
            normals[(i*18)+j*3+2] = normal.z;
        }
    }
    for(int i = 0; i < 216; i++){
        normals[648*2+i*3] = 0.0;
        normals[648*2+i*3+1] = 1.0;
        normals[648*2+i*3+2] = 0.0;
    }
}


void Player::draw(const glm::mat4 &projection, const glm::mat4 &view, const glm::vec3& cameraPos) const {
    shader.useProgram();
    shader.changeUniform4M("view", view);
    shader.changeUniform4M("projection", projection);
    shader.changeUniformVec3("cameraPos", cameraPos.x, cameraPos.y, cameraPos.z);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, (216+324/3)*2);
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
    pos = newPos;
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

void Player::setLightPos(const glm::vec3 &pos) const {
    shader.useProgram();
    shader.changeUniformVec3("lightPos", pos.x, pos.y, pos.z);
}

bool Player::isFalling() const {
    return falling;
}

void Player::setFalling(bool f) {
    falling = f;
}

