//
// Created by stefano on 7/25/24.
//

#ifndef OPENGL_HELPER_H
#define OPENGL_HELPER_H

#include <iostream>

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

std::string loadShader(const char* path);
int probability(float prob); //Ritorna 1 con una probabilità = prob (massimo una cifra decimale)
int getSign(int x);
void showVectorInfo(const glm::vec3& vec);

#endif //OPENGL_HELPER_H
