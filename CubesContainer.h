//
// Created by stefano on 8/21/24.
//

#ifndef MINECRAFT_CUBESCONTAINER_H
#define MINECRAFT_CUBESCONTAINER_H

#include"GrassCube.h"
#include<vector>

class CubesContainer {
private:
    std::vector<GrassCube> cubes;
public:
    CubesContainer() = default;
    void genCube(const glm::vec3& pos, int width, int height, int depth);
    void drawCubes() const;
};


#endif //MINECRAFT_CUBESCONTAINER_H
