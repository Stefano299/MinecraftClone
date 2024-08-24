//
// Created by stefano on 8/21/24.
//

#include "CubesContainer.h"
#include"helper.h"

void CubesContainer::genCube(const glm::vec3& pos, int width, int height, int depth) {
    int nCubes = width*height*depth;
    cubes.reserve(nCubes);
    cubesModel.reserve(nCubes);
    cubesType.reserve(nCubes);
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            for(int k = 0; k < depth; k++){
                glm::vec3 cubePos = pos + glm::vec3(i, -j, -k);
                glm::mat4 cubeModel = glm::translate(glm::mat4(1.0), cubePos);
                if(j > 0) {
                    cubes.push_back(GrassCube(cubePos, Type::Terrain));
                    cubesModel.push_back(cubeModel);
                    cubesType.push_back(0);
                }
                else if(j == 0){
                    cubes.push_back(GrassCube(cubePos, Type::Grass));
                    cubesModel.push_back(cubeModel);
                    cubesType.push_back(1);
                }
            }
        }
    }

    //setHidden(); //Una volta creati decido quali non vanno disegnati
    setInstances();

    /*for(int i = 0; i < width; i++){
        int j = 0;
        for(int k = 0; k < depth; k++){
            if( i> 0){
                j = cubes[(i-1)*width + k].getPos().y-pos.y;
                std::cout << j << std::endl;
            }
            if(j==0){
                j += probability(4);
            }
            else if(j == 1){
                j += probability(95);
            }
            else if(j >=2 && k  > depth/2){
                j -= probability(90);
            }
            else if(j == 2){
                j += probability(87);
            }
            else if(j == 3){
                j -= probability(20);

                j += probability(70);
            }
            else if(j == 4){
                j -= probability(25);
                j += probability(30);
            }
            else if(j == 5){
                j -= probability(80);
            }
            auto it = cubes.end();
            if(cubes.size() > 2){
                it -=1;
                if(abs((it->getPos().y-pos.y) - j) > 1){
                    cubes.push_back(GrassCube(pos+glm::vec3(i, cubes[(i-1)*width + k].getPos().y-pos.y, k), Type::Grass));
                }
                else
                    cubes.push_back(GrassCube(pos+glm::vec3(i, j, k), Type::Grass));
            }
            else
                cubes.push_back(GrassCube(pos+glm::vec3(i, j, k), Type::Grass));

        }
    }*/
}

void CubesContainer::drawCubes() const {
    int instanceCount = cubes.size();
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    /*for(auto it: cubes){
        if(!it.isHidden()) {
            it.draw();
        }
    }*/
    GrassCube::draw();
    glDrawArraysInstanced(GL_TRIANGLES, 0, 36, instanceCount);
    glDisable(GL_CULL_FACE);
}

bool CubesContainer::isPresent(const glm::vec3 &pos) const {
    bool found = false;
    for(auto it: cubes){
        if(abs(it.getPos().x-pos.x) <= 0.5 && abs(it.getPos().y-pos.y) <= 0.5 && abs(it.getPos().z-pos.z) <= 0.5){
            found = true;
            return found;
        }
    }
    return found;

}

bool CubesContainer::isOnSameY(const GrassCube &cube) const {
    bool found = false;
    for(auto it: cubes){
        if(it.getPos().y == cube.getPos().y && it != cube){
            if(abs(it.getPos().x - cube.getPos().x) <= 1.1  && abs(it.getPos().z - cube.getPos().z) <= 1.1) {
                found = true;
                return found;
            }
        }
    }
    return found;
}

int CubesContainer::nSurroundingCubes(const GrassCube &cube) const {
    int n = 0;
    for(auto it: cubes){
        if(it != cube){
            if(abs(it.getPos().x - cube.getPos().x) <= 1.1  && abs(it.getPos().z - cube.getPos().z) <= 1.1 && abs(it.getPos().y - cube.getPos().y) <= 1.1){
                n++;
            }
        }
    }
    return n;
}

void CubesContainer::setHidden() {
    for(auto& it: cubes){
        if(nSurroundingCubes(it) == 26){ //Se è circondato interamente da cubi non va disegnato
            it.setHidden(true);
        }
    }
}

void CubesContainer::setInstances() {
    int nCubes = cubesModel.size();
    std::size_t vec4Size = sizeof(glm::vec4);
    glBindVertexArray(GrassCube::getVAO());
    glGenBuffers(1, &instancesVBO);
    glBindBuffer(GL_ARRAY_BUFFER, instancesVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4)*nCubes+sizeof(int)*nCubes, nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::mat4)*nCubes, cubesModel.data());
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, vec4Size*4, (void*)0);
    glEnableVertexAttribArray(2);
    glVertexAttribDivisor(2, 1);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, vec4Size*4, (void*)(1 * vec4Size));
    glEnableVertexAttribArray(3);
    glVertexAttribDivisor(3, 1);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, vec4Size*4, (void*)(2 * vec4Size));
    glEnableVertexAttribArray(4);
    glVertexAttribDivisor(4, 1);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, vec4Size*4, (void*)(3 * vec4Size));
    glEnableVertexAttribArray(5);
    glVertexAttribDivisor(5, 1);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::mat4)*nCubes, sizeof(int)*nCubes, cubesType.data());
    glVertexAttribIPointer(6, 1, GL_INT, sizeof(int), (void*)(nCubes*vec4Size*4));
    glEnableVertexAttribArray(6);
    glVertexAttribDivisor(6, 1);
    /*unsigned int otherVBO;
    glGenBuffers(1, &otherVBO);
    glBindBuffer(GL_ARRAY_BUFFER, otherVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(int)*nCubes, cubesType.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(6, 1, GL_INT, GL_FALSE, sizeof(int), (void*)0);
    glEnableVertexAttribArray(6);
    glVertexAttribDivisor(6, 1);*/
}
