//
// Created by stefano on 8/21/24.
//

#include "CubesContainer.h"
#include"helper.h"

void CubesContainer::genCube(const glm::vec3& pos, int width, int height, int depth) {
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            for(int k = 0; k < depth; k++){
                if(j > 0) {
                    cubes.push_back(GrassCube(pos + glm::vec3(i, -j, -k), Type::Terrain));
                }
                else if(j == 0){
                    cubes.push_back(GrassCube(pos + glm::vec3(i, -j, -k), Type::Grass));
                }
            }
        }
    }

    setHidden(); //Una volta creati decido quali non vanno disegnati

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
    for(auto it: cubes){
        if(!it.isHidden()) {
            it.draw();
        }
    }
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
