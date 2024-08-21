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
    bool isPresent(const glm::vec3& pos) const; //Per determinare se in una posizione si trova un cubo
    bool isOnSameY(const GrassCube& cube) const; //Ritorna vero se è presente un blocco adiacete alla stessa altezza
    int nSurroundingCubes(const GrassCube& cube) const;//Ritorna il numero di cubi adiacenti
    void setHidden(); //Passa in rassegna i cubi e imposta quali devono essere nascosti
public:
    CubesContainer() = default;
    void genCube(const glm::vec3& pos, int width, int height, int depth);
    void drawCubes() const;
};


#endif //MINECRAFT_CUBESCONTAINER_H
