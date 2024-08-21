//
// Created by stefano on 8/21/24.
//

#include "CubesContainer.h"
#include"helper.h"

void CubesContainer::genCube(const glm::vec3& pos, int width, int height, int depth) {
    /*for(int i = 0; i < width; i++){
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
    }*/
    for(int i = 0; i< width; i++){
        int k= 0;

        for(int j = 0; j < depth; j++){
            if(k==0)
                k+= probability(5.5);
            if(k==1){
                k+= probability(95);
            }
            if(k==2)
                k+= probability(94);
            if(k==3)
                k+= probability(90.5);
            if(k==4)
                k+= probability(85);
            if(k == 5) {
                k += probability(79);
                k-= probability(8);
            }
            if(k==6){
                k+= probability(43.7);
                k-= probability(13);
            }
            if(k > 6 && k < 10){
                k += probability(12);
                k-= probability(56);
            }
            else{
                k -= probability(87);
            }
            cubes.push_back(GrassCube(pos + glm::vec3(i, -k, -j), Type::Grass));
        }
    }
}

void CubesContainer::drawCubes() const {
    for(auto it: cubes){
        it.draw();
    }
}
