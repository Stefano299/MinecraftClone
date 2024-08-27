//
// Created by stefano on 8/21/24.
//

#ifndef MINECRAFT_CUBESCONTAINER_H
#define MINECRAFT_CUBESCONTAINER_H

#include <vector>

#include "GrassCube.h"

class CubesContainer {
private:

    unsigned int instancesVBO;
    std::vector<GrassCube> cubes;
    std::vector<glm::vec3> visibleCubePos;
    std::vector<glm::mat4> cubesModel;
    std::vector<int> cubesType; //0=terrain, 1=grass
    bool isPresent(const glm::vec3& pos) const; //Per determinare se in una posizione si trova un cubo
    bool isOnSameY(const GrassCube& cube) const; //Ritorna vero se è presente un blocco adiacete alla stessa altezza
    int nSurroundingCubes(const GrassCube& cube) const;//Ritorna il numero di cubi adiacenti
    void setHidden(); //Passa in rassegna i cubi e imposta quali devono essere nascosti
    void setInstances();
    void setTypes(); //Passa in rassegna tutti i cubi e mette i tipi nel vettore cubesTypes
    void addSurroundingBlocksToVectors(const glm::vec3& pos);
public:
    CubesContainer();
    void genCube(const glm::vec3& pos, int width, int height, int depth);
    void addCube(const glm::vec3& pos, Type type);
    void drawCubes() const;
    const std::vector<glm::vec3>& getVisibleCubesPos() const;
    void removeCube(const glm::vec3& pos);
};


#endif //MINECRAFT_CUBESCONTAINER_H
